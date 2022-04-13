#include "stm32f10x.h" // Device heade
#include "Delay.h"

// LED 流水灯
int main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;			  // 建立 GPIO 初始化结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 通用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;		  // 所有针脚全打开
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 50Hz

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 打开 GPIO A 时钟

	// 以 GPIO_InitStructure 设定的配置初始化 GPIO A
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	while (1)
	{
		// /* 手动方式 */
		// // 这里 Set 和 Reset 写反了，变成了 LED 轮流灭一盏
		// GPIO_SetBits(GPIOA, GPIO_Pin_1);
		// Delay_ms(50000);
		// GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		// GPIO_SetBits(GPIOA, GPIO_Pin_2);
		// Delay_ms(50000);
		// GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		// GPIO_SetBits(GPIOA, GPIO_Pin_3);
		// Delay_ms(50000);
		// GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		// GPIO_SetBits(GPIOA, GPIO_Pin_4);
		// Delay_ms(50000);
		// GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		// GPIO_SetBits(GPIOA, GPIO_Pin_5);
		// Delay_ms(50000);
		// GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		// GPIO_SetBits(GPIOA, GPIO_Pin_6);
		// Delay_ms(50000);
		// GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		// GPIO_SetBits(GPIOA, GPIO_Pin_7);
		// Delay_ms(50000);
		// GPIO_ResetBits(GPIOA, GPIO_Pin_7);
		// GPIO_SetBits(GPIOA, GPIO_Pin_8);
		// Delay_ms(50000);
		// GPIO_ResetBits(GPIOA, GPIO_Pin_8);

		/* 循环方式 */
		int i;
		// 一共接了 8 个灯，对应 pa1~pa8（别问我为什么不是从 0 开始，接错了）
		for (i = 0; i != 8; i++)
		{
			GPIO_Write(GPIOA, ~(0x1 << (i + 1))); // 品
			Delay_ms(50000);
		}
	}
}

// LED 闪烁
int main_LED_Bink(void)
{
	/* 寄存器写法
		// 直接写 = 不规范嗷
		RCC->APB2ENR = 0X00000010; // 打开 GPIO C 时钟
		GPIOC->CRH = 0x00300000;   // 配置 C13 针脚的模式（通用推挽输出）
		GPIOC->ODR = 0x00002000;   // 配置 C13 针脚电平（0 是亮）
	*/

	/* 库函数写法 */
	GPIO_InitTypeDef GPIO_InitStructure;			  // 建立 GPIO 初始化结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 通用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;		  // 针脚13
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 50Hz

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // 打开 GPIO C 时钟

	// 以 GPIO_InitStructure 设定的配置初始化 GPIO C
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	// GPIO_SetBits(GPIOC, GPIO_Pin_13); // 将 PC13 设为高电平
	// GPIO_ResetBits(GPIOC, GPIO_Pin_13); // 将 PC13 设为低电平
	// GPIO_WriteBit(GPIOC, GPIO_Pin_13,Bit_SET); // 将 PC13 设为高电平
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET); // 将 PC13 设为低电平

	while (1)
	{
		// 为了在Proteus 显示出效果，延迟设的很长，同时Proteus的晶振设置为 12Mhz
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
		Delay_ms(50000);
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
		Delay_ms(50000);
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		Delay_ms(50000);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		Delay_ms(50000);
	}
}
