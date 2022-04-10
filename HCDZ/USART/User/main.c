#include "sys.h"

// MODE COM1 9600,0,8,1
// ASSIGN COM1<S1IN>S1OUT

int main(void)
{
	u16 temp;
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); // proteus 仿真要加这句
	//LED_GPIO_Config();
	//delay_init();
	// TIM2_Init(4999,7199);
	// TIM3_Init(9999,7199);

	// USART1 初始化
	My_USART1();

	// USART_ClearFlag(USART1,USART_FLAG_TC);
	// // while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	// USART_SendData(USART1, 'I');
	// while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	// USART_SendData(USART1, 'J');
	// while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	// USART_SendData(USART1, 'K');
	// 	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	// USART_SendData(USART1, 'L');
	// 	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	// USART_SendData(USART1, 'M');
	// 	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	// USART_SendData(USART1, 'N');


	//USART_SendString(USART1, "你好，世界！\r\nHello World!\r\n");


	printf("你好，世界！Hello World!\r\n");
	while (1)
	{
		// temp = USART_ReceieByte(USART1);
		// USART_SendByte(USART1, temp);


	}
}
