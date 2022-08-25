#ifndef __PASSWORD_H__
#define __PASSWORD_H__
#include"headfile.h"
//使用者身份
extern int user_id;
//普通用户
#define general_user 1
//管理员用户
#define admin_user   2

//用户身份选择界面
int user();
//输入密码
int get_passworld();

//管理员登录
int adm_login();



#endif