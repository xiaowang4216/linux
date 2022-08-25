#include "get_xy_hd.h"


int x0_value,y0_value;

//**********************************************************
//函数名： get_xy   获取触摸屏坐标
//参数：   
//      int x_1     滑动区域范围左上角像素横坐标
//      int y_1     滑动区域范围左上角像素纵坐标
//      int x_2     滑动区域范围右下角像素横坐标
//      int y_2     滑动区域范围右下角像素纵坐标
//返回值： int      -1打开文件失败
//**********************************************************
int get_xy_hd(int x_1,int y_1,int x_2,int y_2)
{
	int ts_flag = 0;//（右滑：1 左滑：2 下滑：3 上滑：4）
	int x,y;
	int x0_value,y0_value;
	int x_flag = 0;
	int y_flag = 0;
	//1.打开触摸屏驱动
	int ts_fd = open("/dev/input/event0",O_RDWR);
	if(ts_fd<0)
	{
		printf("open ts fail\n");
		return -1;
	}
	printf("open ts ok\n");   
	//2.定义一个输入子系统结构体
	struct input_event ts;
	
	//3.循环读取触摸屏驱动，检测是否产生了触摸动作
	while(1)
	{
	    //1.如果产生了触摸动作就把输入数据读取到输入子系统
    	read(ts_fd,&ts,sizeof(ts));
	   
	    //2.分析输入子系统获取触摸坐标
	     //1.判断是否是触摸事件
		 if(ts.type ==  EV_ABS)
		 {
			//1.判断是否是x轴事件 
			if(ts.code ==  ABS_X ) 
			{
				x = ts.value;
				if(x_flag == 0)//保存起点坐标
				{
					x0_value = x;
					x_flag = 1;
				}
				
			}
			 //2.判断是否是y轴事件
			if(ts.code ==  ABS_Y ) 
			{
				y = ts.value;
				if(y_flag == 0)//保存起点坐标
				{
					y0_value = y;
					y_flag = 1;
				}
			}
		 }			 

         //2.判断手指头是否离开了屏幕
		 if(ts.type == EV_KEY && ts.code == BTN_TOUCH)
		 {
			  //离开了，保存当前的触摸坐标，跳出循环
			 if(ts.value == 0)
			 {            
                if((x>x_1&&x<x_2)&&(y>y_1&&y<y_2))
                {
                    if(x - x0_value > 30)//右滑
				 {
					 //printf("right floating \n");
					 ts_flag = 1;
					 break; 
				 }
				 if(x - x0_value < -30)//左滑
				 {
					 //printf("left floating \n");
					 ts_flag = 2;
					 break; 
				 }
				if(y - y0_value > 30)//下滑
				 {
					 //printf("down floating \n");
					 ts_flag = 3;
					 break; 
				 }
				 if(y - y0_value < -30)//上滑
				 {
					 //printf("up floating \n");
					 ts_flag = 4;
					 break; 
				 }

                }
			    break;

			 }
		 }
           
		
	}
	
	//4.关闭驱动
	   close(ts_fd);	
}