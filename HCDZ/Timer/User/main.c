#include "sys.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// proteus 仿真要加这句
	LED_GPIO_Config();
	delay_init();

	TIM2_Init(4999,7199);
	TIM3_Init(9999,7199);
	while(1)
	{
		
	}
}
