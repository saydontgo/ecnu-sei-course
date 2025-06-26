                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
/*
	Ê¹ÓÃ¼Ä´æÆ÷µÄ·½·¨µãÁÁLEDµÆ
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
		/* LED ¶Ë¿Ú³õÊ¼»¯ */
	
	/*GPIOH MODER10Çå¿Õ*/
	GPIOH_MODER  &= ~( 0x03<< (2*color));	
	/*PH10 MODER10 = 01b Êä³öÄ£Ê½*/
	GPIOH_MODER |= (1<<2*color);
	
	/*GPIOH OTYPER10Çå¿Õ*/
	GPIOH_OTYPER &= ~(1<<1*color);
	/*PH10 OTYPER10 = 0b ÍÆÍìÄ£Ê½*/
	GPIOH_OTYPER |= (0<<1*color);
	
	/*GPIOH OSPEEDR10Çå¿Õ*/
	GPIOH_OSPEEDR &= ~(0x03<<2*color);
	/*PH10 OSPEEDR10 = 0b ËÙÂÊ2MHz*/
	GPIOH_OSPEEDR |= (0<<2*color);
	
	/*GPIOH PUPDR10Çå¿Õ*/
	GPIOH_PUPDR &= ~(0x03<<2*color);
	/*PH10 PUPDR10 = 01b ÉÏÀ­Ä£Ê½*/
	GPIOH_PUPDR |= (1<<2*color);

}

/**
  *   ä¸»å‡½æ•°
  */
int main(void)
{	
	/*å¤–è®¾æ—¶é’Ÿè®¾ç½®*/
	RCC_AHB1ENR |= (1<<7);	
	
	int red=10;
	int green=11;
	int blue=12;
	
	init_led(red);
	init_led(blue);
	init_led(green);
	while(1)
	{
	/*çº¢ç¯è®¾ç½®*/
	GPIOH_BSRR |= (1<<16<<red);
		DelayNS(100);
	GPIOH_BSRR |= (1<<red);
		
	GPIOH_BSRR |= (1<<16<<green);			
	DelayNS(100);
	/*ç»¿ç¯è®¾ç½®*/
	GPIOH_BSRR |= (1<<green);	
		
			GPIOH_BSRR |= (1<<16<<blue);			
	DelayNS(100);
	/*è“ç¯è®¾ç½®*/
	GPIOH_BSRR |= (1<<blue);	
	}
}

// º¯ÊýÎª¿Õ£¬Ä¿µÄÊÇÎªÁËÆ­¹ý±àÒëÆ÷²»±¨´í
void SystemInit(void)
{	
}






/*********************************************END OF FILE**********************/

