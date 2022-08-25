#include "car.h"

static struct timeval timeout;
int g_buz;

#define DEV_PATH1   "/dev/ttySAC1"
#define DEV_PATH2   "/dev/ttySAC2"
#define DEV_PATH3   "/dev/ttySAC3"

/* 设置窗口参数:9600速率 */
void init_ttty(int fd)
{    
	//声明设置串口的结构体
	struct termios termios_new;
	//先清空该结构体
	bzero( &termios_new, sizeof(termios_new));

	cfmakeraw(&termios_new);

	//设置波特率
	cfsetispeed(&termios_new, B9600);
	cfsetospeed(&termios_new, B9600);

	// CLOCAL和CREAD分别用于本地连接和接受使能
	// 首先要通过位掩码的方式激活这两个选项。    
	termios_new.c_cflag |= CLOCAL | CREAD;

	//通过掩码设置数据位为8位
	termios_new.c_cflag &= ~CSIZE;
	termios_new.c_cflag |= CS8; 

	//设置无奇偶校验
	termios_new.c_cflag &= ~PARENB;

	//一位停止位
	termios_new.c_cflag &= ~CSTOPB;

	// 可设置接收字符和等待时间，无特殊要求可以将其设置为0
	termios_new.c_cc[VTIME] = 0;
	termios_new.c_cc[VMIN] = 1;

	// 用于清空输入/输出缓冲区
	tcflush (fd, TCIFLUSH);

	//完成配置后，可以使用以下函数激活串口设置
	if(tcsetattr(fd, TCSANOW, &termios_new))
		printf("Setting the serial1 failed!\n");

}


/*计算校验和*/
unsigned char CalBCC(unsigned char *buf, int n)
{
	int i;
	unsigned char bcc=0;
	for(i = 0; i < n; i++)
	{
		bcc ^= *(buf+i);
	}
	return (~bcc);
}

void beep(int buz, float microsec)
{
	ioctl(buz, 0, 1);
	usleep(microsec * 1000*1000);
	ioctl(buz, 1, 1);
}

int space_num = 12;//车位数
int car_num  =0; //已有车辆数
int money = 2;// 1秒5块
int sum_money = 0;//停车费用
//int time = 0;//停车时间

int show_num(int num,int x0,int y0)//num 1 01    10  10
{
	//获取num的十位和个位的数
	int a = num /10 ;//十位
	int b = num %10 ;//个位
	//显示数字
	char numbmp[128];
	bzero(numbmp,128);
	
	sprintf(numbmp,"./mnt/%d.bmp",a);
	showbmp(numbmp,x0,y0);//显示十位
	
	sprintf(numbmp,"./mnt/%d.bmp",b);
	showbmp(numbmp,x0+32,y0);//显示个位
}
int show_car_space_info()
{
	//显示车位
	show_num(space_num,150,145);
	//显示单价
	show_num(money,150,250);
	//显示状态 待机  入库  出库
	
	
	
}
int temp_time = 0;
int parking_time[2];
int car(void)
{
	if(display_lcd == display_car)
	{
		//显示主界面
		//showbmp();
		//显示车库的初始化数据
		
		// 初始化串口
		int fd = open(DEV_PATH2, O_RDWR | O_NOCTTY);
		init_ttty(fd);//配置串口参数 波特率 9600
		// 打开蜂鸣器
		g_buz = open("/dev/beep", O_RDWR);

		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		char WBuf[7], RBuf[128];
		char KBuf[8];

		bzero(WBuf, 7);
		WBuf[0] = 0x07;	//帧长= 7 Byte
		WBuf[1] = 0x02;	//包号= 0 , 命令类型= 0x01
		WBuf[2] = 'A';	//命令= 'A'，检测卡片
		WBuf[3] = 0x01;	//信息长度 = 1
		WBuf[4] = 0x52;	//请求模式:  ALL=0x52
		WBuf[5] = CalBCC(WBuf, WBuf[0]-2); //校验和
		WBuf[6] = 0x03; //结束标志

		fprintf(stderr, "Detecting pictures");
		int count = 0;
		
		bzero(KBuf, 8);
		KBuf[0] = 0x08;	//帧长= 8 Byte
		KBuf[1] = 0x02;	//包号= 0 , 命令类型= 0x01
		KBuf[2] = 'B';	//命令= 'B'
		KBuf[3] = 0x02;	//信息长度= 2
		KBuf[4] = 0x93;	//防碰撞0x93: 一级防碰撞
		KBuf[5] = 0x00;	//位计数0
		KBuf[6] = CalBCC(KBuf, KBuf[0]-2); //校验和
		KBuf[7] = 0x03;	//结束标志
		
		int cardid = 0;
		int bufid = 0;
		int q = 12;
		int w = 2;
	
		show_num(q,140,253);//车位数
		//show_num(q-1,140,253);
		//显示价格
		show_num(w,140,323);
		//按键检测
		tx = 0;
		ty = 0;
		ts_flag = 0;
		//等待选择出库还是其他选择
		start:
		while(1)
		{
			temp_time ++;
			sleep(1);
			if(tx<168&&tx>0&&ty>0&&ty<49)//点击入库
			{
				tx = 0;
				ty = 0;
				ts_flag = 0;
				showbmp("./mnt/enter.bmp",140,288);
				while(1)
				{
					while(1)
					{
						// 向串口发送指令
						tcflush(fd, TCIFLUSH);
						write(fd, WBuf, 7);

						usleep(10*1000);

						bzero(RBuf, 128);
						read(fd, RBuf, 128);

						//应答帧状态部分为0 则请求成功
						if(RBuf[2] == 0x00)	
						{
							printf("\nAcquire RFID card information successfully[%d]: ", RBuf[3]);

							int i;
							for(i=0; i<RBuf[3]; i++)
							{
								printf("%c", RBuf[4+i]);
							}
							printf("\n");
							break;
							
							
						}
						else
						{
							if(count%10 == 0)
							{
								fprintf(stderr, ".");
							}
							count++;
							usleep(100*1000);
						}
					}

					// 向串口发送指令
					tcflush (fd, TCIFLUSH);
					write(fd, KBuf, 8);

					usleep(10*1000);

					bzero(RBuf, 128);
					read(fd, RBuf, 128);

					//应答帧状态部分为0 则成功
					
					if(RBuf[2] == 0x00) 
					{
						int i, j;
						for(i=RBuf[3]-1, j=0; i>=0; i--, j++)
						{
							memcpy((char *)&cardid+j, &RBuf[4+i], 1);
						}
					}
					else
					{
						printf("获取卡号失败.\n");
						continue;
						//exit(0);
					}
					
					printf("卡号: %#x\n", cardid);	
					//入库
					if(cardid != bufid)
					{
						bufid = cardid;
						showbmp("./mnt/red.bmp",6,58);
						showbmp("./mnt/car_wait.bmp",140,288);
						show_num(--q,140,253);//车位数
						beep(g_buz, 0.5); // 长哔一声表示成功
						parking_time[0] = temp_time;
						goto start;
					}
				}									
			}
			if(tx<175&&tx>0&&ty>430&&ty<480)//点击出库
			{
				tx = 0;
				ty = 0;
				ts_flag = 0;
				showbmp("./mnt/out.bmp",140,288);
				while(1)
				{
					while(1)
					{
						// 向串口发送指令
						tcflush(fd, TCIFLUSH);
						write(fd, WBuf, 7);

						usleep(10*1000);

						bzero(RBuf, 128);
						read(fd, RBuf, 128);

						//应答帧状态部分为0 则请求成功
						if(RBuf[2] == 0x00)	
						{
							printf("\nAcquire RFID card information successfully[%d]: ", RBuf[3]);

							int i;
							for(i=0; i<RBuf[3]; i++)
							{
								printf("%c", RBuf[4+i]);
							}
							printf("\n");
							break;							
						}
						else
						{
							if(count%10 == 0)
							{
								fprintf(stderr, ".");
							}
							count++;
							usleep(100*1000);
						}
					}

					// 向串口发送指令
					tcflush (fd, TCIFLUSH);
					write(fd, KBuf, 8);

					usleep(10*1000);

					bzero(RBuf, 128);
					read(fd, RBuf, 128);

					//应答帧状态部分为0 则成功
					
					if(RBuf[2] == 0x00) 
					{
						int i, j;
						for(i=RBuf[3]-1, j=0; i>=0; i--, j++)
						{
							memcpy((char *)&cardid+j, &RBuf[4+i], 1);
						}
					}
					else
					{
						printf("获取卡号失败.\n");
						continue;
						//exit(0);
					}
					
					printf("卡号: %#x\n", cardid);	
					//出库
					if(cardid == bufid)
					{
						showbmp("./mnt/green.bmp",6,58);
						show_num(++q,140,253);//车位数
						parking_time[1] = temp_time;
						temp_time = parking_time[1] - parking_time[0];
						show_num(temp_time,139,359);//停车时间
						show_num(temp_time*w,140,396);//停车费用
						temp_time = 0;
						beep(g_buz, 0.1); usleep(50*1000);
						beep(g_buz, 0.1);
						cardid = 1;
						bufid = 2;
						goto start;
						
					}
				}									
			}
			if(tx<800&&tx>680&&ty>400&&ty<480)//点击退出
			{
				tx = 0;
				ty = 0;
				ts_flag = 0;
				close(fd);
				showbmp("./mnt/menu.bmp",0,0);
				display_lcd = display_menu;
				break;


			}
		}
		//close(fd);
	}
	// ======================================	
	//exit(0);
}
