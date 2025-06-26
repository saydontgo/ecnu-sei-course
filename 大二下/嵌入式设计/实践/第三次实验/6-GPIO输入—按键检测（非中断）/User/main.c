/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   使用按键控制彩灯
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F429 开发板
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./led/bsp_led.h"
#include "./key/bsp_key.h" 


volatile uint8_t paused = 0;

/*define Delay function*/
void DelayNS( int dly)
{
	int i;
	
	
	for(;dly>0;dly--)
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
  
  /*初始化按键*/
  Key_GPIO_Config();
	
	while(1)                            
	{	
		if(!paused){
			
		// red light on	
		LED1_ON;
		LED3_OFF;
		
		int i;
		for(i=0;i<=1500;i++){
		if( Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON  ) // check if pressed
		{
			paused = !paused;
		}   
		DelayNS(1); 
		}
		
		// paused, get out of the loop
		if(paused)continue;
		
		// green light on
		LED1_OFF;
		LED2_ON;
		
		for(i=0;i<=1500;i++){
		if( Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON  ) // check if pressed
		{
			paused = !paused;
		}   
		DelayNS(1);
		}
	}
	else{
		if( Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON  )
		{
			paused = !paused;
		}
		
		}

	}
}



/*********************************************END OF FILE**********************/

