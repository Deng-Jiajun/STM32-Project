#ifndef _MY_USART_H_
#define _MY_USART_H_

#define USART1_GPIO_PIN_TX GPIO_Pin_9
#define USART1_GPIO_PIN_RX GPIO_Pin_10
	
void My_USART1(void);
void USART_SendByte(USART_TypeDef* USARTx, uint16_t Data);
void USART_SendString( USART_TypeDef * USARTx, char *str);
uint8_t USART_ReceieByte(USART_TypeDef *USARTx);

#endif
