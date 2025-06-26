#include "exit/exit.h"


void EXTIX_Init(void)
{

	EXTI_InitTypeDef EXTI_InitStructure;	//外部中断结构体初始化
	NVIC_InitTypeDef NVIC_InitStructure;	//中断分组结构体初始化

	KEY_Init();

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//开启AFIO时钟

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);	//映射IO口与中断线
	
    //以下为配置中断线初始化
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//中断模式
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//使能中断线
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;				//中断线标号
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;	//触发方式

	EXTI_Init(&EXTI_InitStructure);

	//以下为中断优先级的配置
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;		//声明使用的中断是哪一个
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//设置抢占优先级为2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;	//设置子优先级为3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//使能中断

	NVIC_Init(&NVIC_InitStructure);
}

void EXTI0_IRQHandler(void)		//中断服务函数
{
	delay_ms(10);			//软件去抖
	if(WK_UP==1)
	{				 
		LED0 = !LED0;
		LED1 = !LED1;
	}
	EXTI_ClearITPendingBit(EXTI_Line0);		//清除中断位
}


