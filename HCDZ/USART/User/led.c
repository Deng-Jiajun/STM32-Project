#include "sys.h"

extern u8 flag;

void LED_GPIO_Config(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	/* 💡Proteus 一盏灯的闪烁似乎有问题，再加一盏灯，接到 A15 */

	GPIO_InitTypeDef GPIO_InitStruct2;

	RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);
	GPIO_InitStruct.GPIO_Pin = LED_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStruct2.GPIO_Pin =GPIO_Pin_15;
	GPIO_InitStruct2.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct2.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
	GPIO_Init(GPIOA, &GPIO_InitStruct2);
}


void LED_Change()
{
	static u8 i = 0;
	if (flag == 1)
	{
		flag = 0;
		switch (i)
		{
		case 0:
			PCout(13) = 1;
			PAout(15) = 0;
			i++;
			break;
		case 1:
			PCout(13) = 0;
			PAout(15) = 1;
			i = 0;
			break;
		}
	}
}
