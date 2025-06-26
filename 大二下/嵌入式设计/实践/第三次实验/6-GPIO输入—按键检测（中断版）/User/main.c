/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   使用按键控制彩灯
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F429 开发板
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./led/bsp_led.h"
#include "./key/bsp_key.h" 
#include "main.h"


volatile uint8_t paused = 0;

/*define Delay function*/
void DelayNS( int dly)
{
	int i;
	
	
	for(;dly>0;dly--)
		for(i=0;i<50000;i++);
	
}

static void EXTI_NVIC_Config(void)
{
		NVIC_InitTypeDef NVIC_InitStruct;
	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
		NVIC_InitStruct.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStruct);	
}


void EXTI_Key_Config(void)
{
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;
	
		EXTI_InitTypeDef  EXTI_InitStruct;

		/*开启LED相关的GPIO外设时钟*/
		RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOA, ENABLE);
	
		//RCC_APB2PeriphClockCmd ( RCC_APB2Periph_SYSCFG, ENABLE);
	
	    EXTI_NVIC_Config();
		
		/*选择要控制的GPIO引脚*/												
	GPIO_InitStructure.GPIO_Pin =  KEY1_PIN;	
		/*设置引脚模式为输入模式*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   
    /*设置引脚为浮空模式*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	    /*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
		GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);
	
		SYSCFG_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE, KEY1_INT_EXTI_PINSOURCE);	
	
		EXTI_InitStruct.EXTI_Line = KEY1_INT_EXTI_LINE;
		EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
     EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
		EXTI_InitStruct.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStruct);
}




/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	/* LED 端口初始化 */
	LED_GPIO_Config();	 
  
  /*初始化按键*/
  // Key_GPIO_Config();
	
	EXTI_Key_Config();
	
 
	/* 轮询按键状态，若按键按下则反转LED */ 
	while(1)                            
	{	
		if(!paused){
			LED1_ON;
			LED2_OFF;
			DelayNS(1500);
			if(paused)continue;
			LED1_OFF;
			LED2_ON;
			DelayNS(1500);
		}
		else{
		}
	}
}



/*********************************************END OF FILE**********************/

