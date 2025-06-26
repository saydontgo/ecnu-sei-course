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
		
		// �ҵ�ѧ��Ϊ10235101477, ����λת��Ϊ16���ƣ�0x101477
		SetRGBColor(0x100000); // ��ǰ��λ��
		Delay(0xFFFFFF);
		
		SetRGBColor(0x001400); // ���м���λ����
		Delay(0xFFFFFF);
		
		SetRGBColor(0x000077); // ��������λ��
		Delay(0xFFFFFF);
	}
}



/*********************************************END OF FILE**********************/

