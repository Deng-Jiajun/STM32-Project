#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "Timer.h"
#include "PWM.h"

#define TIM3CH2 // 驱动呼吸灯
// #define TIM2CH1 // 驱动风扇

int main(void)
{
	uint8_t i = 0;
	// /* 库函数写法 */
	// GPIO_InitTypeDef GPIO_InitStructure;			  // 建立 GPIO 初始化结构体
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 通用推挽输出
	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;		  // 针脚13
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 50Hz

	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 打开 GPIO C 时钟

	// // 以 GPIO_InitStructure 设定的配置初始化 GPIO C
	// GPIO_Init(GPIOA, &GPIO_InitStructure);

	//  GPIO_ResetBits(GPIOA, GPIO_Pin_7); // 将 PA7 设为低电平

	// OLED_Init();

#ifdef TIM3CH2
	PWM_Init();
	while (1)
	{
		for (i = 20; i <= 100; i++)
		{
			TIM_SetCompare2(TIM3, i);
			Delay_ms(20);
		}
		for (; i >= 20; i--)
		{
			TIM_SetCompare2(TIM3, i);
			Delay_ms(20);
		}
	}
#endif

#ifdef TIM2CH1
	PWM_Init2();
	while (1)
	{
		for (i = 20; i <= 100; i++)
		{
			TIM_SetCompare1(TIM2, i);
			Delay_ms(20);
		}
		for (; i >= 20; i--)
		{
			TIM_SetCompare1(TIM2, i);
			Delay_ms(20);
		}
	}
#endif
}
