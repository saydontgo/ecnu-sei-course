#ifndef __BASIC_TIM_H
#define	__BASIC_TIM_H
#include "stm32f4xx.h"

 #define COLOR_LED1_PIN                  GPIO_Pin_10                
 #define COLOR_LED1_GPIO_PORT           GPIOH                      
 #define COLOR_LED1_GPIO_CLK            RCC_AHB1Periph_GPIOH
 #define COLOR_LED1_PINSOURCE		    	 GPIO_PinSource10
 #define COLOR_LED1_AF				 GPIO_AF_TIM5

 #define COLOR_LED2_PIN                  GPIO_Pin_11               
 #define COLOR_LED2_GPIO_PORT           GPIOH                      
 #define COLOR_LED2_GPIO_CLK            RCC_AHB1Periph_GPIOH
 #define COLOR_LED2_PINSOURCE		    	 GPIO_PinSource11
 #define COLOR_LED2_AF				 GPIO_AF_TIM5
 
 #define COLOR_LED3_PIN                  GPIO_Pin_12
 #define COLOR_LED3_GPIO_PORT           GPIOH                      
 #define COLOR_LED3_GPIO_CLK            RCC_AHB1Periph_GPIOH
 #define COLOR_LED3_PINSOURCE		    	 GPIO_PinSource12
 #define COLOR_LED3_AF				 GPIO_AF_TIM5
 
 // ¶¨Ê±Æ÷
 #define COLOR_TIM						TIM5
 #define COLOR_TIM_CLK					RCC_APB1Periph_TIM5
 #define COLOR_LED1_CCRx 				CCR1
 #define COLOR_LED2_CCRx				CCR2
 #define COLOR_LED3_CCRx				CCR3
 
 #define COLOR_LED1_TIM_CHANNEL						TIM_Channel_1
 #define COLOR_LED2_TIM_CHANNEL						TIM_Channel_2
 #define COLOR_LED3_TIM_CHANNEL						TIM_Channel_3
 
 #define COLOR_TIM_IRQn TIM5_IRQn
 #define COLOR_TIM_IRQHandler TIM5_IRQHandler
 
 /* RGB??? 24?*/
 #define COLOR_WHITE  0xFFFFFF
#define COLOR_BLACK   0x000000
#define COLOR_GREY    0xC0C0C0
#define COLOR_BLUE    0x0000FF
#define COLOR_RED  	  0xFF0000
#define COLOR_MAGENTA 0xFFOOFF
#define COLOR_GREEN   0x00FF00
#define COLOR_CYAN    0x00FFFF
#define COLOR_YELLOW  0xFFFFO0

void ColorLED_Config(void);
void SetRGBColor(uint32_t rgb);
void SetColorValue(uint8_t r,uint8_t g, uint8_t b);


#endif /* __BASIC_TIM_H */
