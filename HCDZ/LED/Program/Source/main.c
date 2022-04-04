#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

int main(void)
{
    int i = 0, k;
    RCC->APB2ENR |= (1 << 4);         // 打开 GPIOC 时钟

    /* 通过创建 GPIO 初始化结构体，配置 GPIO 输出模式 */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_SetBits(GPIOC, GPIO_Pin_13); 
    // GPIO_ResetBits(GPIOC, GPIO_Pin_13); 
    while (1)
    {
        i++;
        if (i % 2 == 0)
            GPIO_SetBits(GPIOC, GPIO_Pin_13);
        else
            GPIO_ResetBits(GPIOC, GPIO_Pin_13);

        for (k = 0; k < 2000; k++)
        {
        }
    }
}

void SystemInit(void)
{
}
