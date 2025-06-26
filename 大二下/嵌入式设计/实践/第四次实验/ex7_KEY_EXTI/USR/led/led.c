#include "./led/led.h"

void LED_Config()
{
	GPIO_InitTypeDef  GPIO_InitStructure; /*定义一个GPIO_InitTypeDef类型的变量*/
	RCC_AHB1PeriphClockCmd(LED1_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED1_PIN;  /*设置控制的引脚号*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  /*设置该引脚为输出类型*/
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  /*设置其类型为推挽模式*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  /*设置其引脚速度*/
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; /*设置为上拉模式*/
		GPIO_Init(LED1_GPIO, &GPIO_InitStructure);  /*调用库函数，初始化GPIOB12引脚*/
}
