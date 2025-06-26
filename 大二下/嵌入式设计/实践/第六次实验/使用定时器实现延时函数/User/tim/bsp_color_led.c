#include "./tim/bsp_color_led.h"


static void TIM_Mode_Config(void)
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef 	TIM_OCInitStructure;
	
		RCC_APB1PeriphClockCmd(COLOR_TIM_CLK, ENABLE);
	
		TIM_TimeBaseStructure.TIM_Period = 256-1;
		TIM_TimeBaseStructure.TIM_Prescaler = ((SystemCoreClock/2)/1000000)*30-1;	
	
		
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;//设置时钟分频系数:不分频
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
	
		TIM_TimeBaseInit(COLOR_TIM, &TIM_TimeBaseStructure);
	
		// PWM初始化
		// 通道初始化
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	// 设置PWM模式1  
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	// 打开输出通道
		TIM_OCInitStructure.TIM_Pulse = 0;	  // 设置初始占空比
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;  // 输出极性为低有效，即低电平时点亮led
	
		TIM_OC1Init(COLOR_TIM, &TIM_OCInitStructure); // 使能通道1
	
		TIM_OC1PreloadConfig(COLOR_TIM, TIM_OCPreload_Enable); // 使能通道1重载
		
		TIM_OC2Init(COLOR_TIM, &TIM_OCInitStructure); // 使能通道2
	
		TIM_OC2PreloadConfig(COLOR_TIM, TIM_OCPreload_Enable); // 使能通道2重载
		
		TIM_OC3Init(COLOR_TIM, &TIM_OCInitStructure); // 使能通道3
	
		TIM_OC3PreloadConfig(COLOR_TIM, TIM_OCPreload_Enable); // 使能通道3重载
		
		TIM_ARRPreloadConfig(COLOR_TIM, ENABLE);	// 使能TIM重载寄存器	
		// 使能计数器
		TIM_Cmd(COLOR_TIM, ENABLE);	
}

static void TIMx_GPIO_Config(void){
	
	/*定义一个GPI0 InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*开启LED相关的GPIO外设时钟*/
	RCC_AHB1PeriphClockCmd(COLOR_LED1_GPIO_CLK | COLOR_LED2_GPIO_CLK | COLOR_LED3_GPIO_CLK,ENABLE);
	
	GPIO_PinAFConfig(COLOR_LED1_GPIO_PORT, COLOR_LED1_PINSOURCE, COLOR_LED1_AF);
	GPIO_PinAFConfig(COLOR_LED2_GPIO_PORT, COLOR_LED2_PINSOURCE, COLOR_LED2_AF);
	GPIO_PinAFConfig(COLOR_LED3_GPIO_PORT, COLOR_LED3_PINSOURCE, COLOR_LED3_AF);

	/* COLOR LED1 */
	
	GPIO_InitStructure.GPIO_Pin = COLOR_LED1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用模式，信号源来自于其他部件
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出模式
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //无上下拉模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(COLOR_LED1_GPIO_PORT, &GPIO_InitStructure);
	
	
	// led2  GPIO初始化
	GPIO_InitStructure.GPIO_Pin = COLOR_LED2_PIN;
	GPIO_Init(COLOR_LED2_GPIO_PORT, &GPIO_InitStructure);
	
	// led3  GPIO初始化
	GPIO_InitStructure.GPIO_Pin = COLOR_LED3_PIN;
	GPIO_Init(COLOR_LED3_GPIO_PORT, &GPIO_InitStructure);
}



void ColorLED_Config(void)
{   
	TIMx_GPIO_Config();
	
	TIM_Mode_Config();
	
	SetColorValue(0xff, 0xff, 0xff);
}

void SetRGBColor(uint32_t rgb){
	uint8_t r = 0, g = 0, b = 0;
	r = (uint8_t)(rgb >> 16); // 取高8位，然后强制转化为8bit
	g = (uint8_t)(rgb >> 8);  // 取高16位，然后强制转化为8bit，相当于取了中间8位
	b = (uint8_t) rgb;		  // 取低8位
	
	// 根据PWM表修改定时器的比较寄存器值
	COLOR_TIM->COLOR_LED1_CCRx = r;
	COLOR_TIM->COLOR_LED2_CCRx = g;
	COLOR_TIM->COLOR_LED3_CCRx = b;
}

void SetColorValue(uint8_t r, uint8_t g, uint8_t b){
	// 根据PWM表修改定时器的比较寄存器值
	COLOR_TIM->COLOR_LED1_CCRx = r;
	COLOR_TIM->COLOR_LED2_CCRx = g;
	COLOR_TIM->COLOR_LED3_CCRx = b;
	
}
