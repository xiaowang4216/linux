#ifndef  _USART_H_ //防止头文件被重复包含
#define  _USART_H_

#include"headfile.h"

void *routine(void *arg);

extern char *esp_order;

extern void init_tty(int fd);
int esp_usart_init();

#endif