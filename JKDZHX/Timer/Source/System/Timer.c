#include "stm32f10x.h"

extern uint16_t counter;

// 定时器2初始化，频率为1Hz（1 秒中断一次）
void Timer_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// 开启定时器2的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	// 使用内部时钟（没配置的话，默认就是内部时钟，所以这句可以不写）
	TIM_InternalClockConfig(TIM2);

	/*
	TIM_Prescaler = 7200-1，72MHz 进行 7200 分频，得到 10kHz，即计数频率为 10kHz
	TIM_Period    = 10000-1，计数器以 10kHz 计数 10000 次，即 1s
	 */
	// 初始化定时器2的时基单元
	TIM_TimeBaseInitStructure.TIM_Period = 10000;					// 周期（=自动重装器的值）
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;				// 预分频器的值
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		// 采样频率分频系数
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
	// TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; // 重复计数器的值，TIM1 和 TIM8 才有效
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

	TIM_ClearFlag(TIM2, TIM_FLAG_Update); // 清除更新标志（避免一上电就触发中断）

	// 开启定时器2的中断，定时器中断源为 TIM_IT_Update
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	// 初始化 NVIC
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;			  // 中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // 抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		  // 响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // 通道使能
	NVIC_Init(&NVIC_InitStructure);

	// 启动定时器2
	TIM_Cmd(TIM2, ENABLE);
}

// 定时器2中断处理程序
void TIM2_IRQHandler(void)
{
	// 判断的定时器中断源是初始化的时设定的 TIM_IT_Update
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) // 检查更新中断发生与否
	{
		counter++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // 清除中断标志
	}
}

// 外部时钟(ETR)
void External_Clock_Timer_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	// 开启定时器2的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	// 开启GPIOA的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	// 初始化 GPIOA
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// 使用外部时钟
	// 定时器2，不分频，高电平/上升沿触发，不用滤波器（bookxnotepro://opennote/?nb={01a25f6c-fe16-454c-8f38-591392487e16}&book=47f07b86a273b11dbbc9034f7a90f448&page=283&x=176&y=448&id=193）
	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);

	/*
	TIM_Prescaler = 0，不分频
	TIM_Period    = 10-1，数到 10 中断一次
	 */
	// 初始化定时器2的时基单元
	TIM_TimeBaseInitStructure.TIM_Period = 10;					// 周期（=自动重装器的值）
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;				// 预分频器的值
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		// 采样频率分频系数
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
	// TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; // 重复计数器的值，TIM1 和 TIM8 才有效
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

	TIM_ClearFlag(TIM2, TIM_FLAG_Update); // 清除更新标志（避免一上电就触发中断）

	// 开启定时器2的中断，定时器中断源为 TIM_IT_Update
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	// 初始化 NVIC
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;			  // 中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // 抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		  // 响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // 通道使能
	NVIC_Init(&NVIC_InitStructure);

	// 启动定时器2
	TIM_Cmd(TIM2, ENABLE);
}
