#include "stm32f10x.h" // Device heade

int main(void)
{

	int a = 0;
	int b = 0;

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
	GPIO_SetBits(GPIOC, GPIO_Pin_13); // 将 PC13 设为高电平
	// GPIO_ResetBits(GPIOC, GPIO_Pin_13); // 将 PC13 设为低电平

	while (1)
	{
		a++;
		if (a % 2 == 1)
		{
			// GPIOC->ODR = 0x00002000;
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
		}
		else
		{
			// GPIOC->ODR = 0x00000000;
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		}

		for (b = 0; b < 1000; b++)
		{
		}
	}
}
