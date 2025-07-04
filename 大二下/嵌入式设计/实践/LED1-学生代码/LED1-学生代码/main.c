                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
/*
	使用寄存器的方法点亮LED灯
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
		/* LED 端口初始化 */
	
	/*GPIOH MODER10清空*/
	GPIOH_MODER  &= ~( 0x03<< (2*color));	
	/*PH10 MODER10 = 01b 输出模式*/
	GPIOH_MODER |= (1<<2*color);
	
	/*GPIOH OTYPER10清空*/
	GPIOH_OTYPER &= ~(1<<1*color);
	/*PH10 OTYPER10 = 0b 推挽模式*/
	GPIOH_OTYPER |= (0<<1*color);
	
	/*GPIOH OSPEEDR10清空*/
	GPIOH_OSPEEDR &= ~(0x03<<2*color);
	/*PH10 OSPEEDR10 = 0b 速率2MHz*/
	GPIOH_OSPEEDR |= (0<<2*color);
	
	/*GPIOH PUPDR10清空*/
	GPIOH_PUPDR &= ~(0x03<<2*color);
	/*PH10 PUPDR10 = 01b 上拉模式*/
	GPIOH_PUPDR |= (1<<2*color);

}

/**
  *   涓诲嚱鏁�
  */
int main(void)
{	
	/*澶栬鏃堕挓璁剧疆*/
	RCC_AHB1ENR |= (1<<7);	
	
	int red=10;
	int green=11;
	int blue=12;
	
	init_led(red);
	init_led(blue);
	init_led(green);
	while(1)
	{
	/*绾㈢伅璁剧疆*/
	GPIOH_BSRR |= (1<<16<<red);
		DelayNS(100);
	GPIOH_BSRR |= (1<<red);
		
	GPIOH_BSRR |= (1<<16<<green);			
	DelayNS(100);
	/*缁跨伅璁剧疆*/
	GPIOH_BSRR |= (1<<green);	
		
			GPIOH_BSRR |= (1<<16<<blue);			
	DelayNS(100);
	/*钃濈伅璁剧疆*/
	GPIOH_BSRR |= (1<<blue);	
	}
}

// 函数为空，目的是为了骗过编译器不报错
void SystemInit(void)
{	
}






/*********************************************END OF FILE**********************/

