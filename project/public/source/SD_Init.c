#include"SD_Init.h"

int check_sd()
{
    int file = -1;
    file = open( "/mnt/login.bmp", O_RDONLY);
    close(file);
    return file;
}

//**********************************************************
//函数名： SD_Init   检查是否挂载内存卡
//参数：   void     无
//返回值： void     无
//**********************************************************
void SD_Init(void)
{
    if (check_sd()==-1)
    {
        system("mount /dev/mmcblk1p1 /mnt");
    }
}