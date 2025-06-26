/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   使用按键控制彩灯
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F429 开发板
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./led/bsp_led.h"
#include "./uart/bsp_usart.h" 



static void Show_message(){
	printf("\r\n 这是一个通过串口通信指令控制RGB彩灯实验 \n");
	printf("使用 USART1 参数为 %d 8-N-1 \n", USARTx_BAUDRATE);
	printf("开发板接到指令后控制RGB彩灯颜色，指令对应如下 \n");
	printf("指令  ------- 彩灯颜色 \n");
	printf("1 ------ 红 \n");
}

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	char ch;
	
	/* LED 端口初始化 */
	LED_GPIO_Config();	 

  /*初始化串口*/
  usartx_Config();
	
	Show_message();
	
	while(1)                            
	{	   
		ch = getchar();
		
		if(ch == '1'){
			LED_RED;
		}
		else{
			LED_RGBOFF;
			printf("输入错误，请重输\n");
		}
	}
}



/*********************************************END OF FILE**********************/

