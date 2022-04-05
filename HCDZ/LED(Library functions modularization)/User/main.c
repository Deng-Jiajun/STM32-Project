#include "stm32f10x.h"
#include "led.h"

int main(void)
{
    int i = 0;
    int k = 0;

    LED_Init();
    while (1)
    {
        i++;
        if (i % 2 == 0)
            LED_On();
        else
            LED_Off();

        for (k = 0; k < 2000; k++)
        {
        }
    }
}
