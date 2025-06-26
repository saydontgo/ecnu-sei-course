#include "./uart/bsp_usart.h"


// 配置Usart, know how to explain the config
void usartx_Config(void)
{
	// 定义初始化结构体变量
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	// 本实验使用串口1，以及PA9 PA10 两个GPIO口
	// 因此开启串口1 PA9 PA10 这组GPIO的的时钟
	RCC_AHB1PeriphClockCmd(USARTx_RX_GPIO_CLK|USARTx_TX_GPIO_CLK,ENABLE);
	USARTx_CLOCKCMD(USARTx_CLK, ENABLE);

	// IO口初始化
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin =   USARTx_TX_PIN;
	GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  USARTx_RX_PIN;
	GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStructure);
	/*USART1通信需要使用的PA9和PA10上电后默认不是其发送和接收
	引脚，需要进行端口复用设置后才是，这里进行I/O口的端口复用*/
	GPIO_PinAFConfig(USARTx_RX_GPIO_PORT,USARTx_RX_SOURCE,USARTx_RX_AF);
	GPIO_PinAFConfig(USARTx_TX_GPIO_PORT,USARTx_TX_SOURCE,USARTx_TX_AF);
	// USART初始化
	USART_InitStructure.USART_BaudRate = USARTx_BAUDRATE;					// 波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		// 8位字长
	USART_InitStructure.USART_StopBits = USART_StopBits_1;				// 一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;						// 无奇偶校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;																// 无硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		// 收发全双工模式

	USART_Init(USARTx, &USART_InitStructure); 										// 用以上参数调用库函数初始化

	USART_Cmd(USARTx, ENABLE);																		// 开启串口

}


///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		USART_SendData(USARTx, (uint8_t) ch);	
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);		
		return (ch);
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);
		return (int)USART_ReceiveData(USARTx);
}
/*****************************END OF FILE**********************/
