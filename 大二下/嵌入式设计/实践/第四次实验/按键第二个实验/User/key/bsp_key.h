#ifndef __KEY_H
#define	__KEY_H

#include "stm32f4xx.h"

//按键初始化
#define KEY2_INT_GPIO_PIN         GPIO_Pin_13                 
#define KEY2_INT_GPIO_PORT        GPIOC
#define KEY2_INT_GPIO_CLK         RCC_AHB1Periph_GPIOC

#define KEY2_INT_EXTI_LINE        EXTI_Line13
#define KEY2_INT_EXTI_PORTSOURCE  EXTI_PortSourceGPIOC
#define KEY2_INT_EXTI_PINSOURCE   EXTI_PinSource13
#define KEY2_INT_EXTI_IRQ         EXTI15_10_IRQn
#define KEY2_IRQHANDLER           EXTI15_10_IRQHandler


void EXTI_Key_Config(void);

#endif /* __LED_H */
