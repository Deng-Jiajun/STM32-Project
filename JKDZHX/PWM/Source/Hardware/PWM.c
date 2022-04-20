#include "stm32f10x.h"
#include "PWM.h"
/**
 * 呼吸灯，PA7
 * 查表得到，PA7 可复用作为 TIM3_CH2（定时器3的通道2）
 */
// PWM 初始化函数
void PWM_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	// GPIOA时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	// 初始化 GPIOA 的 PA7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出（由定时器而不是输出寄存器控制输出）
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// 定时器3时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	// 使用内部时钟（没配置的话，默认就是内部时钟，所以这句可以不写）
	TIM_InternalClockConfig(TIM3);

	/*
	TIM_Prescaler = 7200-1，72MHz 进行 7200 分频，得到 10kHz，即计数频率为 10kHz
	TIM_Period    = 10000-1，计数器以 10kHz 计数 10000 次，即 1s
	 */
	// 初始化定时器3的时基单元
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;					// 周期（=自动重装器 ARR 的值）
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1;				// 预分频器的值（PSC）
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		// 采样频率分频系数
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;			// 重复计数器的值，TIM1 和 TIM8 才有效
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_7);

	// 初始化输出比较单元
	TIM_OCStructInit(&TIM_OCInitStructure);						  // 初始化结构体(赋默认值，避免未定义情况)
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;			  // PWM 模式 1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 输出使能
	TIM_OCInitStructure.TIM_Pulse = 100;						  // 脉冲宽度(CCR 的值)
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	  // 输出极性，高电平有效
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);					  // 初始化 TIM3 的通道2

	// 启动定时器2
	TIM_Cmd(TIM3, ENABLE);
}

/* 想试试能不能驱动风扇，结果 3.3V 带不动 */
// PA0 可复用作为 TIM3_CH1（定时器3的通道1）
void PWM_Init2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
	//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; // GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_InternalClockConfig(TIM2);

	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;	   // ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1; // PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;		 // CCR
	TIM_OC1Init(TIM2, &TIM_OCInitStructure); // 初始化 TIM2 的通道1

	TIM_Cmd(TIM2, ENABLE);
}
