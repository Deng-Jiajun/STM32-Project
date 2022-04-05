#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
int main()
{
    LED_Init();
    delay_init();
    while (1)
    {
        LED_On();
        delay_ms(100);
        LED_Off();
        delay_ms(100);
    }
}
