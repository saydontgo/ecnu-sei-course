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
#include "./led/bsp_led.h"
#include "./tim/bsp_color_led.h" 

static void  Delay(__IO uint32_t nCount) // �򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	ColorLED_Config();
	
	while(1){
		SetRGBColor(0xFF0000); // ����ɫ��
		Delay(0xFFFFFF);
		
		SetRGBColor(0x00FF00); // ����ɫ��
		Delay(0xFFFFFF);
		
		SetRGBColor(0x0000FF); // ����ɫ��
		Delay(0xFFFFFF);
	}
}



/*********************************************END OF FILE**********************/

