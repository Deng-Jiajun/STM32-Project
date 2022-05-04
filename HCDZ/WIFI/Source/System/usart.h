#ifndef __USART_H
#define __USART_H

#define USART1_GPIO GPIOA
#define USART1_TX_PIN GPIO_Pin_9
#define USART1_RX_PIN GPIO_Pin_10

#define USART2_GPIO GPIOA
#define USART2_TX_PIN GPIO_Pin_2
#define USART2_RX_PIN GPIO_Pin_3


#define USART1_TX_BUFFER_SIZE 1024 // USART1 输出缓冲区大小

#define USART2_TX_BUFFER_SIZE 1024 // USART2 输出缓冲区大小
#define USART2_RX_BUFFER_SIZE 1024 // USART2 输入缓冲区大小

/* 向外暴露缓冲区信息 */

extern char USART2_Rx_Buffer[USART2_RX_BUFFER_SIZE];
extern uint8_t USART2_Rx_Length;

/* ----- USART1 用于重定向 printf 函数 ----- */

void USART1_Init(void);
void USART1_Printf(char *fmt, ...);

/* USART2 用于连接 WiFi 模块，作为向 esp8266(esp-01s) 发送 AT 指令的串口 */

void USART2_Init(void);
void USART2_Printf(char *fmt, ...);

/* 💡USART1 和 USART2 的中断处理函数位于 usart.c */

#endif
