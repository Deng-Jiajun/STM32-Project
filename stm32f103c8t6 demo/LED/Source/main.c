#include "stm32f10x.h" // Device heade
#include "Delay.h"

// LED 闪烁
int main(void)
{


	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	while (1)
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_RESET);
		Delay_ms(500);
		GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_SET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_RESET);
		Delay_ms(500);
		GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_SET);
	}
}
