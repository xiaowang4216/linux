#include "game.h"


int data[3][3];

int game()
{   start:
    if(display_lcd==display_game)
    {
        int num,num_copy,jsq = 0;
        // 1.准备工作 
        system("rm /pipe");
        system("mkfifo /pipe");
        system("chmod 777 /pipe");
        //2.以后台方式播放视频
        system("mplayer -slave -quiet -input  file=/pipe  -geometry  0:0 -zoom -x 800 -y 480  ./mnt/game_start.avi");
    
        //显示启动按钮
        showbmp("./mnt/game_start.bmp",0,0);
        
        
        //循环检测是否点击了按钮区域
        while(1)
        {
            if((tx<720&&tx>600&&ty<430&&ty>370)||(strcmp(rbuf, "game_start") == 0))
            {
                bzero(rbuf, 1024);
                //坐标清零
                tx=0;
                ty=0;
                break;
            }
            if(ts_flag == 3&&y0_value > 0&&y0_value <= 10)//退出
            {
                ts_flag=0;
                tx=0;
                ty=0;
                showbmp("./mnt/menu.bmp",0,0);               
                display_lcd = display_menu;
                goto start;
            }
            
        }

        //显示启动背景
        showbmp("./mnt/game_loading.bmp",0,0);
        //显示进度条
        loading(700,10,40,456,2000,0,200,200,100);
        again:
        //初始化变量
        num = 0;
        num_copy= 0;
	    jsq = 0;

        //初始化游戏数据
	    for (int i = 0; i < 3; i++)
	    {
		    for (int j = 0; j < 3; j++)
		    {
			    jsq++;
			    data[i][j]=jsq;
		    }
		
	    }

        //显示主界面	
        showbmp("./mnt/game_work.bmp",0,0);
        while(1)
        {           
            if(tx<137&&tx>37&&ty<122&&ty>22&&data[0][0]==1)//1
            {
                //记录总点击次数
                num_copy++;
                //点击次数记录
                num++;
                //坐标清零
                tx=0;
                ty=0;
                if(num==1)
                {
                    showbmp("./mnt/quan.bmp",47,32);
                    //52 124
                }
                else if(num==2)
                {
                    showbmp("./mnt/cha.bmp",47,32);
                    
                }
                
                data[0][0] = num+20;
                if((data[0][0]==data[0][1]&&data[0][1]==data[0][2])||(data[0][0]==data[1][0]&&data[1][0]==data[2][0])||(data[0][0]==data[1][1]&&data[1][1]==data[2][2])||(data[2][2]==data[2][1]&&data[2][1]==data[2][0])||(data[2][2]==data[1][2]&&data[1][2]==data[0][2])||(data[0][2]==data[1][1]&&data[1][1]==data[2][0])||(data[0][1]==data[1][1]&&data[1][1]==data[2][1])||(data[1][0]==data[1][1]&&data[1][1]==data[1][2]))
                {
                    //显示胜利图片
                    showbmp("./mnt/game_win.bmp",420,0);
                    //选择继续还是退出
                    while (1)
                    {
                        if(tx<520&&tx>420&&ty<250&&ty>150)
                        {
                            tx=0;
                            ty=0;
                            goto again;
                        }
                        if (tx<520&&tx>420&&ty<350&&ty>250)
                        {
                            tx=0;
                            ty=0;
                            showbmp("./mnt/menu.bmp",0,0);               
                            display_lcd = display_menu;
                            goto start;
                        }  
                    }
                }
            }
        

            if(tx<273&&tx>173&&ty<116&&ty>16&&data[0][1]==2)//2
            {
                //记录总点击次数
                num_copy++;
                //点击次数记录
                num++;
                //坐标清零
                tx=0;
                ty=0;
                if(num==1)
                {
                    showbmp("./mnt/quan.bmp",173,26);
                    
                }
                else if(num==2)
                {
                    showbmp("./mnt/cha.bmp",173,26);
                    
                }
                data[0][1] = num+20;
                if((data[0][0]==data[0][1]&&data[0][1]==data[0][2])||(data[0][0]==data[1][0]&&data[1][0]==data[2][0])||(data[0][0]==data[1][1]&&data[1][1]==data[2][2])||(data[2][2]==data[2][1]&&data[2][1]==data[2][0])||(data[2][2]==data[1][2]&&data[1][2]==data[0][2])||(data[0][2]==data[1][1]&&data[1][1]==data[2][0])||(data[0][1]==data[1][1]&&data[1][1]==data[2][1])||(data[1][0]==data[1][1]&&data[1][1]==data[1][2]))
                {
                    //显示胜利图片
                    showbmp("./mnt/game_win.bmp",420,0);
                    //选择继续还是退出
                    while (1)
                    {
                        if(tx<520&&tx>420&&ty<250&&ty>150)
                        {
                            tx=0;
                            ty=0;
                            goto again;
                        }
                        if (tx<520&&tx>420&&ty<350&&ty>250)
                        {
                            tx=0;
                            ty=0;
                            showbmp("./mnt/menu.bmp",0,0);               
                            display_lcd = display_menu;
                            goto start;
                        }  
                    }
                }
            }

            if(tx<411&&tx>311&&ty<113&&ty>13&&data[0][2]==3)//3
            {
                //记录总点击次数
                num_copy++;
                //点击次数记录
                num++;
                //坐标清零
                tx=0;
                ty=0;
                if(num==1)
                {
                    showbmp("./mnt/quan.bmp",301,28);
                    
                }
                else if(num==2)
                {
                    showbmp("./mnt/cha.bmp",301,28);
                    
                }
                data[0][2] = num+20;
            if((data[0][0]==data[0][1]&&data[0][1]==data[0][2])||(data[0][0]==data[1][0]&&data[1][0]==data[2][0])||(data[0][0]==data[1][1]&&data[1][1]==data[2][2])||(data[2][2]==data[2][1]&&data[2][1]==data[2][0])||(data[2][2]==data[1][2]&&data[1][2]==data[0][2])||(data[0][2]==data[1][1]&&data[1][1]==data[2][0])||(data[0][1]==data[1][1]&&data[1][1]==data[2][1])||(data[1][0]==data[1][1]&&data[1][1]==data[1][2]))
                {
                    //显示胜利图片
                    showbmp("./mnt/game_win.bmp",420,0);
                    //选择继续还是退出
                    while (1)
                    {
                        if(tx<520&&tx>420&&ty<250&&ty>150)
                        {
                            tx=0;
                            ty=0;
                            goto again;
                        }
                        if (tx<520&&tx>420&&ty<350&&ty>250)
                        {
                            tx=0;
                            ty=0;
                            showbmp("./mnt/menu.bmp",0,0);               
                            display_lcd = display_menu;
                            goto start;
                        }  
                    }
                }
            }

            
            if(tx<140&&tx>40&&ty<256&&ty>156&&data[1][0]==4)//4
            {
                //记录总点击次数
                num_copy++;
                //点击次数记录
                num++;
                //坐标清零
                tx=0;
                ty=0;
                if(num==1)
                {
                    showbmp("./mnt/quan.bmp",40,156);
                    
                }
                else if(num==2)
                {
                    showbmp("./mnt/cha.bmp",40,156);
                    
                }
                data[1][0] = num+20;
            if((data[0][0]==data[0][1]&&data[0][1]==data[0][2])||(data[0][0]==data[1][0]&&data[1][0]==data[2][0])||(data[0][0]==data[1][1]&&data[1][1]==data[2][2])||(data[2][2]==data[2][1]&&data[2][1]==data[2][0])||(data[2][2]==data[1][2]&&data[1][2]==data[0][2])||(data[0][2]==data[1][1]&&data[1][1]==data[2][0])||(data[0][1]==data[1][1]&&data[1][1]==data[2][1])||(data[1][0]==data[1][1]&&data[1][1]==data[1][2]))
                {
                    //显示胜利图片
                    showbmp("./mnt/game_win.bmp",420,0);
                    //选择继续还是退出
                    while (1)
                    {
                        if(tx<520&&tx>420&&ty<250&&ty>150)
                        {
                            tx=0;
                            ty=0;
                            goto again;
                        }
                        if (tx<520&&tx>420&&ty<350&&ty>250)
                        {
                            tx=0;
                            ty=0;
                            showbmp("./mnt/menu.bmp",0,0);               
                            display_lcd = display_menu;
                            goto start;
                        }  
                    }
                }
            }

            
            if(tx<276&&tx>176&&ty<249&&ty>149&& data[1][1]==5)//5
            {
                //记录总点击次数
                num_copy++;
                //点击次数记录
                num++;
                //坐标清零
                tx=0;
                ty=0;
                if(num==1)
                {
                    showbmp("./mnt/quan.bmp",176,149);
                    
                }
                else if(num==2)
                {
                    showbmp("./mnt/cha.bmp",176,149);
                    
                }
                data[1][1] = num+20;
            if((data[0][0]==data[0][1]&&data[0][1]==data[0][2])||(data[0][0]==data[1][0]&&data[1][0]==data[2][0])||(data[0][0]==data[1][1]&&data[1][1]==data[2][2])||(data[2][2]==data[2][1]&&data[2][1]==data[2][0])||(data[2][2]==data[1][2]&&data[1][2]==data[0][2])||(data[0][2]==data[1][1]&&data[1][1]==data[2][0])||(data[0][1]==data[1][1]&&data[1][1]==data[2][1])||(data[1][0]==data[1][1]&&data[1][1]==data[1][2]))
                {
                    //显示胜利图片
                    showbmp("./mnt/game_win.bmp",420,0);
                    //选择继续还是退出
                    while (1)
                    {
                        if(tx<520&&tx>420&&ty<250&&ty>150)
                        {
                            tx=0;
                            ty=0;
                            goto again;
                        }
                        if (tx<520&&tx>420&&ty<350&&ty>250)
                        {
                            tx=0;
                            ty=0;
                            showbmp("./mnt/menu.bmp",0,0);               
                            display_lcd = display_menu;
                            goto start;
                        }  
                    }
                }
            }

            
            if(tx<416&&tx>316&&ty<249&&ty>149&&data[1][2]==6)//6
            {
                //记录总点击次数
                num_copy++;
                //点击次数记录
                num++;
                //坐标清零
                tx=0;
                ty=0;
                if(num==1)
                {
                    showbmp("./mnt/quan.bmp",301,149);
                    
                }
                else if(num==2)
                {
                    showbmp("./mnt/cha.bmp",301,149);
                    
                }
                data[1][2] = num+20;
            if((data[0][0]==data[0][1]&&data[0][1]==data[0][2])||(data[0][0]==data[1][0]&&data[1][0]==data[2][0])||(data[0][0]==data[1][1]&&data[1][1]==data[2][2])||(data[2][2]==data[2][1]&&data[2][1]==data[2][0])||(data[2][2]==data[1][2]&&data[1][2]==data[0][2])||(data[0][2]==data[1][1]&&data[1][1]==data[2][0])||(data[0][1]==data[1][1]&&data[1][1]==data[2][1])||(data[1][0]==data[1][1]&&data[1][1]==data[1][2]))
                {
                    //显示胜利图片
                    showbmp("./mnt/game_win.bmp",420,0);
                    //选择继续还是退出
                    while (1)
                    {
                        if(tx<520&&tx>420&&ty<250&&ty>150)
                        {
                            tx=0;
                            ty=0;
                            goto again;
                        }
                        if (tx<520&&tx>420&&ty<350&&ty>250)
                        {
                            tx=0;
                            ty=0;
                            showbmp("./mnt/menu.bmp",0,0);               
                            display_lcd = display_menu;
                            goto start;
                        }  
                    }
                }
            }

            
            if(tx<137&&tx>37&&ty<392&&ty>292&& data[2][0]==7)//7
            {
                //记录总点击次数
                num_copy++;
                //点击次数记录
                num++;
                //坐标清零
                tx=0;
                ty=0;
                if(num==1)
                {
                    showbmp("./mnt/quan.bmp",37,292);
                    
                }
                else if(num==2)
                {
                    showbmp("./mnt/cha.bmp",37,292);
                    
                }
                data[2][0] = num+20;
            if((data[0][0]==data[0][1]&&data[0][1]==data[0][2])||(data[0][0]==data[1][0]&&data[1][0]==data[2][0])||(data[0][0]==data[1][1]&&data[1][1]==data[2][2])||(data[2][2]==data[2][1]&&data[2][1]==data[2][0])||(data[2][2]==data[1][2]&&data[1][2]==data[0][2])||(data[0][2]==data[1][1]&&data[1][1]==data[2][0])||(data[0][1]==data[1][1]&&data[1][1]==data[2][1])||(data[1][0]==data[1][1]&&data[1][1]==data[1][2]))
                {
                    //显示胜利图片
                    showbmp("./mnt/game_win.bmp",420,0);
                    //选择继续还是退出
                    while (1)
                    {
                        if(tx<520&&tx>420&&ty<250&&ty>150)
                        {
                            tx=0;
                            ty=0;
                            goto again;
                        }
                        if (tx<520&&tx>420&&ty<350&&ty>250)
                        {
                            tx=0;
                            ty=0;
                            showbmp("./mnt/menu.bmp",0,0);               
                            display_lcd = display_menu;
                            goto start;
                        }  
                    }
                }
            }
            
            
            if(tx<273&&tx>173&&ty<398&&ty>298&&data[2][1]==8)//8
            {
                //记录总点击次数
                num_copy++;
                //点击次数记录
                num++;
                //坐标清零
                tx=0;
                ty=0;
                if(num==1)
                {
                    showbmp("./mnt/quan.bmp",173,298);
                    
                }
                else if(num==2)
                {
                    showbmp("./mnt/cha.bmp",173,298);
                    
                }
                data[2][1] = num+20;
                if((data[0][0]==data[0][1]&&data[0][1]==data[0][2])||(data[0][0]==data[1][0]&&data[1][0]==data[2][0])||(data[0][0]==data[1][1]&&data[1][1]==data[2][2])||(data[2][2]==data[2][1]&&data[2][1]==data[2][0])||(data[2][2]==data[1][2]&&data[1][2]==data[0][2])||(data[0][2]==data[1][1]&&data[1][1]==data[2][0])||(data[0][1]==data[1][1]&&data[1][1]==data[2][1])||(data[1][0]==data[1][1]&&data[1][1]==data[1][2]))
                {
                    //显示胜利图片
                    showbmp("./mnt/game_win.bmp",420,0);
                    //选择继续还是退出
                    while (1)
                    {
                        if(tx<520&&tx>420&&ty<250&&ty>150)
                        {
                            tx=0;
                            ty=0;
                            goto again;
                        }
                        if (tx<520&&tx>420&&ty<350&&ty>250)
                        {
                            tx=0;
                            ty=0;
                            showbmp("./mnt/menu.bmp",0,0);               
                            display_lcd = display_menu;
                            goto start;
                        }  
                    }
                }
            }

            
            if(tx<417&&tx>317&&ty<392&&ty>292&& data[2][2]==9)//9
            {
                //记录总点击次数
                num_copy++;
                //点击次数记录
                num++;
                //坐标清零
                tx=0;
                ty=0;
                if(num==1)
                {
                    showbmp("./mnt/quan.bmp",302,292);
                    
                }
                else if(num==2)
                {
                    showbmp("./mnt/cha.bmp",302,292);
                    
                }
                data[2][2] = num+20;
                if((data[0][0]==data[0][1]&&data[0][1]==data[0][2])||(data[0][0]==data[1][0]&&data[1][0]==data[2][0])||(data[0][0]==data[1][1]&&data[1][1]==data[2][2])||(data[2][2]==data[2][1]&&data[2][1]==data[2][0])||(data[2][2]==data[1][2]&&data[1][2]==data[0][2])||(data[0][2]==data[1][1]&&data[1][1]==data[2][0])||(data[0][1]==data[1][1]&&data[1][1]==data[2][1])||(data[1][0]==data[1][1]&&data[1][1]==data[1][2]))
                {
                    //显示胜利图片
                    showbmp("./mnt/game_win.bmp",420,0);
                    //选择继续还是退出
                    while (1)
                    {
                        if(tx<520&&tx>420&&ty<250&&ty>150)
                        {
                            tx=0;
                            ty=0;
                            goto again;
                        }
                        if (tx<520&&tx>420&&ty<350&&ty>250)
                        {
                            tx=0;
                            ty=0;
                            showbmp("./mnt/menu.bmp",0,0);               
                            display_lcd = display_menu;
                            goto start;
                        }  
                    }
                }

            }
            //圈叉交替
            if(num==2)
            {
                num = 0;
                    
            }
            //平局判定
            if((num_copy==9)&&(((data[0][0]==data[0][1]&&data[0][1]==data[0][2])||(data[0][0]==data[1][0]&&data[1][0]==data[2][0])||(data[0][0]==data[1][1]&&data[1][1]==data[2][2])||(data[2][2]==data[2][1]&&data[2][1]==data[2][0])||(data[2][2]==data[1][2]&&data[1][2]==data[0][2])||(data[0][2]==data[1][1]&&data[1][1]==data[2][0])||(data[0][1]==data[1][1]&&data[1][1]==data[2][1])||(data[1][0]==data[1][1]&&data[1][1]==data[1][2]))==0))
            {
                //显示平局图片
                showbmp("./mnt/game_ping.bmp",420,0);
                //选择继续还是退出
                while(1)
                {
                    if(tx<520&&tx>420&&ty<250&&ty>150)
                    {
                        tx=0;
                        ty=0;
                        goto again;
                    }
                    if (tx<520&&tx>420&&ty<350&&ty>250)
                    {
                        tx=0;
                        ty=0;
                        showbmp("./mnt/menu.bmp",0,0);               
                        display_lcd = display_menu;
                        goto start;
                    }  
                }

            }

            if((tx>643&&tx<747)&&(ty>34&&ty<77))//点击退出游戏
            {
                ts_flag=0;
                tx=0;
                ty=0;
                showbmp("./mnt/menu.bmp",0,0);               
                display_lcd = display_menu;
                goto start;
            }
            if(ts_flag == 3&&y0_value > 0&&y0_value <= 10)//下滑退出游戏
            {
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








        
                
            
    
