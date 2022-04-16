/****************重要说明**************
使用此函数需要添加

#include "stdio.h"      
#include "stdarg.h"		
#include "string.h"

这三个头文件
**********************************/

#include "sys.h"
u16 USART2_RxCounter = 0;      
char USART2_RxBuff[1024]; 

void My_USART2(void)
{
	GPIO_InitTypeDef  GPIO_InitStrue;
	USART_InitTypeDef USART2_InitStrue;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStrue.GPIO_Pin=USART2_GPIO_PIN_TX;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;		
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStrue.GPIO_Pin=USART2_GPIO_PIN_RX;	
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	USART2_InitStrue.USART_BaudRate=115200;
	USART2_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART2_InitStrue.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART2_InitStrue.USART_Parity=USART_Parity_No;
	USART2_InitStrue.USART_StopBits=USART_StopBits_1;
	USART2_InitStrue.USART_WordLength=USART_WordLength_8b;
	
	USART_Init(USART2,&USART2_InitStrue);	
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART2,ENABLE);	

}


__align(8) char USART2_TxBuff[256];  

void u2_printf(char* fmt,...) 
{  
	unsigned int i =0,length=0;
	
	va_list ap;
	va_start(ap,fmt);
	vsprintf(USART2_TxBuff,fmt,ap);
	va_end(ap);
	
	length=strlen((const char*)USART2_TxBuff);
	while(i<length)
	{
		USART_SendByte(USART2,USART2_TxBuff[i]);		
		i++;		
	}
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
	
}

void USART2_IRQHandler(void)   
{ 
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {  
		                              
		if(USART2->DR)
		{                                 	
			USART2_RxBuff[USART2_RxCounter]=USART_ReceiveData(USART2); 	
			USART2_RxCounter++;                        
		}		
		
	}
};
