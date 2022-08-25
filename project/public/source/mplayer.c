#include "mplayer.h"


//视频播放状态
int video_sta;
//音乐播放状态
int music_sta;
void playvideo()
{
    if(display_lcd == display_video)
    {
        video_sta = 1;
        tx = 0;
        ty = 0;
        showbmp( "./mnt/video_begin.bmp",0,400) ;//显示提示*
        // 1.准备工作  
        system("rm /pipe");
        system("mkfifo /pipe");
        system("chmod 777 /pipe");
        video_home:
        //2.以后台方式播放视频
        system("mplayer -slave -quiet -input  file=/pipe  -geometry  0:0 -zoom -x 800 -y 400  ./mnt/dream.avi &");
        
        while(1)
        {
            if((tx>0&&tx<800&&ty>0&&ty<400)||(strcmp(rbuf, "video_on/off") == 0))//暂停、继续
            {
                bzero(rbuf, 1024);
                video_sta = ~video_sta;
                printf("video_value %d\n",video_sta);
                if(video_sta  == 1)
                {
                    showbmp( "./mnt/video_begin.bmp",0,400) ;//显示提示*
                }   
                else
                {                   
                    showbmp( "./mnt/video_pause.bmp",0,400) ;//显示提示*
                }            
                tx=0;
                ty=0;
                system("echo pause >>  /pipe");
            }     
            if((tx>340&&tx<420&&ty>400&&ty<480)||(strcmp(rbuf, "video_on/off") == 0))//暂停、继续
            {
                bzero(rbuf, 1024);
                video_sta = ~video_sta;
                if(video_sta == 1)
                {
                    showbmp( "./mnt/video_begin.bmp",0,400) ;//显示提示*
                }   
                else
                {                   
                    showbmp( "./mnt/video_pause.bmp",0,400) ;//显示提示*
                }            
                tx=0;
                ty=0;
                system("echo pause >>  /pipe");
            }  
            if((tx>530&&tx<626&&ty>400&&ty<480)||(strcmp(rbuf, "video_forward") == 0))//快进
            {
                bzero(rbuf, 1024);
                video_sta = 1;
                showbmp( "./mnt/video_begin.bmp",0,400) ;//显示提示*           
                tx=0;
                ty=0;
                system("echo seek +5 > /pipe");
            }   
            if((tx>230&&tx<320&&ty>400&&ty<480)||(strcmp(rbuf, "video_retreat") == 0))//快退
            {
                bzero(rbuf, 1024);
                video_sta = 1;
                showbmp( "./mnt/video_begin.bmp",0,400) ;//显示提示*             
                tx=0;
                ty=0;
                system("echo seek -5 > /pipe");
            }
            if((tx>437&&tx<521&&ty>400&&ty<480)||(strcmp(rbuf, "video_again") == 0))//重新开始
            {
                bzero(rbuf, 1024);
                video_sta = 0;
                tx=0;
                ty=0;
                system("killall -kill mplayer");
                goto video_home;
            }
            if((ts_flag == 3&&y0_value > 0&&y0_value <= 10)||(strcmp(rbuf, "video_exit") == 0))//退出
            {
                bzero(rbuf, 1024);
                ts_flag=0;
                tx=0;
                ty=0;
                system("killall -kill mplayer");
                showbmp("./mnt/menu.bmp",0,0);               
                display_lcd = display_menu;
                break;
            }
            if((tx>0&&tx<80&&ty>400&&ty<480)||(strcmp(rbuf, "video_exit") == 0))//退出
            {
                bzero(rbuf, 1024);
                ts_flag=0;
                tx=0;
                ty=0;
                system("killall -kill mplayer");
                showbmp("./mnt/menu.bmp",0,0);              
                display_lcd = display_menu;
                break;
            }
            
        }
    }
}


//音乐播放
void playmusic()
{
    if(display_lcd == display_music)
    {
        music_sta = 1;
        tx = 0;
        ty = 0;
        showbmp( "./mnt/music_begin.bmp",0,0) ;//显示提示*
        DIR *dirp;
        struct dirent *direntp;
        //添加寻找路径
        char *path = "./mnt";
        //存储图片路径
        char music_path[100][100];
        
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
            if(strstr(dirbuf,"mp3"))
            {
                printf("The file path is:%s\n",dirbuf);
                strcpy(music_path[i],dirbuf);
                i++;
            }
        }
        closedir(dirp);
        // 1.准备工作  
        system("rm /pipe");
        system("mkfifo /pipe");
        system("chmod 777 /pipe");
        //2.以后台方式播放视频
        system("mplayer -slave -quiet -input  file=/pipe ./mnt/1.mp3 &");
        
        char music_name[100];
        i = 0;
        while(1)
        {
            if((tx>0&&tx<800&&ty>0&&ty<400)||(strcmp(rbuf, "music_on/off") == 0))//暂停、继续
            {
                bzero(rbuf, 1024);
                music_sta = ~music_sta;
                printf("music_value %d\n",music_sta);
                if(music_sta  == 1)
                {
                    showbmp( "./mnt/music_begin.bmp",0,0) ;//显示提示*
                }   
                else
                {                   
                    showbmp( "./mnt/music_pause.bmp",0,0) ;//显示提示*
                }            
                tx=0;
                ty=0;
                system("echo pause >>  /pipe");
            }     
            if((tx>340&&tx<420&&ty>400&&ty<480)||(strcmp(rbuf, "music_on/off") == 0))//暂停、继续
            {
                bzero(rbuf, 1024);
                music_sta = ~music_sta;
                if(music_sta == 1)
                {
                    showbmp( "./mnt/music_begin.bmp",0,0) ;//显示提示*
                }   
                else
                {                   
                    showbmp( "./mnt/music_pause.bmp",0,0) ;//显示提示*
                }            
                tx=0;
                ty=0;
                system("echo pause >>  /pipe");
            }  
            if((tx>530&&tx<626&&ty>400&&ty<480)||(strcmp(rbuf, "music_down") == 0))//下一曲
            {
                bzero(rbuf, 1024);
                music_sta = 1;
                showbmp( "./mnt/music_begin.bmp",0,0) ;//显示提示* 
                i ++;
                ts_flag = 0;
                tx = 0;
                ty = 0;
                if(music_path[i] == NULL)
                {
                    i = 0;
                }
                music_home:
                system("killall -kill mplayer");
                system("rm /pipe");
                system("mkfifo /pipe");
                system("chmod 777 /pipe");
                sprintf(music_name,"mplayer -slave -quiet -input  file=/pipe %s &",music_path[i]);
                printf("order :%s",music_name);
                system((char *)music_name);
            }   
            if((tx>230&&tx<320&&ty>400&&ty<480)||(strcmp(rbuf, "music_up") == 0))//上一曲
            {
                bzero(rbuf, 1024);
                music_sta = 1;
                showbmp( "./mnt/music_begin.bmp",0,0) ;//显示提示* 
                i --;
                if(i< 0 )
                {
                    i = 0;
                }
                ts_flag = 0;
                tx = 0;
                ty = 0;
                system("killall -kill mplayer");
                system("rm /pipe");
                system("mkfifo /pipe");
                system("chmod 777 /pipe");
                sprintf(music_name,"mplayer -slave -quiet -input  file=/pipe %s &",music_path[i]);
                printf("order :%s",music_name);
                system((char *)music_name);
            }
            if((tx>630&&tx<730&&ty>400&&ty<480)||(strcmp(rbuf, "music_upvolume") == 0))//音量加
            {
                bzero(rbuf, 1024);
                music_sta = 1;
                showbmp( "./mnt/music_begin.bmp",0,0) ;//显示提示*             
                tx=0;
                ty=0;
                system("echo volume +10 >> /pipe");
            }
            if((tx>130&&tx<230&&ty>400&&ty<480)||(strcmp(rbuf, "music_downvolume") == 0))//音量减
            {
                bzero(rbuf, 1024);
                music_sta = 1;
                showbmp( "./mnt/music_begin.bmp",0,0) ;//显示提示*             
                tx=0;
                ty=0;
                system("echo volume -10 >> /pipe");
            }
            if((tx>436&&tx<526&&ty>400&&ty<480)||(strcmp(rbuf, "music_again") == 0))//重新开始
            {
                bzero(rbuf, 1024);
                music_sta = 0;
                tx=0;
                ty=0;
                system("killall -kill mplayer");
                goto music_home;
            }
            if((ts_flag == 3&&y0_value > 0&&y0_value <= 10)||(strcmp(rbuf, "music_exit") == 0))//退出
            {
                bzero(rbuf, 1024);
                ts_flag=0;
                tx=0;
                ty=0;
                system("killall -kill mplayer");
                showbmp("./mnt/menu.bmp",0,0);               
                display_lcd = display_menu;
                break;
            }
            if((tx>0&&tx<80&&ty>400&&ty<480)||(strcmp(rbuf, "music_exit") == 0))//退出
            {
                bzero(rbuf, 1024);
                ts_flag=0;
                tx=0;
                ty=0;
                system("killall -kill mplayer");
                showbmp("./mnt/menu.bmp",0,0);              
                display_lcd = display_menu;
                break;
            }
            
        }
    }

}