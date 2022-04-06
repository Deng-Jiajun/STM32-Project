#include "led.h"

// LED 初始化
void LED_Init(void)
{
    /* 通过创建 GPIO 初始化结构体，配置 GPIO 输出模式 */
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(LED_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin = LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);
}

// 点亮 LED
void LED_On(void)
{
    GPIO_SetBits(LED_PORT, LED_PIN);
}

// 关闭 LED
void LED_Off(void)
{
    GPIO_ResetBits(LED_PORT, LED_PIN);
}