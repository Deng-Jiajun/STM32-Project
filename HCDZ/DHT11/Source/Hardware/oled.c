#include "sys.h"
#include "oledfont.h"
/*-----------------------------------------------
��������OLED������ų�ʼ��                      
��  ������                            
����ֵ���� 
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
	
	delay_ms(800);//��ʼ��ǰ��ʱ����Ҫ��
	Write_IIC_Command(0xAE);//�ر���ʾ
	Write_IIC_Command(0x00);//���õ��е�ַ
	Write_IIC_Command(0x10);//���ø��е�ַ
	
	Write_IIC_Command(0x40);//--������ʾ��ʼ�� [5:0],������������ʼ�е�ַ,��ӳ��RAM��ʾ��ʼ��(0x00~0x3F)  
	
	Write_IIC_Command(0xB0);//--set page address
	
	Write_IIC_Command(0x81); // �Աȶ�����
	Write_IIC_Command(0xFF);//--128   
	
	Write_IIC_Command(0xA1);//���ض�������,bit0:0,0->0;1,0->127;
	
	Write_IIC_Command(0xA6);////������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ
	
	Write_IIC_Command(0xA8);//--��������·��
	Write_IIC_Command(0x3F);//--1/32 dutyĬ��0X3F(1/64)
	
	Write_IIC_Command(0xC8);//����COMɨ�跽��;bit3:0,��ͨģʽ;1,�ض���ģʽ COM[N-1]->COM0;N:����·��   0xc0���·��� 0xc8����
	
	Write_IIC_Command(0xD3);//������ʾƫ��λ��ӳ��RAM������(0x00~0x3F)
	Write_IIC_Command(0x00);//Ĭ��Ϊ0
	
	Write_IIC_Command(0x20);//�����ڴ�Ѱַģʽ
	Write_IIC_Command(0x02);
	
	Write_IIC_Command(0xD5);//����ʱ�ӷ�Ƶ����,��Ƶ��
	Write_IIC_Command(0x80);//[3:0],��Ƶ����;[7:4],��Ƶ��	
	
	Write_IIC_Command(0xD9);//����Ԥ�������
	Write_IIC_Command(0xF1);//[3:0],PHASE 1;[7:4],PHASE 2;	
	
	Write_IIC_Command(0xDA);//����COMӲ����������
	Write_IIC_Command(0x12);//[5:4]����	
	
	Write_IIC_Command(0xDB);//����VCOMH ��ѹ����
	Write_IIC_Command(0x30);//[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;	
	
	Write_IIC_Command(0x8D);//��ɱ�����
	Write_IIC_Command(0x14);//bit2�������߹ر�	
	
	Write_IIC_Command(0xAF);//����ʾ
}
/*-----------------------------------------------
������������IIC��ʼ�ź�                      
��  ������                            
����ֵ���� 
------------------------------------------------*/
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}

/*-----------------------------------------------
������������IICֹͣ�ź�                      
��  ������                            
����ֵ���� 
------------------------------------------------*/
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	delay_us(4);							   	
}
/*-----------------------------------------------
��������д��1�ֽ�                      
��  ����д����ֽ�                            
����ֵ��ackΪ0����ʾд��ɹ���ackΪ1����ʾд��ʧ��
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
����������֤�ӻ��Ƿ����                      
��  �����ӻ��ĵ�ַ                            
����ֵ��ackΪ0����ʾ�ӻ����ڣ�ackΪ1����ʾ�ӻ�������
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
�����������������                     
��  �������͵�ָ��                            
����ֵ���޷���
------------------------------------------------*/
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   IICWrite(0x78);   //Ҳ��д�� IICWrite(0x3C<<1);        
	
   IICWrite(0x00);			
	
   IICWrite(IIC_Command); 
		
   IIC_Stop();
}

/*-----------------------------------------------
���������������ݺ���                     
��  �������͵�����                            
����ֵ���޷���
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
������������                     
��  �����޲���                           
����ֵ���޷���
------------------------------------------------*/
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		Write_IIC_Command(0xb0+i);    //����ҳ��ַ��0~7��
		Write_IIC_Command(0x00);      //������ʾλ�á��е͵�ַ
		Write_IIC_Command(0x10);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)
		   Write_IIC_Data(0); 
	} 
}
		   			 
/*-----------------------------------------------
����������ȫ��                     
��  �����޲���                           
����ֵ���޷���
------------------------------------------------*/
void OLED_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		Write_IIC_Command(0xb0+i);    //����ҳ��ַ��0~7��
		Write_IIC_Command(0x00);      //������ʾλ�á��е͵�ַ
		Write_IIC_Command(0x10);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)
			Write_IIC_Data(1); 
	} 
}


		   			 
/*-----------------------------------------------
����������������                     
��  ����x��ʾ�����꣬������أ�y��ʾ�����꣬��ҳ���                          
����ֵ���޷���
------------------------------------------------*/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 	
	Write_IIC_Command(0xb0+y);
	Write_IIC_Command(((x&0xf0)>>4)|0x10);
	Write_IIC_Command((x&0x0f)); 
}

/*-----------------------------------------------
����������ʾ�ַ�                     
��  ����x��ʾ�����꣬y��ʾ�����꣬Char_Size��ʾҪ��ʾ�����С                
����ֵ���޷���
------------------------------------------------*/
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
		unsigned char c=0,i=0;	
		c=chr-' ';//�õ�ƫ�ƺ��ֵ			
		if(x>128-1)
		{
			x=0;y=y+2;
		}
		if(Char_Size ==16)
		{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
				Write_IIC_Data(F8X16[c*16+i]);//�ϰ벿��
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
				Write_IIC_Data(F8X16[c*16+i+8]);//�°벿��
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
			Write_IIC_Data(F16X16[no*32+i]);//�ϰ벿��
		OLED_Set_Pos(x,y+1);
		for(i=0;i<16;i++)
			Write_IIC_Data(F16X16[no*32+i+16]);//�°벿��
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
