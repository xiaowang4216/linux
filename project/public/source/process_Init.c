#include"process_Init.h"

//1.设置任务
void *ts_thread(void *arg)
{
	while(1)
	{
		get_xy();
        usleep(10);

	}		
	  	  
}

//1.设置任务
void *system_thread(void *arg)
{
	while(1)
	{
		system_run(0);
        usleep(10);

	}		
	  	  
}

//1.设置任务
void *camera_thread(void *arg)
{
	while(1)
	{
		get_real_time();
        usleep(10);

	}		
	  	  
}

//1.设置任务
void *video_thread(void *arg)
{
	while(1)
	{
		playvideo();
        usleep(10);

	}		
	  	  
}

//1.设置任务
void *music_thread(void *arg)
{
	while(1)
	{
		playmusic();
        usleep(10);

	}		
	  	  
}

//1.设置任务
void *game_thread(void *arg)
{
	while(1)
	{
		game();
        usleep(10);

	}		
	  	  
}


//1.设置任务
void *photo_thread(void *arg)
{
	while(1)
	{
		photo_album();
        usleep(10);

	}		
	  	  
}

void *wifi_thread(void *arg)
{
	while(1)
	{
	    wifi();
        usleep(10);

	}		
	  	  
}

void *car_thread(void *arg)
{
	while(1)
	{
	    car();
        usleep(10);

	}		
	  	  
}

//**********************************************************
//函数名： process_Init   线程初始化
//参数：   void			  无
//返回值： void           无
//**********************************************************
void process_Init(void)
{
    //2.设置线程的名字
    pthread_t p1;    
    //3.创建触摸屏线程   
    pthread_create(&p1,NULL,ts_thread,NULL);
    //2.设置线程的名字
    pthread_t p2;    
    //3.创建正常运行线程   
    pthread_create(&p2,NULL,system_thread,NULL);
    //2.设置线程的名字
    pthread_t p3;    
    //3.创建监控线程   
    pthread_create(&p3,NULL,camera_thread,NULL);
    //2.设置线程的名字
    pthread_t p4;    
    //3.创建视频播放线程   
    pthread_create(&p4,NULL,video_thread,NULL);   
    //2.设置线程的名字
    pthread_t p5;    
    //3.创建音乐播放线程   
    pthread_create(&p5,NULL,music_thread,NULL); 
    //2.设置线程的名字
    pthread_t p6;    
    //3.创建游戏线程   
    pthread_create(&p6,NULL,game_thread,NULL);
    pthread_t p7;    
    //3.创建游戏线程   
    pthread_create(&p7,NULL,photo_thread,NULL);
    pthread_t p8;    
    //3.创建游戏线程   
    pthread_create(&p8,NULL,wifi_thread,NULL);
    pthread_t p9;    
    //3.创建游戏线程   
    pthread_create(&p9,NULL,car_thread,NULL);
}