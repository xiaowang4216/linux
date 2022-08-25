#include "loading.h"

//**********************************************************
//函数名： loading   进度条显示
//参数：   
//      int w           图片宽
//      int h           图片高
//      int x0          显示位置横坐标（左上角）
//      int y0          显示位置纵坐标（左上角）
//      int usleep_time 进度条速度（微妙延时）
//      int R           像素点红原色
//      int B           像素点蓝原色
//      int G           像素点绿原色
//      int A           图片透明度
//返回值： int      -1打开文件失败
//**********************************************************
int loading(int w,int h,int x0,int y0,int usleep_time,int R,int B,int G,int A)
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
	printf("mmap ok\n");
	
	
	//3.处理颜色数据同时把颜色数据丢到虚拟内存
      //使用行列式操作
	int x,y;
    //int r;
    //int count = 0;
    //int g = 160,b = 122;
    //r = 255;
     for(x=x0;x<x0+w;x++)//0--799
    {
        if(x%10 == 0)
        {
            B = B - 1;
        }
		for(y=y0;y<y0+h;y++)//0--479
		{
			//第y行第x个
            lcd[0+4*x+800*4*y] = R;//R
            lcd[1+4*x+800*4*y] = B;//B
            lcd[2+4*x+800*4*y] = G;//G
            lcd[3+4*x+800*4*y] = A;//A

		}
        usleep(usleep_time);//1000		
	}	
    //4.关闭驱动、释放内存
     close(lcd_fd);   
	 munmap(lcd,800*480*4);	
}