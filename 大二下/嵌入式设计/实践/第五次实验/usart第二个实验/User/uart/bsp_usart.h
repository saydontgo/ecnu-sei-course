#ifndef __USART_H
#define	__USART_H

#include "stm32f4xx.h"
#include <stdio.h>

//????
/*******************************************************/

/* ?????????????,??????????,?????? 
 * ??1?6?      RCC_APB2PeriphClockCmd
 * ??2/3/4/5/7? RCC_APB1PeriphClockCmd
 */
#define USARTx                             USART1
#define USARTx_CLK                         RCC_APB2Periph_USART1
#define USARTx_CLOCKCMD                    RCC_APB2PeriphClockCmd
#define USARTx_BAUDRATE                    115200  //?????

#define USARTx_RX_GPIO_PORT                GPIOA
#define USARTx_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define USARTx_RX_PIN                      GPIO_Pin_10
#define USARTx_RX_AF                       GPIO_AF_USART1
#define USARTx_RX_SOURCE                   GPIO_PinSource10

#define USARTx_TX_GPIO_PORT                GPIOA
#define USARTx_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define USARTx_TX_PIN                      GPIO_Pin_9
#define USARTx_TX_AF                       GPIO_AF_USART1
#define USARTx_TX_SOURCE                   GPIO_PinSource9


 
 /* Exported functions ----------------------------------------------- */
void usartx_Config(void);

#endif /* __USART_H */
