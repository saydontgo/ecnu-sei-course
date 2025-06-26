#ifndef __LED_H
#define	__LED_H

#include "stm32f4xx.h"

//���Ŷ���
/*******************************************************/
//R ��ɫ��
#define LED1_PIN                  GPIO_Pin_10                 
#define LED1_GPIO_PORT            GPIOH                      
#define LED1_GPIO_CLK             RCC_AHB1Periph_GPIOH

//G green light
#define LED2_PIN                  GPIO_Pin_11                 
#define LED2_GPIO_PORT            GPIOH                      
#define LED2_GPIO_CLK             RCC_AHB1Periph_GPIOH

//B blue light
#define LED3_PIN                  GPIO_Pin_12                 
#define LED3_GPIO_PORT            GPIOH                      
#define LED3_GPIO_CLK             RCC_AHB1Periph_GPIOH

/************************************************************/

/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)					{p->BSRRL=i;}			  //����Ϊ�ߵ�ƽ		
#define digitalLo(p,i)					{p->BSRRH=i;}				//����͵�ƽ
#define digitalToggle(p,i)		{p->ODR ^=i;}			//�����ת״̬


/* �������IO�ĺ� */
#define LED1_TOGGLE		digitalToggle(LED1_GPIO_PORT,LED1_PIN)
#define LED1_OFF				digitalHi(LED1_GPIO_PORT,LED1_PIN)
#define LED1_ON				digitalLo(LED1_GPIO_PORT,LED1_PIN)

#define LED2_TOGGLE		digitalToggle(LED2_GPIO_PORT,LED2_PIN)
#define LED2_OFF				digitalHi(LED2_GPIO_PORT,LED2_PIN)
#define LED2_ON				digitalLo(LED2_GPIO_PORT,LED2_PIN)

#define LED3_TOGGLE		digitalToggle(LED3_GPIO_PORT,LED3_PIN)
#define LED3_OFF				digitalHi(LED3_GPIO_PORT,LED3_PIN)
#define LED3_ON				digitalLo(LED3_GPIO_PORT,LED3_PIN)

// light it up
#define LED_RED   LED1_ON;LED2_OFF;LED3_OFF 
#define LED_GREEN   LED2_ON;LED1_OFF;LED3_OFF 
#define LED_BLUE   LED3_ON;LED2_OFF;LED1_OFF 


//�����
//#define LED_RED   LED1_ON;LED2_OFF;LED3_OFF 
//�����
//#define LED_RED_OFF LED1_OFF 


					
void LED_GPIO_Config(void);

#endif /* __LED_H */
