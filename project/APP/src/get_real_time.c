#include"get_real_time.h"

FrameBuffer freambuf;

//**********************************************************
//函数名： get_real_time   摄像头操作函数
//参数：   void		 无
//返回值： void      无
//**********************************************************
void get_real_time(void)
{
	//如果打开了摄像头界面
	if(display_lcd == display_camera)
	{
		int jpg_fd;
	
		/* 打开LCD屏幕*/
		lcd_open();
		
		/* 初始化摄像头设备*/
		linux_v4l2_device_init("/dev/video0");
		
		/* 启动摄像头*/
		linux_v4l2_start_capturing();
		printf("camera ok !\n");
		//重新打开摄像头
		camera_start:
		while(1)
		{		
			// 实时监控
			/* 获取摄像头数据      存放jpg文件流*/
			linux_v4l2_get_fream(&freambuf);
				
			/* 显示摄像头图像*/
			lcd_draw_jpg(0, 0, NULL, freambuf.buf, freambuf.length, 0);
			if((tx > 688&&tx<800&&ty>0&&ty<117&&user_id==admin_user)||((strcmp(rbuf, "camera_snap") == 0)&&user_id==admin_user))//抓拍
			{	
				bzero(rbuf, 1024);
				tx = 0;
				ty = 0;		
				//2.??????????jpg???
				system("touch 1.jpg");
				//3.??jpg???
				jpg_fd = open("1.jpg",O_RDWR);
				
				if(jpg_fd < 0)
				{
					printf("open jpg fail\n");
					continue;
				}
				printf("open jpg ok\n");
				//4.???????????д??jpg???
				write(jpg_fd,freambuf.buf,freambuf.length);
				//5.???jpg???
				close(jpg_fd);
				printf("take photo ok\n");
			}
			if((tx > 679&&tx<800&&ty>133&&ty<240&&user_id==admin_user)||((strcmp(rbuf, "camera_echo") == 0)&&user_id==admin_user))//回显
			{
				bzero(rbuf, 1024);
				tx = 0;
				ty = 0;	
				lcd_draw_jpg(0, 0,"1.jpg",NULL, freambuf.length, 0);
				while(1)
				{
					if((tx > 679&&tx<774&&ty>263&&ty<322)||(strcmp(rbuf, "camera_pause") == 0))//暂停
					{
						bzero(rbuf, 1024);
						showbmp("./mnt/stop1.bmp",640,0);
						tx = 0;
						ty = 0;
						break;
					}
					if((tx > 679&&tx<774&&ty>364&&ty<472)||(strcmp(rbuf, "camera_play") == 0))//继续
					{
						bzero(rbuf, 1024);
						tx = 0;
						ty = 0;
						showbmp("./mnt/begin.bmp",0,0);
						printf("camera exit\n");
						while(1)
						{
							if(tx > 679&&tx<774&&ty>364&&ty<472)//????
							{
								tx = 0;
								ty = 0;
								goto camera_start;
							}
						}
					}
				}
			}
			if((tx > 688&&tx<800&&ty>259&&ty<368)||(strcmp(rbuf, "camera_pause") == 0))//暂停
			{
				bzero(rbuf, 1024);
				tx = 0;
				ty = 0;
				showbmp("./mnt/stop1.bmp",640,0);
				while(1)
				{
					if((tx > 688&&tx<800&&ty>259&&ty<368)||(strcmp(rbuf, "camera_play") == 0))//继续
					{
						bzero(rbuf, 1024);
						showbmp("./mnt/begin.bmp",0,0);
						tx = 0;
						ty = 0;
						break;
					}
				}
			}
			
			if((tx > 688&&tx<800&&ty>380&&ty<480)||(strcmp(rbuf, "camera_exit") == 0))//关闭摄像头
			{
				bzero(rbuf, 1024);
				tx = 0;
				ty = 0;
				showbmp("./mnt/menu.bmp",0,0);
				printf("camera exit\n");     
				display_lcd = display_menu;
				break;          
			}	
			if((ts_flag == 3&&y0_value > 0&&y0_value <= 10)||(strcmp(rbuf, "camera_exit") == 0))//退出
            {
				bzero(rbuf, 1024);
				ts_flag=0;
                tx = 0;
				ty = 0;
				showbmp("./mnt/menu.bmp",0,0);
				printf("camera exit\n");     
				display_lcd = display_menu;
				break;
            }				
		}
			/* 停止摄像头*/
	linux_v4l2_stop_capturing();
	
	/* 卸载摄像头*/
	linux_v4l2_device_uinit();
	}
	
	
}