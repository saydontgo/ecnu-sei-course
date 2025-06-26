                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
/*
	ʹ�üĴ����ķ�������LED��
  */

#include "stm32f4xx.h" 

/*define Delay function*/
void DelayNS( int dly)
{
	int i;
	
	
	for(;dly>0;dly--)
		for(i=0;i<50000;i++);
	
}

void init_led(int color)
{
		/* LED �˿ڳ�ʼ�� */
	
	/*GPIOH MODER10���*/
	GPIOH_MODER  &= ~( 0x03<< (2*color));	
	/*PH10 MODER10 = 01b ���ģʽ*/
	GPIOH_MODER |= (1<<2*color);
	
	/*GPIOH OTYPER10���*/
	GPIOH_OTYPER &= ~(1<<1*color);
	/*PH10 OTYPER10 = 0b ����ģʽ*/
	GPIOH_OTYPER |= (0<<1*color);
	
	/*GPIOH OSPEEDR10���*/
	GPIOH_OSPEEDR &= ~(0x03<<2*color);
	/*PH10 OSPEEDR10 = 0b ����2MHz*/
	GPIOH_OSPEEDR |= (0<<2*color);
	
	/*GPIOH PUPDR10���*/
	GPIOH_PUPDR &= ~(0x03<<2*color);
	/*PH10 PUPDR10 = 01b ����ģʽ*/
	GPIOH_PUPDR |= (1<<2*color);

}

/**
  *   主函数
  */
int main(void)
{	
	/*外设时钟设置*/
	RCC_AHB1ENR |= (1<<7);	
	
	int red=10;
	int green=11;
	int blue=12;
	
	init_led(red);
	init_led(blue);
	init_led(green);
	while(1)
	{
	/*红灯设置*/
	GPIOH_BSRR |= (1<<16<<red);
		DelayNS(100);
	GPIOH_BSRR |= (1<<red);
		
	GPIOH_BSRR |= (1<<16<<green);			
	DelayNS(100);
	/*绿灯设置*/
	GPIOH_BSRR |= (1<<green);	
		
			GPIOH_BSRR |= (1<<16<<blue);			
	DelayNS(100);
	/*蓝灯设置*/
	GPIOH_BSRR |= (1<<blue);	
	}
}

// ����Ϊ�գ�Ŀ����Ϊ��ƭ��������������
void SystemInit(void)
{	
}






/*********************************************END OF FILE**********************/

