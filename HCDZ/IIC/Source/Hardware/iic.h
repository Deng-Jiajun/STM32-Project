#ifndef __IIC_H
#define __IIC_H
#include "sys.h"

//����PA7���������ģʽ
#define SDA_IN()                         \
    {                                    \
        GPIOB->CRL &= 0X0FFFFFFF;        \
        GPIOB->CRL |= (uint32_t)8 << 28; \
    }
#define SDA_OUT()                        \
    {                                    \
        GPIOB->CRL &= 0X0FFFFFFF;        \
        GPIOB->CRL |= (uint32_t)3 << 28; \
    }

#define IIC_SCL PBout(6) // д SCL
#define IIC_SDA PBout(7) // д SDA
#define READ_SDA PBin(7) // �� SDA

void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
uint8_t IICWrite(uint8_t data);
uint8_t IICAdress(uint8_t address);

#endif
