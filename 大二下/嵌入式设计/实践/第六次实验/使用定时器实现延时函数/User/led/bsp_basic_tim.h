#ifndef __BASIC_TIM_H
#define	__BASIC_TIM_H
#include "stm32f4xx.h"

#define BASIC_TIM           		TIM7
#define BASIC_TIM_CLK       		RCC_APB1Periph_TIM7

#define BASIC_TIM_IRQn			TIM7_IRQn
#define BASIC_TIM_IRQHandler    TIM7_IRQHandler

void TIMx_Configuration(void);

#endif /* __BASIC_TIM_H */
