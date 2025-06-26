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
		
		switch(ch){
			case '1':
				LED_RED;
				break;
			case '2':
				LED_GREEN;
				break;
			case '3':
				LED_BLUE;
				break;
			case '4':
				LED_YELLOW;
				break;
			case '5':
				LED_PURPLE;
				break;
			case '6':
				LED_CYAN;
				break;
			case '7':
				LED_WHITE;
				break;
			case '8':
				LED_RGBOFF;
				break;
			default:
				printf("�������������,��ֻ����1��8���ڵ�����\n");
				break;
		
		}
	}
}



/*********************************************END OF FILE**********************/

