#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "timer3.h"

int main(void)
{
    // TIM1时钟使能，别问为啥，反正不加这个 Proteus 就报错
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
    LED_Init();
    delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    TIM3_Init(999, 7199);

    while (1)
    {
    }
}
