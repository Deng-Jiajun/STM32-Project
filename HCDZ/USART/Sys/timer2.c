#include "sys.h"

void TIM2_Init(u16 arr, u16 psc)
{
	// 定时器初始化结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	// NVIC 初始化结构体
	NVIC_InitTypeDef NVIC_InitStructure;

	// 使能定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	// 设置定时器初始化结构体的参数
	TIM_TimeBaseStructure.TIM_Period = arr;						// 重装载的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;					// 预分频的值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		// 不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数

	// 根据定时器初始化结构体初始化定时器
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	// 使能定时器中断
	TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);
	// 设置NVIC 初始化结构体的参数
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;			  // TIM3 的中断源
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // 抢占优先级 2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		  // 响应优先级 2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // 中断使能

	// 根据 NVIC 初始化结构体初始化 NVIC
	NVIC_Init(&NVIC_InitStructure);

	// 使能定时器
	TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void)
{
	static u8 i = 0;
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		switch (i)
		{
		case 0:
			GPIO_ResetBits(GPIOA, GPIO_Pin_15);
			i++;
			break;
		case 1:
			GPIO_SetBits(GPIOA, GPIO_Pin_15);
			i = 0;
			break;
		}
		// 清除标志位
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
