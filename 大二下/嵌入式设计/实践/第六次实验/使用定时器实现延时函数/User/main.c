/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ʹ�ð������Ʋʵ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F429 ������
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */

 
#include "stm32f4xx.h"
#include "./led/bsp_basic_tim.h"
#include "./tim/bsp_color_led.h"

extern __IO uint8_t delay_finished;

void  Delay() // �򵥵���ʱ����, �̶���ʱ1��
{
	delay_finished = 0;
    TIM_Cmd(BASIC_TIM, ENABLE);
    while (!delay_finished);  // �ȴ��ж����ñ�־
}	

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	ColorLED_Config();
	TIMx_Configuration();
	while(1){
		
		SetRGBColor(0xFF0000); // ����ɫ��
		Delay();
		
		SetRGBColor(0x00FF00); // ����ɫ��
		Delay();
		
		SetRGBColor(0x0000FF); // ����ɫ��
		Delay();
	}
}



/*********************************************END OF FILE**********************/

