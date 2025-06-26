#ifndef __KEY_H
#define	__KEY_H

#include "stm32f4xx.h"

//引脚定义
#define KEY1_INT_GPIO_PIN         GPIO_Pin_0                 
#define KEY1_INT_GPIO_PORT        GPIOA
#define KEY1_INT_GPIO_CLK         RCC_AHB1Periph_GPIOA

#define KEY1_INT_EXTI_LINE        EXTI_Line0
#define KEY1_INT_EXTI_PORTSOURCE  EXTI_PortSourceGPIOA
#define KEY1_INT_EXTI_PINSOURCE   EXTI_PinSource0
#define KEY1_INT_EXTI_IRQ         EXTI0_IRQn
#define KEY1_IRQHANDLER           EXTI0_IRQHandler

/** 按键按下标置宏
	 * 按键按下为高电平，设置 KEY_ON=1， KEY_OFF=0
 * 若按键按下为低电平，把宏设置成KEY_ON=0 ，KEY_OFF=1 即可
	 */
/*#define KEY_ON	0
  #define KEY_OFF	1
  void Key_GPIO_Config(void);
  uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);
*/
void EXTI_Key_Config(void);

#endif /* __LED_H */
