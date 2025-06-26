#include "stm32f4xx.h"

/*引脚定义*/

/*绿色LED灯*/
#define LED1_PIN GPIO_Pin_12
#define LED1_GPIO GPIOB
#define LED1_CLK RCC_AHB1Periph_GPIOB

/*初始化函数的说明*/
void LED_Config(void);
