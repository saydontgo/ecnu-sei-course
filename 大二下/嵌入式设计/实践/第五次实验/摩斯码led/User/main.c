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
#include <string.h>
#include <ctype.h>

static void Show_message(){
	printf("\r\n ����һ��ʹ��ledչʾĦ˹�����ʵ�� \n");
	printf("����һ��ֻ����Ӣ���ַ����ַ������ͻ�ʹ��led���ֳ���Ӧ��Ħ˹�� \n");
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


void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{ int i;
	
	for(; nCount != 0; nCount--)
		for(i=0;i<50000;i++);
	
}

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */

int main(void)
{
	char ch[20];
	
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();	 

  /*��ʼ������*/
  usartx_Config();
	Show_message();
	
	while(1)                            
	{	
		scanf("%s", ch);
		for(int i=0;i < strlen(ch); i++){
			int row = tolower(ch[i]) - 'a';
			if(row < 0 || row > 25){
				printf("������ģ� %c ���Ϸ����޷�ת���Ħ˹��\n", row + 'a');
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

