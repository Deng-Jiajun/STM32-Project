#include "stm32f10x.h"

/* LED 初始化函数 */
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*  2 个 LED 连接在 PA7 和 PA8 */

	/* 开启 GPIO A 的时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);

	/* 初始化 GPIO A1 和 A2 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* 先关闭 LED1 和 LED2 */
	GPIO_SetBits(GPIOA, GPIO_Pin_7 | GPIO_Pin_8);
}

uint8_t l1;
uint8_t l2;

/* LED1 点亮 */
void LED1_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);
	l1=1;
}

/* LED1 熄灭 */
void LED1_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
	l1=0;
}

/* LED2 点亮 */
void LED2_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
	l2=1;
}

/* LED2 熄灭 */
void LED2_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
	l2=0;
}

/* LED1 反转 */
void LED1_Toggle(void){
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_7)==0){
		GPIO_SetBits(GPIOA, GPIO_Pin_7);
	}
	else{
		GPIO_ResetBits(GPIOA, GPIO_Pin_7);
	}
}

/* LED2 反转 */
void LED2_Toggle(void){
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_8)==0){
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
	}
	else{
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
	}
}
