#include "sys.h"
#include "oledfont.h"
/*-----------------------------------------------
函数名：OLED相关引脚初始化                      
参  数：无                            
返回值：无 
------------------------------------------------*/
void OLED_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
 
	IIC_SCL=1;
	IIC_SDA=1;
	
	delay_ms(800);//初始化前延时，重要！
	Write_IIC_Command(0xAE);//关闭显示
	Write_IIC_Command(0x00);//设置低列地址
	Write_IIC_Command(0x10);//设置高列地址
	
	Write_IIC_Command(0x40);//--设置显示开始行 [5:0],行数。设置起始行地址,集映射RAM显示起始行(0x00~0x3F)  
	
	Write_IIC_Command(0xB0);//--set page address
	
	Write_IIC_Command(0x81); // 对比度设置
	Write_IIC_Command(0xFF);//--128   
	
	Write_IIC_Command(0xA1);//段重定义设置,bit0:0,0->0;1,0->127;
	
	Write_IIC_Command(0xA6);////设置显示方式;bit0:1,反相显示;0,正常显示
	
	Write_IIC_Command(0xA8);//--设置驱动路数
	Write_IIC_Command(0x3F);//--1/32 duty默认0X3F(1/64)
	
	Write_IIC_Command(0xC8);//设置COM扫描方向;bit3:0,普通模式;1,重定义模式 COM[N-1]->COM0;N:驱动路数   0xc0上下反置 0xc8正常
	
	Write_IIC_Command(0xD3);//设置显示偏移位移映射RAM计数器(0x00~0x3F)
	Write_IIC_Command(0x00);//默认为0
	
	Write_IIC_Command(0x20);//设置内存寻址模式
	Write_IIC_Command(0x02);
	
	Write_IIC_Command(0xD5);//设置时钟分频因子,震荡频率
	Write_IIC_Command(0x80);//[3:0],分频因子;[7:4],震荡频率	
	
	Write_IIC_Command(0xD9);//设置预充电周期
	Write_IIC_Command(0xF1);//[3:0],PHASE 1;[7:4],PHASE 2;	
	
	Write_IIC_Command(0xDA);//设置COM硬件引脚配置
	Write_IIC_Command(0x12);//[5:4]配置	
	
	Write_IIC_Command(0xDB);//设置VCOMH 电压倍率
	Write_IIC_Command(0x30);//[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;	
	
	Write_IIC_Command(0x8D);//电荷泵设置
	Write_IIC_Command(0x14);//bit2开启或者关闭	
	
	Write_IIC_Command(0xAF);//开显示
}
/*-----------------------------------------------
函数名：产生IIC起始信号                      
参  数：无                            
返回值：无 
------------------------------------------------*/
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}

/*-----------------------------------------------
函数名：产生IIC停止信号                      
参  数：无                            
返回值：无 
------------------------------------------------*/
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	delay_us(4);							   	
}
/*-----------------------------------------------
函数名：写入1字节                      
参  数：写入的字节                            
返回值：ack为0，表示写入成功；ack为1，表示写入失败
------------------------------------------------*/
u8 IICWrite(u8 dat)
{
	u8 ack;
	u8 mask;
	SDA_OUT();
	for(mask=0x80;mask!=0;mask>>=1)
	{
		if((mask&dat) == 0)
		{
			IIC_SDA=0;
		}
		else
			IIC_SDA=1;
		delay_us(4);
		IIC_SCL=1;
		delay_us(4);
		IIC_SCL=0;
	}
	SDA_IN(); 
	IIC_SDA=1;	
	delay_us(4);
	IIC_SCL=1;
	ack=READ_SDA;
	delay_us(4);
	IIC_SCL=0;
	return ack;	
}
/*-----------------------------------------------
函数名：验证从机是否存在                      
参  数：从机的地址                            
返回值：ack为0，表示从机存在；ack为1，表示从机不存在
------------------------------------------------*/
u8 IICAdress(u8 addr)
{
	u8 ack;
	IIC_Start();
	ack=IICWrite(addr<<1);
	IIC_Stop();
	return ack;

}


/*-----------------------------------------------
函数名：发送命令函数                     
参  数：发送的指令                            
返回值：无返回
------------------------------------------------*/
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   IICWrite(0x78);   //也可写成 IICWrite(0x3C<<1);        
	
   IICWrite(0x00);			
	
   IICWrite(IIC_Command); 
		
   IIC_Stop();
}

/*-----------------------------------------------
函数名：发送数据函数                     
参  数：发送的数据                            
返回值：无返回
------------------------------------------------*/
void Write_IIC_Data(unsigned char IIC_Data)
{
    IIC_Start();
    IICWrite(0x78);			
		
    IICWrite(0x40);			
		
    IICWrite(IIC_Data);
		
    IIC_Stop();
}

		   			 
/*-----------------------------------------------
函数名：清屏                     
参  数：无参数                           
返回值：无返回
------------------------------------------------*/
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		Write_IIC_Command(0xb0+i);    //设置页地址（0~7）
		Write_IIC_Command(0x00);      //设置显示位置—列低地址
		Write_IIC_Command(0x10);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)
		   Write_IIC_Data(0); 
	} 
}
		   			 
/*-----------------------------------------------
函数名：屏全亮                     
参  数：无参数                           
返回值：无返回
------------------------------------------------*/
void OLED_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		Write_IIC_Command(0xb0+i);    //设置页地址（0~7）
		Write_IIC_Command(0x00);      //设置显示位置—列低地址
		Write_IIC_Command(0x10);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)
			Write_IIC_Data(1); 
	} 
}


		   			 
/*-----------------------------------------------
函数名：设置坐标                     
参  数：x表示横坐标，跟列相关；y表示纵坐标，跟页相关                          
返回值：无返回
------------------------------------------------*/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 	
	Write_IIC_Command(0xb0+y);
	Write_IIC_Command(((x&0xf0)>>4)|0x10);
	Write_IIC_Command((x&0x0f)); 
}

/*-----------------------------------------------
函数名：显示字符                     
参  数：x表示横坐标，y表示纵坐标，Char_Size表示要显示字体大小                
返回值：无返回
------------------------------------------------*/
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
		unsigned char c=0,i=0;	
		c=chr-' ';//得到偏移后的值			
		if(x>128-1)
		{
			x=0;y=y+2;
		}
		if(Char_Size ==16)
		{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
				Write_IIC_Data(F8X16[c*16+i]);//上半部分
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
				Write_IIC_Data(F8X16[c*16+i+8]);//下半部分
		}
		else 
		{	
			OLED_Set_Pos(x,y);
			for(i=0;i<6;i++)
			Write_IIC_Data(F6x8[c][i]);
				
		}
}

void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	while(*chr != '\0')
	{
		OLED_ShowChar(x,y,*chr++,Char_Size);
		x +=8;
		if(x>120)
		{
			x = 0;
			y+=2;
		}
	}

}

void OLED_ShowCHinese(u8 x,u8 y,u8 no,u8 Size)
{
	unsigned char i=0;
	if(Size ==16)
	{
		OLED_Set_Pos(x,y);	
		for(i=0;i<16;i++)
			Write_IIC_Data(F16X16[no*32+i]);//上半部分
		OLED_Set_Pos(x,y+1);
		for(i=0;i<16;i++)
			Write_IIC_Data(F16X16[no*32+i+16]);//下半部分
		}
}

void OLED_ShowNum(u8 x,u8 y,int num,u8 Size)
{
	u8 i=0;
	u8 t=0;
	u8 len=0;	
	u8 buf[3];
	
	while(num>0)
	{
		buf[i++] = num%10;
		num /= 10;
	}
	len = i;
	for(t=0;t<i;t++)
	{
	OLED_ShowChar(x+(Size/2)*t,y,buf[--len]+'0',Size);
	}
}
