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
#include "./tim/bsp_color_led.h" 

static void  Delay(__IO uint32_t nCount) // 简单的延时函数
{
	for(; nCount != 0; nCount--);
}

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	ColorLED_Config();
	
	

	while(1){
	for(int i = 0;i < 256;i++){
		SetColorValue(i, 0, 0);
		Delay(0xFFFFF);
	}
	
	for(int i = 255;i > -1;i--){
		SetColorValue(i, 0, 0);
		Delay(0xFFFFF);
	}
	}
}



/*********************************************END OF FILE**********************/

