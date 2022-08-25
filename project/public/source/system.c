#include "system.h"


int display_lcd = 0;


//1.设置任务函数
void system_run(void *arg)
{
    //读取内存卡路径下图片
    start: 
    showbmp("./mnt/login.bmp",0,0);
    sleep(1);
    display_lcd = display_login;
    ts_flag = 0;
	while(1)
	{	
        //点击登录	
		if(211<=tx&&tx<=572&&83<=ty&&ty<=431&&display_lcd == display_login)
        {
            showbmp("./mnt/loading.bmp",0,0);
            loading(600,40,100,330,1000,160,122,255,0);
            user();
        }
        //打开摄像头界面
        if(tx>0&&tx<133&&ty>0&&ty<=100&&display_lcd == display_menu)
        {
            showbmp("./mnt/begin.bmp",0,0);
            display_lcd = display_camera;

        }
        //打开视频界面
        if(tx>158&&tx<284&&ty>0&&ty<=100&&display_lcd == display_menu&&user_id == admin_user)
        {
            showbmp("./mnt/video_begin.bmp",0,400);
            display_lcd = display_video;

        }
        //打开音乐界面
        if(tx>490&&tx<590&&ty>0&&ty<=100&&display_lcd == display_menu)
        {
            showbmp("./mnt/music_begin.bmp",0,0);
            display_lcd = display_music;

        }
        //打开游戏界面
        if(tx>300&&tx<470&&ty>0&&ty<=100&&display_lcd == display_menu)
        {
            showbmp("./mnt/game_begin.bmp",0,0);
            display_lcd = display_game;

        }
        //打开相册界面
        if(tx>600&&tx<700&&ty>0&&ty<=100&&display_lcd == display_menu)
        {
            showbmp("./mnt/game_begin.bmp",0,0);
            display_lcd = display_photo;
        }
        //打开车库管理界面
        if(tx>0&&tx<137&&ty>136&&ty<=217&&display_lcd == display_menu)
        {
            showbmp("./mnt/car_begin.bmp",0,0);
            display_lcd = display_car;
        }
        
        // if(35<=tx&&tx<=115&&20<=ty<=50&&display_lcd == display_back)
        // {
        //     goto start;
        // }

        //右滑关机
        // if(ts_flag == 1&&x0_value <= 10&&x0_value > 0)
        // {
        //     clear_lcd();
        //     printf("power off");
        //     ts_flag == 0;
        //     tx = 0;
        //     ty = 0;
        //     exit(0);
        // }
        //左滑返回上级菜单
        if(ts_flag == 2&&x0_value >= 790&&display_lcd == display_menu)
        {
            ts_flag == 0;
            tx = 0;
            ty = 0;
            goto start;
        }
        usleep(1);
	}		
	  	  
}