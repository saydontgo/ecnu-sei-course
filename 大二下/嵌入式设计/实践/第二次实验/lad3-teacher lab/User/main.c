#include "stm32f4xx.h"
#include "./led/bsp_led.h"

void Delay(__IO uint32_t nCount)	 //简单的延时函数
{ int i;
	
	for(; nCount != 0; nCount--)
		for(i=0;i<50000;i++);
	
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
	


	/* 控制LED灯 */
	while (1)
	{

		/*red-green-blue*/
		LED_RED;
		Delay(0xFF);
		
		LED_GREEN;
		Delay(0xFF);
		
		LED_BLUE;
		Delay(0xFF);
		
		//LED_RED_OFF;
		//Delay(0xFF);
	}
}



/*********************************************END OF FILE**********************/