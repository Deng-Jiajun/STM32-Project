#ifndef __SYS_H
#define __SYS_H

#include "stm32f10x.h"

#include "test.h"
#include "delay.h"
#include "key.h"
#include "led.h"
#include "usart.h"
#include "iic.h"
#include "rcc.h"
#include "assert_param.h"

#include "oled_iic.h"
#include "dht11.h"
#include "wifi.h"
#include "mqtt.h"

#include "stdio.h"
#include "string.h"
#include "stdarg.h"
#include "stdint.h"
#include "stdlib.h"

#include "utils_hmac.h"
#include "utils_md5.h"
#include "utils_sha1.h"


/* ç±» bool åå®ä¹ */
#define SUCCEED ((uint8_t)0x01)
#define FAILED ((uint8_t)0x00)

/* ðè¿ä¸ªå®ä¹æ¾å°äº stm32f10x.h ä¸­ï¼529 è¡ï¼ï¼æ¾å¨å¶ä»ä½ç½®æ æ³ç¼è¯éè¿ï¼åå æªç¥ */
// typedef enum {FALSE = 0, TRUE = !FALSE, false = 0, true = !false} bool, boolean, BOOL;


/* bool ç±»ååæ°æ£æ¥å® */
#define IS_BOOL_TYPE_PARAM(PARAM) (((PARAM) == SUCCEED) || \
                                   ((PARAM) == FAILED) ||  \
                                   ((PARAM) == FALSE) ||   \
                                   ((PARAM) == TRUE) ||    \
                                   ((PARAM) == false) ||   \
                                   ((PARAM) == true))







#define BITBAND(addr, bitnum) ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bitnum << 2))
#define MEM_ADDR(addr) *((volatile unsigned long *)(addr))
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum))

// IOå£å°åæ å°
#define GPIOA_ODR_Addr (GPIOA_BASE + 12) // 0x4001080C
#define GPIOB_ODR_Addr (GPIOB_BASE + 12) // 0x40010C0C
#define GPIOC_ODR_Addr (GPIOC_BASE + 12) // 0x4001100C
#define GPIOD_ODR_Addr (GPIOD_BASE + 12) // 0x4001140C
#define GPIOE_ODR_Addr (GPIOE_BASE + 12) // 0x4001180C
#define GPIOF_ODR_Addr (GPIOF_BASE + 12) // 0x40011A0C
#define GPIOG_ODR_Addr (GPIOG_BASE + 12) // 0x40011E0C

#define GPIOA_IDR_Addr (GPIOA_BASE + 8) // 0x40010808
#define GPIOB_IDR_Addr (GPIOB_BASE + 8) // 0x40010C08
#define GPIOC_IDR_Addr (GPIOC_BASE + 8) // 0x40011008
#define GPIOD_IDR_Addr (GPIOD_BASE + 8) // 0x40011408
#define GPIOE_IDR_Addr (GPIOE_BASE + 8) // 0x40011808
#define GPIOF_IDR_Addr (GPIOF_BASE + 8) // 0x40011A08
#define GPIOG_IDR_Addr (GPIOG_BASE + 8) // 0x40011E08

// IOå£æä½,åªå¯¹åä¸çIOå£!

#define PAout(n) BIT_ADDR(GPIOA_ODR_Addr, n) //è¾åº
#define PAin(n) BIT_ADDR(GPIOA_IDR_Addr, n)  //è¾å¥

#define PBout(n) BIT_ADDR(GPIOB_ODR_Addr, n) //è¾åº
#define PBin(n) BIT_ADDR(GPIOB_IDR_Addr, n)  //è¾å¥

#define PCout(n) BIT_ADDR(GPIOC_ODR_Addr, n) //è¾åº
#define PCin(n) BIT_ADDR(GPIOC_IDR_Addr, n)  //è¾å¥

#define PDout(n) BIT_ADDR(GPIOD_ODR_Addr, n) //è¾åº
#define PDin(n) BIT_ADDR(GPIOD_IDR_Addr, n)  //è¾å¥

#define PEout(n) BIT_ADDR(GPIOE_ODR_Addr, n) //è¾åº
#define PEin(n) BIT_ADDR(GPIOE_IDR_Addr, n)  //è¾å¥

#define PFout(n) BIT_ADDR(GPIOF_ODR_Addr, n) //è¾åº
#define PFin(n) BIT_ADDR(GPIOF_IDR_Addr, n)  //è¾å¥

#define PGout(n) BIT_ADDR(GPIOG_ODR_Addr, n) //è¾åº
#define PGin(n) BIT_ADDR(GPIOG_IDR_Addr, n)  //è¾å¥


void NVIC_Config(void);
#endif
