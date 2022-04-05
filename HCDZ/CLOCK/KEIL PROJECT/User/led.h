#ifndef _LED_H_
#define _LED_H_
#include "stm32f10x.h"


#define LED_CLK RCC_APB2Periph_GPIOC
#define LED_PIN GPIO_Pin_13
#define LED_PORT GPIOC

/**
 * @brief LED 初始化
 * 
 */
void LED_Init(void);


/**
 * @brief 打开 LED
 * 
 */
void LED_On(void);


/**
 * @brief 关闭 LED
 * 
 */
void LED_Off(void);


#endif