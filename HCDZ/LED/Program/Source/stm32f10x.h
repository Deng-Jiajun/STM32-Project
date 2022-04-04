#ifndef _STM32F10X_H_
#define _STM32F10X_H_

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

// 寄存器地址
// #define RCC_APB2ENR *(unsigned int *)0x40021018
// #define GPIOC_CRH *(unsigned int *)0x40011004
// #define GPIOC_ODR *(unsigned int *)0x4001100C

// 总线基地址
#define PERIPH_BASE ((unsigned int)0x40000000)
#define APB1PERIPH_BASE PERIPH_BASE
#define APB2PERIPH_BASE (PERIPH_BASE + 0x00010000)
#define AHBPERIPH_BASE (PERIPH_BASE + 0x00020000)
/* 👆AHB 基地址从 0x00020000开始
 * 从库函数的 stm32f10x.h 查表可以看到，SDIO_BASE 单独设置为从 0x00018000 开始
 */

// 根据总线得到的 GPIOC 的寄存器基地址
#define GPIOC_BASE (APB2PERIPH_BASE + 0x00001000)

// GPIOC 各个寄存器（从地址中取出）
#define GPIOC_CRL *(unsigned int *)(GPIOC_BASE + 0x00)
#define GPIOC_CRH *(unsigned int *)(GPIOC_BASE + 0x04)
#define GPIOC_IDR *(unsigned int *)(GPIOC_BASE + 0x08)
#define GPIOC_ODR *(unsigned int *)(GPIOC_BASE + 0x0C)
#define GPIOC_BSRR *(unsigned int *)(GPIOC_BASE + 0x10)
#define GPIOC_BRR *(unsigned int *)(GPIOC_BASE + 0x14)
#define GPIOC_LCKR *(unsigned int *)(GPIOC_BASE + 0x18)

// RCC 复位和时钟控制
#define RCC_BASE (AHBPERIPH_BASE + 0x1000)
#define RCC_APB2ENR *(unsigned int *)(RCC_BASE + 0x18)

/**
 * @brief GPIO 寄存器对应的结构体
 *        结构体成员为 GPIO 相关的各种寄存器
 *
 */
typedef struct
{
    uint32_t CRL;
    uint32_t CRH;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
    uint32_t BRR;
    uint32_t LCKR;
} GPIO_TypeDef;

#define GPIOC ((GPIO_TypeDef *)GPIOC_BASE)

/**
 * @brief RCC 复位和时钟控制寄存器对应的结构体
 *        结构体成员为 RCC 相关的各种寄存器
 *
 */
typedef struct
{
    uint32_t CR;
    uint32_t CFGR;
    uint32_t CIR;
    uint32_t APB2RSTR;
    uint32_t APB1RSTR;
    uint32_t AHBENR;
    uint32_t APB2ENR;
    uint32_t APB1ENR;
    uint32_t BDCR;
    uint32_t CSR;
} RCC_TypeDef;

#define RCC ((RCC_TypeDef *)RCC_BASE)

#endif
