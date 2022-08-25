#include "get_xy.h"

int tx,ty;//（坐标）
//**********************************************************
//函数名： get_xy   获取手指离开时触摸到屏幕坐标
//参数：   void     无
//返回值： int      -1打开文件失败
//**********************************************************
int tx,ty;
int ts_flag = 0;
int x0_value,y0_value;
//获取触摸屏坐标
int get_xy()
{
	int x,y;	
	int x_flag = 0;
	int y_flag = 0;
	//1.打开触摸屏驱动
	int ts_fd = open("/dev/input/event0",O_RDWR);
	if(ts_fd<0)
	{
		printf("open ts fail\n");
		return -1;
	}
	//printf("open ts ok\n");   
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
				x = ts.value;//蓝边板子
				//x = ts.value*800/1024;//黑边板子
				if(x_flag == 0)//保存起点坐标
				{
					x0_value = x;
					x_flag = 1;
				}				
			}
			 //2.判断是否是y轴事件
			if(ts.code ==  ABS_Y ) 
			{
				y = ts.value;//蓝边板子
				//y = ts.value*480/614;//黑边板子
                if(y_flag == 0)//保存起点坐标
				{
					y0_value = y;
					y_flag = 1;
				}
			}
            //printf("x %d  y %d \n",x,y);
			//printf("x0 %d  y0 %d \n",x0_value,y0_value);
		 }			 
         //2.判断手指头是否离开了屏幕
		 if(ts.type == EV_KEY && ts.code == BTN_TOUCH)
		 {
			  //离开了，保存当前的触摸坐标，跳出循环
			 if(ts.value == 0)
			 {
				 if(x - x0_value > 30)//右滑
				 {
					 printf("right floating \n");
					 ts_flag = 1;
					 break; 
				 }
				 if(x - x0_value < -30)//左滑
				 {
					 printf("left floating \n");
					 ts_flag = 2;
					 break; 
				 }	
                 if(y - y0_value > 30)//下滑
				 {
					 printf("down floating \n");
					 ts_flag = 3;
					 break; 
				 }
				 if(y - y0_value < -30)//上滑
				 {
					 printf("up floating \n");
					 ts_flag = 4;
					 break; 
				 }			 
				 tx = x;
				 ty = y;
				//  printf("tx %d  ty %d \n",tx,ty);
				 break;				 
			 }
		 }           		
	}	
	//4.关闭驱动
	close(ts_fd);	
}
