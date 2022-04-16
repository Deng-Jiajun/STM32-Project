#include "sys.h"

/*-----------------------------------------------
��������DHT11��λ               
��  ������                            
����ֵ�� 0����ʾ��Ӧ�ɹ�����0����ʾ��Ӧ���ɹ���
------------------------------------------------*/	
u8 DHT11_RST(void)	   
{                 
	u8 cnt=0;
	DHT11_OUT(); 	
    DHT11_WRITE=0; 	
    delay_ms(20);    	
    DHT11_WRITE=1; 	 
	delay_us(30);     	
	DHT11_IN();	 
    while (!DHT11_READ&&cnt<100)
	{
		cnt++;
		delay_us(1);
	};	 
	if(cnt>=100)
		return 1;
	else 
		cnt=0;
    while (DHT11_READ&&cnt<100)
	{
		cnt++;
		delay_us(1);
	};
	if(cnt>=100)
		return 1;    
	return 0;
}


/*-----------------------------------------------
��������DHT11��ȡһ��λ               
��  ������                            
����ֵ�� 0����ʾ��ȡ�͵�ƽ��1����ʾ��ȡ�ߵ�ƽ��
------------------------------------------------*/	
u8 DHT11_Read_Bit(void) 			 
{
	while(DHT11_READ);//��⵽�͵�ƽ
	while(!DHT11_READ);////��⵽�ߵ�ƽ	
	delay_us(35);		
	if(DHT11_READ)
		return 1;
	else 
		return 0;		   
}

/*-----------------------------------------------
��������DHT11��ȡһ�ֽ�               
��  ������                            
����ֵ�� ����һ�ֽ�ֵ��
------------------------------------------------*/	
u8 DHT11_Read_Byte(void)    
{        
	u8 mask,dat;
	dat=0;
	for (mask=0x80;mask!=0;mask>>=1) 
	{
		if(DHT11_Read_Bit())
			dat |=mask;
		else
			dat &=~mask;	 	
	}						    
	return dat;
}

/*-----------------------------------------------
��������DHT11��ȡ��ʪ����������               
��  ������                            
����ֵ�� 0����ʾ�ɹ���ȡ����0����ʾ��ȡ���ɹ���
------------------------------------------------*/	
u8 DHT11_Read_Data(u8 *temperature,u8 *humidity)
{
	u8 i;
	u8 buf[5];
	if(DHT11_RST() == 0)
	{
		for(i = 0;i<5;i++)
		{
			buf[i] = DHT11_Read_Byte();
		
		}
		if ((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			 *humidity = buf[0];
			 *temperature = buf[2];
			return 0;		
		}
		else
			return 1;		
	}
	else
		return 1;

}

/*-----------------------------------------------
��������PA5���ų�ʼ��               
��  ������                            
����ֵ�� 0����ʾ��Ӧ�ɹ���1����ʾ��Ӧ���ɹ���
------------------------------------------------*/	
void DHT11_Init(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);				 
 							 			    	
} 







