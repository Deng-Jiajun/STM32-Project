#ifndef __USART_H
#define __USART_H

#define USART1_GPIO GPIOA
#define USART1_TX_PIN GPIO_Pin_9
#define USART1_RX_PIN GPIO_Pin_10

	
void USART1_Init(void);
void USART_SendByte(USART_TypeDef* USARTx, uint16_t Data);
void USART_SendString( USART_TypeDef * USARTx, char *str);
uint8_t USART_ReceieByte(USART_TypeDef *USARTx);

#endif
