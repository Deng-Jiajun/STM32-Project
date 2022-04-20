#include "stm32f10x.h"

/* LED 初始化函数 */
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*  2 个 LED 连接在 PA1 和 PA2 */

	/* 开启 GPIO A 的时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);

	/* 初始化 GPIO A1 和 A2 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* 先关闭 LED1 和 LED2 */
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
}

/* LED1 点亮 */
void LED1_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}

/* LED1 熄灭 */
void LED1_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
}

/* LED2 点亮 */
void LED2_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
}

/* LED2 熄灭 */
void LED2_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
}

/* LED1 反转 */
void LED1_Toggle(void){
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1)==0){
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
	}
	else{
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	}
}

/* LED2 反转 */
void LED2_Toggle(void){
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2)==0){
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
	}
	else{
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	}
}
