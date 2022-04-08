#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"

int main(void)
{
    LED_GPIO_Config();
    delay_init();
    KEY_GPIO_Config();

    while (1)
    {
        KEY_Scan();
        LED_Change();
    }
}
