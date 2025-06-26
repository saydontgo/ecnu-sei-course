#include "./tim/bsp_color_led.h"


static void TIM_Mode_Config(void)
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef 	TIM_OCInitStructure;
	
		RCC_APB1PeriphClockCmd(COLOR_TIM_CLK, ENABLE);
	
		TIM_TimeBaseStructure.TIM_Period = 256-1;
		TIM_TimeBaseStructure.TIM_Prescaler = ((SystemCoreClock/2)/1000000)*30-1;	
	
		
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;//����ʱ�ӷ�Ƶϵ��:����Ƶ
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
	
		TIM_TimeBaseInit(COLOR_TIM, &TIM_TimeBaseStructure);
	
		// PWM��ʼ��
		// ͨ����ʼ��
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	// ����PWMģʽ1  
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	// �����ͨ��
		TIM_OCInitStructure.TIM_Pulse = 0;	  // ���ó�ʼռ�ձ�
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;  // �������Ϊ����Ч�����͵�ƽʱ����led
	
		TIM_OC1Init(COLOR_TIM, &TIM_OCInitStructure); // ʹ��ͨ��1
	
		TIM_OC1PreloadConfig(COLOR_TIM, TIM_OCPreload_Enable); // ʹ��ͨ��1����
		
		TIM_OC2Init(COLOR_TIM, &TIM_OCInitStructure); // ʹ��ͨ��2
	
		TIM_OC2PreloadConfig(COLOR_TIM, TIM_OCPreload_Enable); // ʹ��ͨ��2����
		
		TIM_OC3Init(COLOR_TIM, &TIM_OCInitStructure); // ʹ��ͨ��3
	
		TIM_OC3PreloadConfig(COLOR_TIM, TIM_OCPreload_Enable); // ʹ��ͨ��3����
		
		TIM_ARRPreloadConfig(COLOR_TIM, ENABLE);	// ʹ��TIM���ؼĴ���	
		// ʹ�ܼ�����
		TIM_Cmd(COLOR_TIM, ENABLE);	
}

static void TIMx_GPIO_Config(void){
	
	/*����һ��GPI0 InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*����LED��ص�GPIO����ʱ��*/
	RCC_AHB1PeriphClockCmd(COLOR_LED1_GPIO_CLK | COLOR_LED2_GPIO_CLK | COLOR_LED3_GPIO_CLK,ENABLE);
	
	GPIO_PinAFConfig(COLOR_LED1_GPIO_PORT, COLOR_LED1_PINSOURCE, COLOR_LED1_AF);
	GPIO_PinAFConfig(COLOR_LED2_GPIO_PORT, COLOR_LED2_PINSOURCE, COLOR_LED2_AF);
	GPIO_PinAFConfig(COLOR_LED3_GPIO_PORT, COLOR_LED3_PINSOURCE, COLOR_LED3_AF);

	/* COLOR LED1 */
	
	GPIO_InitStructure.GPIO_Pin = COLOR_LED1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//����ģʽ���ź�Դ��������������
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������ģʽ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //��������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(COLOR_LED1_GPIO_PORT, &GPIO_InitStructure);
	
	
	// led2  GPIO��ʼ��
	GPIO_InitStructure.GPIO_Pin = COLOR_LED2_PIN;
	GPIO_Init(COLOR_LED2_GPIO_PORT, &GPIO_InitStructure);
	
	// led3  GPIO��ʼ��
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
	r = (uint8_t)(rgb >> 16); // ȡ��8λ��Ȼ��ǿ��ת��Ϊ8bit
	g = (uint8_t)(rgb >> 8);  // ȡ��16λ��Ȼ��ǿ��ת��Ϊ8bit���൱��ȡ���м�8λ
	b = (uint8_t) rgb;		  // ȡ��8λ
	
	// ����PWM���޸Ķ�ʱ���ıȽϼĴ���ֵ
	COLOR_TIM->COLOR_LED1_CCRx = r;
	COLOR_TIM->COLOR_LED2_CCRx = g;
	COLOR_TIM->COLOR_LED3_CCRx = b;
}

void SetColorValue(uint8_t r, uint8_t g, uint8_t b){
	// ����PWM���޸Ķ�ʱ���ıȽϼĴ���ֵ
	COLOR_TIM->COLOR_LED1_CCRx = r;
	COLOR_TIM->COLOR_LED2_CCRx = g;
	COLOR_TIM->COLOR_LED3_CCRx = b;
	
}
