#ifndef __DHT11_H
#define __DHT11_H

#include "sys.h"

/* DHT11 �������߽��� PA5 */

/* ������λ������������ DHT11 �Ķ�д���� */
#define DHT11_WRITE PAout(5)
#define DHT11_READ PAin(5)
#define DHT11_PIN GPIO_Pin_5
#define DHT11_PORT GPIOA

/* ���� DHT11 ��Ӧ���ţ�PA5��������/���ģʽ */
#define DHT11_IN()                                               \
    {                                                            \
        /* ���� GPIOA_CLR �� CNF5 �� MODE5��λ 23:20�� */ \
        GPIOA->CRL &= 0XFF0FFFFF;                                \
        /* ����Ϊ����/��������ģʽ��10 00�� */      \
        GPIOA->CRL |= 8 << 5 * 4;                                \
    }
#define DHT11_OUT()                                                       \
    {                                                                     \
        /* ���� GPIOA_CLR �� CNF5 �� MODE5��λ 23:20�� */          \
        GPIOA->CRL &= 0XFF0FFFFF;                                         \
        /* ����Ϊͨ���������������ٶ� 50MHz��00 11�� */ \
        GPIOA->CRL |= 3 << 5 * 4;                                         \
    }

uint8_t DHT11_RST(void);
uint8_t DHT11_Read_Bit(void);
uint8_t DHT11_Read_Byte(void);
uint8_t DHT11_Read_Data(uint8_t *temperature, uint8_t *humidity);
void DHT11_Init(void);

#endif
