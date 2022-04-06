#include "stm32f10x.h"
#include "led.h"
#include "delay.h"

void my_delay_init(void)
{
    ((SysTick_Type *)(0xE000E010))->CTRL &= ~(1 << 2); // SysTick 设为8分频
}

void my_delay_ms(u16 nms)
{
    ((SysTick_Type *)(0xE000E010))->LOAD = (u32)nms * 9000; // 重装初值
    ((SysTick_Type *)(0xE000E010))->VAL = 0x00;             // 清空计数器
    ((SysTick_Type *)(0xE000E010))->CTRL |= 0x01;           // 启动计数(SysTick使能)

    while (!(((SysTick_Type *)(0xE000E010))->CTRL & (1<<16)))
        ; // 等待时间到达
    ((SysTick_Type *)(0xE000E010))->CTRL &= ~(1 << 0); // 关闭计数器
}
int main(void)
{
    LED_Init();
    delay_init();
    while (1)
    {
        LED_On();
        my_delay_ms(500);
        // delay_ms(500);
        LED_Off();
        my_delay_ms(500);
        // delay_ms(500);
    }
}
