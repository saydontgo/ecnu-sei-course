#include "./tim/bsp_basic_tim.h"
static void TIMx_NVIC_Configuration(void)
{   NVIC_InitTypeDef NVIC_InitStructure; 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
	
    NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQn; 	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void TIM_Mode_Config(void)
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		RCC_APB1PeriphClockCmd(BASIC_TIM_CLK, ENABLE);
		TIM_TimeBaseStructure.TIM_Period = 60000-1;
		TIM_TimeBaseStructure.TIM_Prescaler = 9000-1;	
		TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);
		TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);
		TIM_ITConfig(BASIC_TIM,TIM_IT_Update,ENABLE);
		TIM_Cmd(BASIC_TIM, ENABLE);	
}
void TIMx_Configuration(void)
{
		TIMx_NVIC_Configuration();
		TIM_Mode_Config();
}
