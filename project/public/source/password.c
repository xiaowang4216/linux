#include "password.h"


//设置管理员密码
char passworld[6]="123456";
//定义输入密码缓冲区
char inputpass[6];

//使用者身份
int user_id;


//管理员登录
int adm_login()
{
	int pass_flag = 0;
	//显示登录界面
	//showbmp();
	while(1)
	{
		
		//输入密码
	    pass_flag = get_passworld();
		if(pass_flag == 1)//返回上一个界面
		{
			return 1;
		}	    
	    //判断密码是否正确  passworld  inputpass
	    if(strncmp(passworld,inputpass,sizeof(passworld))==0)//正确
	    {
	    	//提示密码正确
	    	//showbmp();
			printf("paaword yes \n");
			user_id = admin_user;       
			break;
	    }
	    else//错误
	    {
	    	//提示密码错误
	    	//showbmp();
            //sleep(1);
	    	//清空输入框
	    	//showbmp();
			printf("password error \n");
            
	    	//清空输入密码的缓冲区
	    	bzero(inputpass,6);
            
	    	//重新输入密码
	    	continue;
	    }	
	    	
	}	
	return 0;
}

//输入密码
int get_passworld()
{
	int i = 0;//下标
	tx = 0;
	ty = 0;
	while(1)
	{
		if(tx>541&&tx<625&&ty>154&&ty<227)//1
        {   
		    if(i==6)//判断输入的是否超出6位
			{
				continue ;
			}
			inputpass[i] = '1';//把1丢到输入缓冲区
			
			showbmp("./mnt/xing.bmp",51+40*i,190) ;//显示提示*
			
			i++;//位置后移一位
			ty = 0;
			tx = 0;
		}		
		if(tx>629&&tx<708&&ty>162&&ty<227)//2
        {
		    if(i==6)
			{
				continue ;
			}
			inputpass[i] = '2';//把1丢到输入缓冲区
			
			showbmp( "./mnt/xing.bmp",51+40*i,190) ;//显示提示*
			
			i++;//位置后移一位
			ty = 0;
			tx = 0;
		}
		if(tx>708&&tx<800&&ty>162&&ty<227)//3
        {
		    if(i==6)
			{
				continue ;
			}
			inputpass[i] = '3';//把1丢到输入缓冲区
			
			showbmp( "./mnt/xing.bmp",51+40*i,190) ;//显示提示*
			
			i++;//位置后移一位
			ty = 0;
			tx = 0;
		}
		if(tx>541&&tx<625&&ty>227&&ty<312)//4
        {
		    if(i==6)
			{
				continue ;
			}
			inputpass[i] = '4';//把1丢到输入缓冲区
			
			showbmp( "./mnt/xing.bmp",51+40*i,190) ;//显示提示*
			
			i++;//位置后移一位
			ty = 0;
			tx = 0;
		}
		if(tx>629&&tx<708&&ty>227&&ty<312)//5
        {
		    if(i==6)
			{
				continue ;
			}
			inputpass[i] = '5';//把1丢到输入缓冲区
			
			showbmp( "./mnt/xing.bmp",51+40*i,190) ;//显示提示*
			
			i++;//位置后移一位
			ty = 0;
			tx = 0;
		}
		if(tx>708&&tx<800&&ty>227&&ty<312)//6
		{
		    if(i==6)
			{
				continue ;
			}
			inputpass[i] = '6';//把1丢到输入缓冲区
			
			showbmp( "./mnt/xing.bmp",51+40*i,190) ;//显示提示*
			
			i++;//位置后移一位
			ty = 0;
			tx = 0;
		}
		if(tx>541&&tx<625&&ty>321&&ty<389)//7
        {
		    if(i==6)
			{
				continue ;
			}
			inputpass[i] = '7';//把1丢到输入缓冲区
			
			showbmp( "./mnt/xing.bmp",51+40*i,190) ;//显示提示*
			
			i++;//位置后移一位
			ty = 0;
			tx = 0;
		}
		if(tx>629&&tx<708&&ty>321&&ty<389)//8
        {
		    if(i==6)
			{
				continue ;
			}
			inputpass[i] = '8';//把1丢到输入缓冲区
			
			showbmp( "./mnt/xing.bmp",51+40*i,190) ;//显示提示*
			
			i++;//位置后移一位
			ty = 0;
			tx = 0;
		}
		if(tx>708&&tx<800&&ty>321&&ty<389)//9
        {
		    if(i==6)
			{
				continue ;
			}
			inputpass[i] = '9';//把1丢到输入缓冲区
			
			showbmp( "./mnt/xing.bmp",51+40*i,190) ;//显示提示*
			
			i++;//位置后移一位
			ty = 0;
			tx = 0;
		}
		if(tx>457&&tx<540&&ty>154&&ty<227)//0
        {
		    if(i==6)
			{
				continue ;
			}
			inputpass[i] = '0';//把1丢到输入缓冲区
			
			showbmp( "./mnt/xing.bmp",51+40*i,190) ;//显示提示*
			
			i++;//位置后移一位
			ty = 0;
			tx = 0;
		}
		if(tx>673&&tx<800&&ty>417&&ty<453)//c 删除   1 2  
		{
			
			inputpass[i] = 0;//清理当前位置的数据
			if(i==0)//判断是否删除完毕
			{
				continue;
			}
			i--;//回到最后一个数据位置
            showbmp("./mnt/null.bmp",51+40*i,190) ;//显示空白图片	
			ty = 0;
			tx = 0;		
		}
		if(tx>78&&tx<268&&ty>279&&ty<330)//ok
		{
			break;
			ty = 0;
			tx = 0;
		}
		if(ts_flag == 2&&x0_value >= 790)//退出  //待设置，设置为左滑退出
		{
			ts_flag == 0;
            tx = 0;
            ty = 0;
			display_lcd = display_login;
			return 1;
		}		
	}
	return 0;	
}

//用户身份选择界面
int user()
{
	int n;
	showbmp("./mnt/user_select.bmp",0,0);
	while(1)
	{		
		if(tx>567&&tx<732&&ty>320&&ty<365)//管理员
		{
			showbmp("./mnt/admin_login.bmp", 0,0);
            n = adm_login(); 
			if(n == 1)
			{
				//显示用户选择界面
				showbmp("./mnt/user_select.bmp", 0,0);
				continue ;
			}
			else
			{
				//进入主界面 进入下一个界面
	    	    showbmp("./mnt/menu.bmp", 0,0);
				display_lcd = display_menu;
				break;
			}
		}
		if(tx>80&&tx<269&&ty>306&&ty<355)//普通用户
		{
			//进入主界面 进入下一个界面
			showbmp("./mnt/menu.bmp", 0,0);
			display_lcd = display_menu;
			user_id = general_user;
			break;
		}
		
	}	
}







