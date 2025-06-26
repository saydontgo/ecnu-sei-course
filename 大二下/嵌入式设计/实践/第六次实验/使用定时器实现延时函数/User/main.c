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
#include "./led/bsp_basic_tim.h"
#include "./tim/bsp_color_led.h"

extern __IO uint8_t delay_finished;

void  Delay() // 简单的延时函数, 固定延时1秒
{
	delay_finished = 0;
    TIM_Cmd(BASIC_TIM, ENABLE);
    while (!delay_finished);  // 等待中断设置标志
}	

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	ColorLED_Config();
	TIMx_Configuration();
	while(1){
		
		SetRGBColor(0xFF0000); // 仅红色亮
		Delay();
		
		SetRGBColor(0x00FF00); // 仅绿色亮
		Delay();
		
		SetRGBColor(0x0000FF); // 仅蓝色亮
		Delay();
	}
}



/*********************************************END OF FILE**********************/

