#ifndef  _SYSTEM_H_ //防止头文件被重复包含
#define  _SYSTEM_H_

#include"headfile.h"

void system_run(void *arg);

#define display_login  1   //登录界面
#define display_back   2   //
#define display_menu   3
#define display_camera 4   //摄像头界面
#define display_video  5   //视频播放界面
#define display_music  6   //音乐播放界面
#define display_game   7   //游戏界面
#define display_photo  8   //相册界面
#define display_car    9   //车库管理面


//屏幕控制
extern int display_lcd;


#endif