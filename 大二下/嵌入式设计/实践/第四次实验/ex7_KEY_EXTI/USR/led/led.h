#include "stm32f4xx.h"

/*���Ŷ���*/

/*��ɫLED��*/
#define LED1_PIN GPIO_Pin_12
#define LED1_GPIO GPIOB
#define LED1_CLK RCC_AHB1Periph_GPIOB

/*��ʼ��������˵��*/
void LED_Config(void);
