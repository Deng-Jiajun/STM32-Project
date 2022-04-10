#include "sys.h"

void My_USART1(void)
{
	/*
		1. 串口时钟、GPIO 时钟使能
		RCC_APB2PeriphClockCmd();
		2. GPIO 端口模式设置
		GPIO_Init();
		3. 串口参数初始化
		USART_Init();
		4. 开启中断并且初始化 NVIC
		NVIC_Init();
		USART_ITConfig();
		5. 串口使能
		USART_Cmd();
		6. 编写中断处理函数
		USARTx_IRQHandler();
	*/

	// 串口初始化结构体
	USART_InitTypeDef USART_InitStructure;

	// GPIO 初始化结构体
	GPIO_InitTypeDef GPIO_InitStructure;

	// NVIC 初始化结构体
	NVIC_InitTypeDef NVIC_InitStructure;

	// 串口时钟、GPIO 时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

	// 串口初始化
	USART_InitStructure.USART_BaudRate = 9600;										// 波特率 9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						// 8 位数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							// 1 位停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;								// 不进行奇偶校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					// 收/发模式
	USART_Init(USART1, &USART_InitStructure);

	// GPIO A9 初始化
	GPIO_InitStructure.GPIO_Pin = USART1_GPIO_PIN_TX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* A9 已经初始化结束了，GPIO_InitStructure 可以赋别的值继续用 */

	// GPIO A10 初始化
	GPIO_InitStructure.GPIO_Pin = USART1_GPIO_PIN_RX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// 开启中断并且初始化 NVIC
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // 开启 USART1 的接收中断
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// 串口使能
	USART_Cmd(USART1, ENABLE);

	// 编写中断处理函数👇
}

// USART1 的接收中断处理函数
void USART1_IRQHandler(void)
{
	// 接收到的数据
	uint8_t data;

	// 如果接收到数据
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		// 读取数据
		data = USART_ReceiveData(USART1);

		// 发送数据
		USART_SendByte(USART1, data);
	}
}

// USART_SendData 修改得到的
void USART_SendByte(USART_TypeDef *USARTx, uint16_t Data)
{
	/* Check the parameters */
	assert_param(IS_USART_ALL_PERIPH(USARTx));
	assert_param(IS_USART_DATA(Data));

	/* Transmit Data */
	USARTx->DR = (Data & (uint16_t)0x01FF);
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
		;
}

void USART_SendString(USART_TypeDef *USARTx, char *str)
{
	while (*str != '\0')
	{
		USART_SendByte(USARTx, *str++);
	}
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
		;
}

unsigned int counter = 0;
// USART_ReceiveData 修改得到的
uint8_t USART_ReceieByte(USART_TypeDef *USARTx)
{
	/* Check the parameters */
	assert_param(IS_USART_ALL_PERIPH(USARTx));

	while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET)
		;
	return (uint16_t)(USARTx->DR & (uint16_t)0x01FF);
}

typedef struct __FILE FILE;
#pragma import(__use_no_semihosting)
struct __FILE
{
	int handle;
};
FILE __stdout;
_sys_exit(int x)
{
	x = x;
}

int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t)ch);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
		;
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
		;
	return (ch);
}

int fgetc(FILE *f)
{
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
		;
	return (int)USART_ReceiveData(USART1);
}
