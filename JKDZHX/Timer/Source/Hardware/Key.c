#include "stm32f10x.h"
#include "Delay.h"

/* 按键初始化函数 */
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*  2 个按键连接在 PB1 和 PB11 */

	/* 开启 GPIO B 的时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);

	/* 初始化 GPIO B1 和 B11 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/* 读取按键值 */
uint8_t KEY_Scan(void)
{
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0);
		return 1;
	}
	else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0);
		return 2;
	}
	else
	{
		return 0;
	}
}
