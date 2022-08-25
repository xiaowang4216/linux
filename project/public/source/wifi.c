#include "wifi.h"


//串口宏定义
#define DEV_PATH1   "/dev/ttySAC1"
#define DEV_PATH2   "/dev/ttySAC2"
#define DEV_PATH3   "/dev/ttySAC3"

int fd_send;
char rbuf[1024];
// void init_tty(int fd)
// {
// 	struct termios new_cfg;
// 	bzero(&new_cfg, sizeof(new_cfg));
	
// 	if(tcgetattr(fd, &new_cfg) != 0)
// 	{
// 		perror("tcgetattr() failed");
// 		exit(0);
// 	}

// 	cfmakeraw(&new_cfg);
	
// 	new_cfg.c_cflag |= CLOCAL | CREAD;
	
// 	cfsetispeed(&new_cfg, B115200);
// 	cfsetospeed(&new_cfg, B115200);

// 	new_cfg.c_cflag &= ~CSIZE;
// 	new_cfg.c_cflag |= CS8;

// 	new_cfg.c_cflag &= ~PARENB;
// 	new_cfg.c_cflag &= ~CSTOPB;

// 	new_cfg.c_cc[VTIME] = 0;  
// 	new_cfg.c_cc[VMIN]  = 1;
// 	tcflush(fd, TCIFLUSH);

// 	if(tcsetattr(fd, TCSANOW, &new_cfg) != 0)
// 	{
// 		perror("tcsetattr() failed");
// 		exit(0);
// 	}
// }

void *routine_thread(void *arg)
{

	int fd_recv = *(int *)arg;

	//char rbuf[1024];

	int n;
	while(1)
	{
		n = read(fd_recv, rbuf, 1024);
		if(n <20)
		{
			fprintf(stderr, "recv: %s", rbuf);
			//打开摄像头
			if(strcmp(rbuf, "camera_open") == 0)
			{
				if(display_lcd == display_menu)
				{
					showbmp("./mnt/begin.bmp",0,0);
					display_lcd = display_camera;
					bzero(rbuf, 1024);

				}					
			}
			//打开视频
			if(strcmp(rbuf, "video_open") == 0)
			{
				if(display_lcd == display_menu)
				{
					showbmp("./mnt/video_begin.bmp",0,400);
					display_lcd = display_video;
					bzero(rbuf, 1024);
				}					
			}
			//打开游戏
			if(strcmp(rbuf, "game_start") == 0)
			{
				if(display_lcd == display_menu)
				{
					showbmp("./mnt/game_begin.bmp",0,0);
					display_lcd = display_game;
					bzero(rbuf, 1024);
				}					
			}
			//打开音乐
			if(strcmp(rbuf, "music_open") == 0)
			{
				if(display_lcd == display_menu)
				{
					showbmp("./mnt/music_begin.bmp",0,0);
					display_lcd = display_music;
					bzero(rbuf, 1024);
				}					
			}
			//打开相册
			if(strcmp(rbuf, "photo_open") == 0)
			{
				if(display_lcd == display_menu)
				{
            		showbmp("./mnt/game_begin.bmp",0,0);
            		display_lcd = display_photo;
					bzero(rbuf, 1024);
				}					
			}

/* 			if(strncmp("1.bmp",rbuf,5)==0)
			{
				showbmp("1.bmp",0,0);
			} */
		}
	}

}

char *menu(void)
{
	printf("1: /dev/ttySAC1\n");
	printf("2: /dev/ttySAC2\n");
	printf("3: /dev/ttySAC3\n");
	printf("4: /dev/ttySAC4\n");

	int n;
	scanf("%d", &n);

	switch(n)
	{
	case 1: return "/dev/ttySAC1";	
	case 2: return "/dev/ttySAC2";	
	case 3: return "/dev/ttySAC3";	
	case 4: return "/dev/ttySAC4";	
	}

	return NULL;
}
int ESP8266_SendCmd(char *cmd)
{


    write(fd_send, (unsigned char *)cmd, strlen((const char *)cmd));
     

	
	return 1;

}
int Esp8266_Init()
{
    //测试指令 
	printf("1. AT\r\n");
	ESP8266_SendCmd("AT\r\n");
	sleep(1);
	//设置ast模式
	printf("2. AT+CWMODE=1\r\n");
    ESP8266_SendCmd("AT+CWMODE=1\r\n");
	sleep(3);
    //重启生效	
	printf("3 AT+RST\r\n");
    ESP8266_SendCmd("AT+RST\r\n");
	sleep(3);
    //连接wifi热点
	printf("3. ESP8266_AP_INFO\r\n");
	ESP8266_SendCmd(ESP8266_AP_INFO);
    sleep(10) ;
	//连接tcp服务器
    printf("4.AT+CIPSTART=\"TCP\"\n ");    
	ESP8266_SendCmd(SERVER_INFO);
    sleep(10);
    //开启透传模式
	printf("5. AT+CIPMODE=1\r\n");
    ESP8266_SendCmd("AT+CIPMODE=1\r\n");
	sleep(5);
    //开始透传
    printf("6.AT+CIPSEND\r\n");
    ESP8266_SendCmd("AT+CIPSEND\r\n");
	sleep(5);
	
	printf("7. ESP8266 Init OK\r\n");
    return 0;
}

int wifi(void)
{
	// GEC6818默认串口名称：/dev/ttySACx
	char *tty_send;
	char *tty_recv;


	tty_send = DEV_PATH1;

	tty_recv = DEV_PATH1;

	// 打开指定的串口设备节点，并初始化
	 fd_send = open(tty_send, O_RDWR|O_NOCTTY);
	if(fd_send == -1)
	{
		fprintf(stderr, "open() %s failed: %s\n",
				tty_send, strerror(errno));
		exit(0);
	}

	int fd_recv = open(tty_recv, O_RDWR|O_NOCTTY);
	if(fd_recv == -1)
	{
		fprintf(stderr, "open() %s failed: %s\n",
				tty_recv, strerror(errno));
		exit(0);
	}
	init_tty(fd_send);
	init_tty(fd_recv);
	sleep(1);
	Esp8266_Init();
	
     
	// ============ 独立线程读取串口信息 from server ============== //
    pthread_t tid;
	pthread_create(&tid, NULL, routine_thread, (void *)&fd_recv);
    

	// ============ 主线程发送串口信息 to client ============ //
    char buf[1024];
	while(1)
	{
		bzero(buf, BUFSIZE);
		fgets(buf, BUFSIZE, stdin);
        
		write(fd_send, buf, strlen(buf));
	}
     
	return 0;
}
