#include "./led/led.h"

void LED_Config()
{
	GPIO_InitTypeDef  GPIO_InitStructure; /*����һ��GPIO_InitTypeDef���͵ı���*/
	RCC_AHB1PeriphClockCmd(LED1_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED1_PIN;  /*���ÿ��Ƶ����ź�*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  /*���ø�����Ϊ�������*/
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  /*����������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  /*�����������ٶ�*/
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; /*����Ϊ����ģʽ*/
		GPIO_Init(LED1_GPIO, &GPIO_InitStructure);  /*���ÿ⺯������ʼ��GPIOB12����*/
}
