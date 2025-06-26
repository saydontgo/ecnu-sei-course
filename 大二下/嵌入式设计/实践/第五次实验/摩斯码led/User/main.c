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
#include <string.h>
#include <ctype.h>

static void Show_message(){
	printf("\r\n 这是一个使用led展示摩斯电码的实验 \n");
	printf("输入一个只包含英文字符的字符串，就会使用led表现出对应的摩斯码 \n");
}

int dict[26][4] = {
	// abcde
	1,2,0,0,
	2,1,1,1,
	2,1,2,1,
	2,1,1,0,
	1,0,0,0,
	
	// fghij
	1,1,2,1,
	2,2,1,0,
	1,1,1,1,
	1,1,0,0,
	1,2,2,2,
	
	// klmno
	2,1,2,0,
	1,2,1,1,
	2,2,0,0,
	2,1,0,0,
	2,2,2,0,
	
	// pqrst
	1,2,2,1,
	2,2,1,2,
	1,2,1,0,
	1,1,1,0,
	2,0,0,0,
	
	// uvwxy
	1,1,2,0,
	1,1,1,2,
	1,2,2,0,
	2,1,1,2,
	2,1,2,2,
	
	// z
	2,2,1,1	
};


void Delay(__IO uint32_t nCount)	 //简单的延时函数
{ int i;
	
	for(; nCount != 0; nCount--)
		for(i=0;i<50000;i++);
	
}

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */

int main(void)
{
	char ch[20];
	
	/* LED 端口初始化 */
	LED_GPIO_Config();	 

  /*初始化串口*/
  usartx_Config();
	Show_message();
	
	while(1)                            
	{	
		scanf("%s", ch);
		for(int i=0;i < strlen(ch); i++){
			int row = tolower(ch[i]) - 'a';
			if(row < 0 || row > 25){
				printf("你输入的： %c 不合法，无法转译成摩斯码\n", row + 'a');
				continue;
			}
			for(int j=0;j < 4;j++){
				switch(dict[row][j]){
					case 1:
						LED_RED;
						Delay(1000);
						break;
					case 2:
						LED_WHITE;
						Delay(3000);
						break;
					default:
						break;
				}
			LED_RGBOFF;
			Delay(500);
			}
			LED_RGBOFF;
			Delay(2000);
		}
		
	}
}



/*********************************************END OF FILE**********************/

