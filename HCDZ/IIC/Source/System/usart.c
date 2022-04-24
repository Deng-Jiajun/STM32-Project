#include "sys.h"

/**
 * @brief USART 配置函数
 *
 */
void USART1_Config(void)
{
	/* USART 初始化结构体 */
	USART_InitTypeDef USART_InitStructure;

	/* GPIO 初始化结构体 */
	GPIO_InitTypeDef GPIO_InitStructure;

	/* NVIC 初始化结构体 */
	NVIC_InitTypeDef NVIC_InitStructure;

	/* 串口时钟 和 GPIO 时钟 使能 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

	/* ------------------ 串口参数配置 ------------------  */
	/* 串口波特率 9600 */
	USART_InitStructure.USART_BaudRate = 9600;
	/*  8 位数据位 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/*  1 位停止位 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/*  无奇偶校验 */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/*  无硬件数据流控制 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/*  收/发模式 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/*  串口初始化 */
	USART_Init(USART1, &USART_InitStructure);

	/* ------------------ 串口 GPIO 配置 ------------------ */
	/*  USART1_TX 初始化 */
	GPIO_InitStructure.GPIO_Pin = USART1_TX_PIN;
	/* 推挽复用输出 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART1_GPIO, &GPIO_InitStructure);

	/* USART1_TX 已经初始化结束了，GPIO_InitStructure 可以赋别的值继续用 */

	/*  USART1_RX 初始化 */
	GPIO_InitStructure.GPIO_Pin = USART1_RX_PIN;
	/* 浮空输入 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART1_GPIO, &GPIO_InitStructure);

	/* ------------------ 串口 NVIC 配置（接收中断） ------------------ */
	/*  开启 USART1 的接收中断 */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	/* NVIC 中断通道 */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	/* 抢占优先级 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	/* 响应优先级 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	/* 中断使能 */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	/* NVIC 初始化 */
	NVIC_Init(&NVIC_InitStructure);

	/*  USART 使能 */
	USART_Cmd(USART1, ENABLE);
}

/**
 * @brief USART1 的 接收中断 处理函数（就只是收到数据再发出去）
 */
void USART1_IRQHandler(void)
{
	/*  接收到的数据 */
	uint8_t data;

	/*  如果接收到数据（中断标志位不为 0） */
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		/* 读取数据（接收） */
		data = USART_ReceiveData(USART1);

		/* 发送数据（再发出去） */
		USART_SendByte(USART1, data);
	}
}

/* 💡 USART 的数据都会与上 0x01FF 是因为有效位就只有 9 位 */

/**
 * @brief 通过 USART 发送一个字符
 *
 * @param USARTx 通过哪个 USART 发送。
 * 				 可以填：USART1, USART2, USART3, UART4 和 UART5
 * @param Data 发送的数据（一个字符）
 *
 * @see USART_SendData
 */
void USART_SendByte(USART_TypeDef *USARTx, uint16_t Data)
{
	/* Check the parameters */
	assert_param(IS_USART_ALL_PERIPH(USARTx));
	assert_param(IS_USART_DATA(Data));

	/* Transmit Data */
	USARTx->DR = (Data & (uint16_t)0x01FF);

	/* TXE: Transmit data register Empty */
	/* 以上部分照搬自 USART_SendData，然后下面加上一个对标志位 TXE 的等待，
	   目的是避免出现数据覆盖（这一个字符还没发出去就被新字符覆盖了） */
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
		;
}

/**
 * @brief 通过 USART 发送字符串（实际上就是循环调用 USART_SendByte）
 *
 * @param USARTx 通过哪个 USART 发送。
 * 				 可以填：USART1, USART2, USART3, UART4 和 UART5
 * @param str 发送的字符串
 * @see USART_SendByte
 */
void USART_SendString(USART_TypeDef *USARTx, char *str)
{
	while (*str != '\0')
	{
		USART_SendByte(USARTx, *str++);
	}

	/* 这里对标志位 TC 的等待，作用与 USART_SendByte 中对标志位 TXE 的等待类似，
	   此处是确保整个字符串都传输完毕 (Transmission Complete) */
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
		;
}

/**
 * @brief 从 USART 接收字符
 *
 * @param USARTx 通过哪个 USART 接收。
 * 				 可以填：USART1, USART2, USART3, UART4 和 UART5
 * @return uint8_t 接收到的数据（一个字符）
 * @see USART_ReceiveData
 * @warning 这里会死等，直到接收到数据
 */
uint8_t USART_ReceieByte(USART_TypeDef *USARTx)
{
	/* Check the parameters */
	assert_param(IS_USART_ALL_PERIPH(USARTx));

	/* RXNE: Read data register not empty */
	/* USART_ReceiveData 总共两句，一句参数判断，一句返回数据
	   为了确认数据的有效性，加一个对标志位 RXNE 的等待 */
	while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET)
		;

	/* 最高位是停止位，直接丢掉不要了 */
	return (uint8_t)(USARTx->DR & (uint16_t)0x01FF);
}

/* ---------- printf 和 scanf 重定向到 USART1 ---------- */
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

	/* 感觉多加一句判断 TC 好像有点用 */
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
