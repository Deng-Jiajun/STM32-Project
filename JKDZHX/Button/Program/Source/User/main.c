#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"
#include "Key.h"

/* 模块化 */
int main(void){
	LED_Init();
	KEY_Init();
	while(1){
		if(KEY_Scan()==1){
			// LED1_ON();
			LED1_Toggle();
		}
		if(KEY_Scan()==2){
			// LED2_ON();
			LED2_Toggle();
		}
	}
}


/* 直接写在主函数里 */
int _led_and_key_in_main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* 按键连接 PB1 和 PB11，分别控制 连接在 PA1 和 PA2 的 LED */

	/* 开启 GPIO A 和 B 的时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

	/* 初始化 GPIO A1 和 A2 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* 初始化 GPIO B1 和 B11 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* 先关闭 LED1 和 LED2 */
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);

	while (1)
	{
		/* 按键按下，点亮 LED1 */
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		}
		/* 按键按下，点亮 LED2 */
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		}
		Delay_ms(100);
	}
}
