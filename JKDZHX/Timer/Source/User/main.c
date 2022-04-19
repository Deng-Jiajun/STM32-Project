#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "Timer.h"

uint16_t counter = 0;

 #define TURN_OFF_OLED
// #define TEST_TIMER_INTERRUPT
// #define TEST_OLED_DISPLAY
//#define TEST_EXTERNAL_CLOCK_INTERRUPT


#ifdef TEST_EXTERNAL_CLOCK_INTERRUPT

int main(void)
{
	OLED_Init();
	External_Clock_Timer_Init();
	OLED_ShowString(1, 1, "Counter:");
	OLED_ShowString(2, 1, "CNT:");
	while (1)
	{
		OLED_ShowNum(1, 9, counter,5);

		/* TIM_Period=10000，可以看到 OLED 上 CNT 从 0~9999 循环
		   修改 TIM_Period、TIM_Prescaler 的值，可以看到相应的变化 */
		OLED_ShowNum(2, 9, TIM_GetCounter(TIM2),5); 

	}
}
#endif

#ifdef TEST_EXTERNAL_CLOCK

int main(void)
{
	OLED_Init();
	Timer_Init();
	OLED_ShowString(1, 1, "Counter:");
	OLED_ShowString(2, 1, "CNT:");
	while (1)
	{
		OLED_ShowNum(1, 9, counter,5);

		/* TIM_Period=10000，可以看到 OLED 上 CNT 从 0~9999 循环
		   修改 TIM_Period、TIM_Prescaler 的值，可以看到相应的变化 */
		OLED_ShowNum(2, 9, TIM_GetCounter(TIM2),5); 

	}
}
#endif

#ifdef TEST_OLED_DISPLAY
int main(void)
{
	OLED_Init();
	OLED_Clear();
	OLED_ShowChar(1, 1, 'A');
	OLED_ShowString(1, 3, "HelloWorld!");
	OLED_ShowNum(2, 1, 12345, 5);
	OLED_ShowSignedNum(2, 7, -66, 2);
	OLED_ShowHexNum(3, 1, 0xAA55, 4);
	OLED_ShowBinNum(4, 1, 0xAA55, 16);
	while (1)
	{
	}
}
#endif

// 环保懂不懂？
#ifdef TURN_OFF_OLED
int main(void){
	OLED_Init();
	OLED_Clear();
}
#endif
