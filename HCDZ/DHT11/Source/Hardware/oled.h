#ifndef __OLED_H
#define __OLED_H

#include "sys.h"

//配置PA7的输入输出模式
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}
	 
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	 
#define READ_SDA   PBin(7)  //输入SDA 

u8 IICAdress(u8 addr);
u8 IICWrite(u8 dat);
void IIC_Stop(void);
void IIC_Start(void);
void OLED_Init(void);

void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_Set_Pos(unsigned char x, unsigned char y); 
void OLED_On(void); 
void OLED_Clear(void); 
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Command(unsigned char IIC_Command);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size);
void OLED_ShowCHinese(u8 x,u8 y,u8 no,u8 Size);
void OLED_ShowNum(u8 x,u8 y,int num,u8 Size);
#endif

