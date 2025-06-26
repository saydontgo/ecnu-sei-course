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

