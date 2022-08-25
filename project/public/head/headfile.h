#ifndef  _HEADFILE_H_ //防止头文件被重复包含
#define  _HEADFILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/input.h>
#include <pthread.h>
#include <termios.h>
#include <dirent.h>
#include <errno.h>
#include <assert.h>
#include <netdb.h>
#include <errno.h>
#include <time.h>


#include "lcd.h"
#include "api_v4l2.h"

#include "system.h"
#include "get_xy.h"
#include "showbmp.h"
#include "loading.h"
#include "get_xy_hd.h"
#include "process_Init.h"
#include "get_real_time.h"
#include "password.h"
#include "system.h"
#include "mplayer.h"
#include "usart.h"
#include "SD_Init.h"
#include "photo.h"
#include "game.h"
#include "wifi.h"
#include "car.h"

#endif
