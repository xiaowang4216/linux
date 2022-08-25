#include "showbmp.h"

//**********************************************************
//函数名： showbmp   在lcd任意位置显示任意大小的图片
//参数：   
//      char *bmpname     图片位置
//      int x0            显示位置横坐标
//      int y0            显示位置纵坐标
//返回值： int      -1打开文件失败
//**********************************************************
int showbmp(char *bmpname,int x0,int y0)
{
        // 1. 打开lcd的驱动
	int lcd_fd = open("/dev/fb0",O_RDWR);
	if(lcd_fd < 0)
	{
		printf("open lcd  fail\n");
		return -1;
	}
	
	//printf("open lcd ok\n");
	//2. 申请虚拟共享内存
	unsigned char *lcd =  mmap(NULL,800*480*4,PROT_READ| PROT_WRITE,MAP_SHARED,lcd_fd,0);//*lcd  lcd[]
	if(lcd == NULL)
	{
		printf("mmap fail\n");
		return -1;
	}
	//printf("mmap ok\n");
	
	// 3.打开bmp图片 
	int bmp_fd = open(bmpname,O_RDWR);
	if(bmp_fd < 0)
	{
		printf("open bmp fail\n");
		return -1;
	}
	
	//printf("open bmp ok\n");
	
	//4.把图片里的颜色数据读取出来
	//读取头数据
	unsigned char bmpinfo[54];
	read(bmp_fd,bmpinfo,54);//跳过头54个字节的数据
	// 3.通过算法获取宽度和高度
	int w = bmpinfo[0x15]<<24| bmpinfo[0x14]<<16|bmpinfo[0x13]<<8|bmpinfo[0x12];
	int h = bmpinfo[0x19]<<24| bmpinfo[0x18]<<16|bmpinfo[0x17]<<8|bmpinfo[0x16];
	//printf("w %d h %d \n",w,h);
	
	unsigned char bmp[w*h*3];
	read(bmp_fd,bmp,w*h*3);
	
	//5.需要把24位的bmp数据转换成32位的lcd数据同时放到虚拟内存
      //使用行列式操作
	int x,y;
    for(y=y0;y<h+y0;y++)//0--479
    {
	    for(x=x0;x<w+x0;x++)//0--799
		{
			//第y行第x个
            lcd[0+4*x+800*4*y] = bmp[0+3*(x-x0)+w*3*(h-1-(y-y0))];//B 
            lcd[1+4*x+800*4*y] = bmp[1+3*(x-x0)+w*3*(h-1-(y-y0))];//G
            lcd[2+4*x+800*4*y] = bmp[2+3*(x-x0)+w*3*(h-1-(y-y0))];//R
            lcd[3+4*x+800*4*y] = 0;//A

		}			 
	}	
    //6.关闭打开的文件，释放内存
     close(lcd_fd);
     close(bmp_fd);	 
	 munmap(lcd,800*480*4);    



}