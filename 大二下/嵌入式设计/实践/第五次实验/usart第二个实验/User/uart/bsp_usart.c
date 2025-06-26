#include "./uart/bsp_usart.h"


// ����Usart, know how to explain the config
void usartx_Config(void)
{
	// �����ʼ���ṹ�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	// ��ʵ��ʹ�ô���1���Լ�PA9 PA10 ����GPIO��
	// ��˿�������1 PA9 PA10 ����GPIO�ĵ�ʱ��
	RCC_AHB1PeriphClockCmd(USARTx_RX_GPIO_CLK|USARTx_TX_GPIO_CLK,ENABLE);
	USARTx_CLOCKCMD(USARTx_CLK, ENABLE);

	// IO�ڳ�ʼ��
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin =   USARTx_TX_PIN;
	GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  USARTx_RX_PIN;
	GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStructure);
	/*USART1ͨ����Ҫʹ�õ�PA9��PA10�ϵ��Ĭ�ϲ����䷢�ͺͽ���
	���ţ���Ҫ���ж˿ڸ������ú���ǣ��������I/O�ڵĶ˿ڸ���*/
	GPIO_PinAFConfig(USARTx_RX_GPIO_PORT,USARTx_RX_SOURCE,USARTx_RX_AF);
	GPIO_PinAFConfig(USARTx_TX_GPIO_PORT,USARTx_TX_SOURCE,USARTx_TX_AF);
	// USART��ʼ��
	USART_InitStructure.USART_BaudRate = USARTx_BAUDRATE;					// ������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		// 8λ�ֳ�
	USART_InitStructure.USART_StopBits = USART_StopBits_1;				// һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;						// ����żУ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;																// ��Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		// �շ�ȫ˫��ģʽ

	USART_Init(USARTx, &USART_InitStructure); 										// �����ϲ������ÿ⺯����ʼ��

	USART_Cmd(USARTx, ENABLE);																		// ��������

}


///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		USART_SendData(USARTx, (uint8_t) ch);	
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);		
		return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);
		return (int)USART_ReceiveData(USARTx);
}
/*****************************END OF FILE**********************/
