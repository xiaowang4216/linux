#include "usart.h"


#define BUFSIZE 1024


char *esp_order;
//配置串口参数
void init_tty(int fd)
{
	struct termios new_cfg;
	bzero(&new_cfg, sizeof(new_cfg));
	//获取串口旧的信息
	if(tcgetattr(fd, &new_cfg) != 0)
	{
		perror("tcgetattr() failed");
		exit(0);
	}

	cfmakeraw(&new_cfg);
	
	new_cfg.c_cflag |= CLOCAL | CREAD;
	
	//设置波特率为 115200
	cfsetispeed(&new_cfg, B115200); 
	cfsetospeed(&new_cfg, B115200);

	new_cfg.c_cflag &= ~CSIZE;
	new_cfg.c_cflag |= CS8;

	new_cfg.c_cflag &= ~PARENB;
	new_cfg.c_cflag &= ~CSTOPB;

	new_cfg.c_cc[VTIME] = 0;  
	new_cfg.c_cc[VMIN]  = 1;
	tcflush(fd, TCIFLUSH);
    //加载新串口参数
	if(tcsetattr(fd, TCSANOW, &new_cfg) != 0)
	{
		perror("tcsetattr() failed");
		exit(0);
	}
}

void *routine(void *arg)
{

	int fd_recv = *(int *)arg;

	char *buf= calloc(1, BUFSIZE);

	int n;
	while(1)
	{
		
		bzero(buf, BUFSIZE);

		n = read(fd_recv, buf, BUFSIZE);
		
        //读取串口信息，进行处理
		if(n > 0)
		{
			//esp_order = strtok(NULL,"@");	
			// esp_order = strtok(buf,"@");
			printf("recv: %s", buf);		
			// while(1)
			// {
				//在此处判断指令esp_order是不是你需要的,此处为模板
				//打开摄像头
				if(strncmp("camera_open",buf,sizeof("camera_open")) == 0)
				{
					printf("%s\n",esp_order);
					if(display_lcd == display_menu)
					{
						showbmp("./mnt/begin.bmp",0,0);
            			display_lcd = display_camera;

					}	
					break;				
				}
				//打开视频
				if(strcmp(esp_order, "video_open") == 0)
				{
					if(display_lcd == display_menu)
					{
						showbmp("./mnt/video_begin.bmp",0,400);
            			display_lcd = display_video;
					}					
				}
				//打开游戏
				if(strcmp(esp_order, "game_start") == 0)
				{
					if(display_lcd == display_menu)
					{
						showbmp("./mnt/game_begin.bmp",0,0);
            			display_lcd = display_game;
					}					
				}
				//打开音乐
				if(strcmp(esp_order, "music_open") == 0)
				{
					if(display_lcd == display_menu)
					{
						showbmp("./mnt/music_begin.bmp",0,0);
            			display_lcd = display_music;
					}					
				}
				//打开相册
				if(strcmp(esp_order, "Photo_open") == 0)
				{
					if(display_lcd == display_menu)
					{
						printf("esp video start ok\n");
						showbmp("./mnt/begin.bmp",0,0);
            			display_lcd = display_video;
					}					
				}   		
				
			//}
		}
        usleep(1);
	}

}

//与esp8266通信
int esp_usart_init()
{
    //1.选择通信串口
	char *tty = "/dev/ttySAC1";
    //2.打开对应的串口驱动
	int fd_recv = open(tty, O_RDWR|O_NOCTTY);
    if(fd_recv == -1)
	{
        printf("open %s fail\n",tty);
		return -1;
	}
	printf("tty open ok !\n");
    //3.配置串口参数
	init_tty(fd_recv);
    //4.通过串口实现通信
	// ============ 独立线程读取串口信息uart1  ============== //
	pthread_t tid;
	pthread_create(&tid, NULL, routine, (void *)&fd_recv);

}



