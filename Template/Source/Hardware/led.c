#include "sys.h"


void __LED_Init(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint32_t __Get_RCC_APB2Periph_GPIOx(GPIO_TypeDef *GPIOx);
/* 👆内部使用的通用函数，不对外暴露（不在 .h 里声明)------- */

/* --- 对外暴露的函数，如果 LED 的针脚和数量改变了，修改这部分函数 --- */

/**
 * @brief LED 初始化函数。
 *        如果 LED 的针脚和数量改变了，修改这个函数即可
 */
void LED_Init(void)
{
    /* 初始化 LED1（PA7）和 LED2（PA8） */
    __LED_Init(LED1_GPIO, LED1_PIN | LED2_PIN);

    /* 初始化之后关灯 */
    GPIO_SetBits(LED1_GPIO, LED1_PIN | LED2_PIN);
}

/**
 * @brief 开启 LED。
 *        如果 LED 的针脚和数量改变了，修改这个函数即可
 *
 * @param led_num 要开启的 LED 编号，从 1 开始
 */
void LED_On(uint8_t led_num)
{
    if (led_num == 1)
    {
        GPIO_ResetBits(LED1_GPIO, LED1_PIN);
    }
    else if (led_num == 2)
    {
        GPIO_ResetBits(LED2_GPIO, LED2_PIN);
    }
}

/**
 * @brief 关闭 LED。
 *        如果 LED 的针脚和数量改变了，修改这个函数即可
 *
 * @param led_num 要开启的 LED 编号，从 1 开始
 */
void LED_Off(uint8_t led_num)
{
    if (led_num == 1)
    {
        GPIO_SetBits(LED1_GPIO, LED1_PIN);
    }
    else if (led_num == 2)
    {
        GPIO_SetBits(LED2_GPIO, LED2_PIN);
    }
}

/**
 * @brief 翻转 LED。
 *        如果 LED 的针脚和数量改变了，修改这个函数即可
 *
 * @param led_num 要开启的 LED 编号，从 1 开始
 */
void LED_Toggle(uint8_t led_num)
{
    /* ❗stm32f10x_gpio 没有定义 GPIO_ToggleBits() 这个函数 */

    if (led_num == 1)
    {
        if (GPIO_ReadOutputDataBit(LED1_GPIO, LED1_PIN) == 0)
        {
            GPIO_SetBits(LED1_GPIO, LED1_PIN);
        }
        else
        {
            GPIO_ResetBits(LED1_GPIO, LED1_PIN);
        }
    }
    else if (led_num == 2)
    {
        if (GPIO_ReadOutputDataBit(LED2_GPIO, LED2_PIN) == 0)
        {
            GPIO_SetBits(LED2_GPIO, LED2_PIN);
        }
        else
        {
            GPIO_ResetBits(LED2_GPIO, LED2_PIN);
        }
    }
}

/* --- 👇内部通用函数，应该不需要修改，只需要修改上面的函数即可 --- */
/**
 * @brief 初始化 LED
 *
 * @param GPIOx LED 端口，可填 GPIOx（x=A..E）
 *
 * @param GPIO_Pin LED 端口对应的引脚，可填 GPIO_Pin_x (x=0..15)。
 *                 可以填多个引脚的组合，比如 GPIO_Pin_0 | GPIO_Pin_1
 */
void __LED_Init(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    /* GPIO 初始化结构体 */
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 参数检查 */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    /* 开启 GPIO 时钟 */
    RCC_APB2PeriphClockCmd(__Get_RCC_APB2Periph_GPIOx(GPIOx), ENABLE);

    /* 配置 GPIO 引脚 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
    /* 通用推挽输出 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    /* 输出速度 50MHz */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    /* 初始化 GPIO */
    GPIO_Init(GPIOx, &GPIO_InitStructure);
}

/**
 * @brief 根据 GPIOx 返回对应 RCC 寄存器的地址
 *
 * @param GPIOx 要查询的 GPIO 端口，可填 GPIOx（x=A..E）
 *
 * @return uint32_t 返回对应的 RCC 寄存器的地址，如果参数错误，返回 0
 * 
 * @retval RCC_APB2Periph_GPIOx(x=A..E) 对应的 RCC 寄存器的地址 
 * @retval 0 参数错误
 */
uint32_t __Get_RCC_APB2Periph_GPIOx(GPIO_TypeDef *GPIOx)
{
    /* 要返回的 RCC 寄存器地址 */
    uint32_t RCC_APB2Periph_GPIOx = 0;

    /* 参数检查 */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    /* 有考虑过用 switch，但是 GPIOx 不是一个整形常量表达式，要算出偏移地址来作为 case，实际上更不直观，不如直接一排 if 还更清晰一点 */
    if (GPIOx == GPIOA)
    {
        RCC_APB2Periph_GPIOx = RCC_APB2Periph_GPIOA;
    }
    else if (GPIOx == GPIOB)
    {
        RCC_APB2Periph_GPIOx = RCC_APB2Periph_GPIOB;
    }
    else if (GPIOx == GPIOC)
    {
        RCC_APB2Periph_GPIOx = RCC_APB2Periph_GPIOC;
    }
    else if (GPIOx == GPIOD)
    {
        RCC_APB2Periph_GPIOx = RCC_APB2Periph_GPIOD;
    }
    else if (GPIOx == GPIOE)
    {
        RCC_APB2Periph_GPIOx = RCC_APB2Periph_GPIOE;
    }
    else
    {
        RCC_APB2Periph_GPIOx = 0;
    }

    return RCC_APB2Periph_GPIOx;
}
