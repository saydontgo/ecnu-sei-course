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
#include "./uart/bsp_usart.h" 



static void Show_message(){
	printf("\r\n ����һ��ͨ������ͨ��ָ�����RGB�ʵ�ʵ�� \n");
	printf("ʹ�� USART1 ����Ϊ %d 8-N-1 \n", USARTx_BAUDRATE);
	printf("������ӵ�ָ������RGB�ʵ���ɫ��ָ���Ӧ���� \n");
	printf("ָ��  ------- �ʵ���ɫ \n");
	printf("1 ------ �� \n");
}

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	char ch;
	
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();	 

  /*��ʼ������*/
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
			printf("�������������\n");
		}
	}
}



/*********************************************END OF FILE**********************/

