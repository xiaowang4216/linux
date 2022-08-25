#include"headfile.h"






int main(void)
{
    //自动挂在内存卡
    SD_Init();
    //esp初始化,并且创建串口一接收线程
    //esp_usart_init();
    //创建系统运行其他线程  
    process_Init();
    while (1)
    {
                    
            
    }
    
    return 0;
}