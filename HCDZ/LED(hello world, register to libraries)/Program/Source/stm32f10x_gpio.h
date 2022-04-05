#ifndef _STM32F10X_GPIO_H_
#define _STM32F10X_GPIO_H_

#include "stm32f10x.h"

/* GPIO_Pin_x 针脚宏定义（从库里复制的），注意看数值，实际上是 1 在不断左移 */
#define GPIO_Pin_0 ((uint16_t)0x0001) // 0x 0000 0000 0000 0001
#define GPIO_Pin_1 ((uint16_t)0x0002) // 0x 0000 0000 0000 0010
#define GPIO_Pin_2 ((uint16_t)0x0004) // 0x 0000 0000 0000 0100
#define GPIO_Pin_3 ((uint16_t)0x0008)
#define GPIO_Pin_4 ((uint16_t)0x0010)
#define GPIO_Pin_5 ((uint16_t)0x0020)
#define GPIO_Pin_6 ((uint16_t)0x0040)
#define GPIO_Pin_7 ((uint16_t)0x0080)
#define GPIO_Pin_8 ((uint16_t)0x0100)
#define GPIO_Pin_9 ((uint16_t)0x0200)
#define GPIO_Pin_10 ((uint16_t)0x0400)
#define GPIO_Pin_11 ((uint16_t)0x0800)
#define GPIO_Pin_12 ((uint16_t)0x1000)
#define GPIO_Pin_13 ((uint16_t)0x2000)
#define GPIO_Pin_14 ((uint16_t)0x4000)
#define GPIO_Pin_15 ((uint16_t)0x8000)
#define GPIO_Pin_All ((uint16_t)0xFFFF)

/**
 * @brief GPIO 模式枚举
 *
 */
typedef enum
{
    GPIO_Mode_AIN = 0x0,          // 模拟输出
    GPIO_Mode_IN_FLOATING = 0x04, // 浮空输入
    GPIO_Mode_IPD = 0x28,         // 下拉输出
    GPIO_Mode_IPU = 0x48,         // 上拉输出

    GPIO_Mode_Out_OD = 0x14, // 通用开漏输出
    GPIO_Mode_Out_PP = 0x10, // 通用推挽输出
    GPIO_Mode_AF_OD = 0x1C,  // 复用开漏输出
    GPIO_Mode_AF_PP = 0x18   // 复用推挽输出
} GPIOMode_TypeDef;

/**
 * @brief GPIO 输出速度枚举
 *
 */
typedef enum
{
    GPIO_Speed_10MHz = 1,
    GPIO_Speed_2MHz,
    GPIO_Speed_50MHz
} GPIOSpeed_TypeDef;

/**
 * @brief GPIO 初始化结构体
 *
 */
typedef struct
{
    uint16_t GPIO_Pin;            // GPIO 对应的针脚，详见 GPIO_Pin_x 针脚定义
    GPIOSpeed_TypeDef GPIO_Speed; // 输出的速度，数值为枚举
    GPIOMode_TypeDef GPIO_Mode;   //输出模式，数值为枚举
} GPIO_InitTypeDef;


/**
 * @brief 设置某个 P 口的某个引脚为高电平
 *
 * @param GPIOx 某个 P 口的结构体指针
 * @param GPIO_Pin 某个针脚，值是宏定义的 GPIO_Pin_x（ x可以是 0~15，或者 All）
 */
void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/**
 * @brief 设置某个 P 口的某个引脚为低电平
 *
 * @param GPIOx 某个 P 口的结构体指针，x 可以是 A~E
 * @param GPIO_Pin 某个针脚
 */
void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);


/**
 * @brief GPIO 初始化函数
 * 
 * @param GPIOx 对应 GPIO 结构体
 * @param GPIO_InitStruct 配置好的 GPIO 初始化结构体
 */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);




#endif
