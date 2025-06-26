#include "stm32f4xx.h"
#include "./led/led.h"
#include "./key/exti.h"
#include "main.h"

void TimingDelay_Decrement(void)
{
		int i,j;
		for(i=0;i<5;i++)
	 	{
			j=5000000;
			while (j>=0) j--;
		}
}

int main()
{
		LED_Config();
		EXTI_Key_Config();
		while(1){}
}
