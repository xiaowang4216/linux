#ifndef  _WIFI_H_ //防止头文件被重复包含
#define  _WIFI_H_

#include"headfile.h"

#define BUFSIZE 1024
#define ESP8266_AP_INFO      "AT+CWJAP=\"S6411_2.4G\",\"s6411s6411\"\r\n"           //wifi热点信息
#define SERVER_INFO          "AT+CIPSTART=\"TCP\",\"192.168.1.161\",10000\r\n" //tcp服务器信息

extern char rbuf[1024];
extern void *routine_thread(void *arg);
extern int wifi(void);

#endif