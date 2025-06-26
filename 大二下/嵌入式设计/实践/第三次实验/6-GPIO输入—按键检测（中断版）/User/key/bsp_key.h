#ifndef __KEY_H
#define	__KEY_H

#include "stm32f4xx.h"

//���Ŷ���
/*******************************************************/
#define KEY1_PIN                  GPIO_Pin_8                
#define KEY1_GPIO_PORT            GPIOC                      
#define KEY1_GPIO_CLK             RCC_AHB1Periph_GPIOC

#define KEY1_INT_EXTI_LINE        EXTI_Line8
#define KEY1_INT_EXTI_PORTSOURCE  EXTI_PortSourceGPIOC
#define KEY1_INT_EXTI_PINSOURCE   EXTI_PinSource8
#define KEY1_INT_EXTI_IRQ         EXTI9_5_IRQn
#define KEY1_INT_EXTI_IRQHANDLER  EXTI9_5_IRQHandler


#define KEY2_PIN                  GPIO_Pin_13                 
#define KEY2_GPIO_PORT            GPIOC                      
#define KEY2_GPIO_CLK             RCC_AHB1Periph_GPIOC
/*******************************************************/

 /** �������±��ú�
	* ��������Ϊ�ߵ�ƽ������ KEY_ON=1�� KEY_OFF=0
	* ����������Ϊ�͵�ƽ���Ѻ����ó�KEY_ON=0 ��KEY_OFF=1 ����
	*/
#define KEY_ON	1
#define KEY_OFF	0


void Key_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);


void EXTI_Key_Config(void);

#endif /* __LED_H */

