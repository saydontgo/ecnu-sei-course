#ifndef __KEY_H
#define	__KEY_H

#include "stm32f4xx.h"

//���Ŷ���
#define KEY1_INT_GPIO_PIN         GPIO_Pin_0                 
#define KEY1_INT_GPIO_PORT        GPIOA
#define KEY1_INT_GPIO_CLK         RCC_AHB1Periph_GPIOA

#define KEY1_INT_EXTI_LINE        EXTI_Line0
#define KEY1_INT_EXTI_PORTSOURCE  EXTI_PortSourceGPIOA
#define KEY1_INT_EXTI_PINSOURCE   EXTI_PinSource0
#define KEY1_INT_EXTI_IRQ         EXTI0_IRQn
#define KEY1_IRQHANDLER           EXTI0_IRQHandler

/** �������±��ú�
	 * ��������Ϊ�ߵ�ƽ������ KEY_ON=1�� KEY_OFF=0
 * ����������Ϊ�͵�ƽ���Ѻ����ó�KEY_ON=0 ��KEY_OFF=1 ����
	 */
/*#define KEY_ON	0
  #define KEY_OFF	1
  void Key_GPIO_Config(void);
  uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);
*/
void EXTI_Key_Config(void);

#endif /* __LED_H */
