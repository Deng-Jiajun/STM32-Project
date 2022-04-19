#include "stm32f10x.h" // Device heade
#include "Delay.h"

int main(void)
{
	// 两个 LED 是 PA7 和 PA8
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// 初始化 GPIO A0 为输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	while (1)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_7);
		}

		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_7);
		}
	}
}


int main1(void)
{
	// 两个 LED 是 PA7 和 PA8
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// 初始化 GPIO A0 为输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	while (1)
	{
		// if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
		// {
		// 	GPIO_SetBits(GPIOA, GPIO_Pin_7);
		// 	while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
		// 		;
		// 	GPIO_ResetBits(GPIOA, GPIO_Pin_7);
		// }

		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_7);
			while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1)
				;
			GPIO_ResetBits(GPIOA, GPIO_Pin_7);
			Delay_s(1);
		}
	}
}
