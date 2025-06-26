#include "stm32f4xx.h"
#include "./led/bsp_led.h"

void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{ int i;
	
	for(; nCount != 0; nCount--)
		for(i=0;i<50000;i++);
	
}

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();	 
	


	/* ����LED�� */
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