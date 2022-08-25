#include "photo.h"



//相册功能
void photo_album()
{
    start:
    //如果进入了相册界面
    if(display_lcd == display_photo)
    {
        //显示相册界面背景
        showbmp("./mnt/mypic/1.bmp",0,0);
        DIR *dirp;
        struct dirent *direntp;
        //添加寻找路径
        char *path = "./mnt/mypic";
        //存储图片路径
        char photo_path[100][100];
        
        int i = 0;
    
        if((dirp=opendir(path))==NULL)
        {
            printf("Open Directory %s Error: %s\n", path, strerror(errno));
            exit(1);
        }
    
        while((direntp=readdir(dirp))!=NULL) 
        {
            /* 给文件或目录名添加路径:argv[1]+"/"+direntp->d_name */
            char dirbuf[512]; 
            memset(dirbuf,0,sizeof(dirbuf)); 
            strcpy(dirbuf,path); 
            strcat(dirbuf,"/"); 
            strcat(dirbuf,direntp->d_name);
                    
            if(strstr(dirbuf,"bmp"))
            {
                printf("The file path is:%s\n",dirbuf);
                strcpy(photo_path[i],dirbuf);
                i++;
            }
        }
        closedir(dirp);
        //开始显示图片
        //char bmp_name[100];
        //sprintf(bmp_name,"./mnt/myfile/%s",photo_path[i]);
        showbmp((char *)photo_path[i],0,0);
        while(1)
        {
            //一直显示,直到没有图片
            while(photo_path[i])
            {
                //如果右滑,显示下一张图片
                if((ts_flag == 1)||(strcmp(rbuf, "photo_up") == 0))
                {
                    bzero(rbuf, 1024);
                    i++;
                    //sprintf(bmp_name,"./mnt/myfile/%s",photo_path[i]);
                    showbmp((char *)photo_path[i],0,0);
                    ts_flag = 0;
                    tx = 0;
                    ty = 0;

                }
                //如果左滑,显示上一张图片
                if((ts_flag == 2)||(strcmp(rbuf, "photo_down") == 0))
                {
                    bzero(rbuf, 1024);
                    i--;
                    if(i == 0)
                    {
                        i = 0;
                    }
                    //sprintf(bmp_name,"./mnt/myfile/%s",photo_path[i]);
                    showbmp((char *)photo_path[i],0,0);
                    //如果是第一张图片.就显示第一张                   
                    ts_flag = 0;
                    tx = 0;
                    ty = 0;
                }
                //如果下滑,返回主菜单
                if((ts_flag == 3&&y0_value > 0&&y0_value <= 10)||(strcmp(rbuf, "photo_exit") == 0))//退出相册
                {
                    bzero(rbuf, 1024);
                    ts_flag=0;
                    tx=0;
                    ty=0;
                    showbmp("./mnt/menu.bmp",0,0);               
                    display_lcd = display_menu;
                    goto start;
                }
            }
        }
    }
}


