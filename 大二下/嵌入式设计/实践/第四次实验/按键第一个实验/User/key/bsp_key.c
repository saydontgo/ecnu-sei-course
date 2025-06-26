#include "./key/bsp_key.h" 

static void NVIC_Configuration(void)
{
		NVIC_InitTypeDef NVIC_InitStruct;
	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
		NVIC_InitStruct.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStruct);	
}

void EXTI_Key_Config(void)
{

		GPIO_InitTypeDef GPIO_InitStructure;
	
		EXTI_InitTypeDef  EXTI_InitStruct;
		
		/* 开启gpio的时钟 */
		RCC_AHB1PeriphClockCmd ( KEY1_INT_GPIO_CLK, ENABLE);
		
		/* 使能SYSCFG时钟 */
		RCC_APB2PeriphClockCmd ( RCC_APB2Periph_SYSCFG, ENABLE);
		
		/* 配置NVIC */
	    NVIC_Configuration();
												
		/* 选择key1 */
		GPIO_InitStructure.GPIO_Pin =  KEY1_INT_GPIO_PIN;
		
	    /* 设置引脚为输入模式 */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   
		
		/* 既不上拉也不下拉*/
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	    
		/* 初始化按键 */
		GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);
		
		/* 连接 EXIT 中断源到key1的引脚 */
		SYSCFG_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE, KEY1_INT_EXTI_PINSOURCE);	
		
		/* 选择 EXIT 中断源 */
		EXTI_InitStruct.EXTI_Line = KEY1_INT_EXTI_LINE;
		
		/* 中断模式 */
		EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
		
		/* 上升沿触发 */
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
		
		/* 使能中断线 */
		EXTI_InitStruct.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStruct);
}
