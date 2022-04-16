#include "sys.h"
void My_USART1(void);
int main(void)
{
		u8 temper;  	    
		u8 humi;
		u8 temp;
		delay_init();
		My_USART1();
		DHT11_Init();
		while(1)			
		{
			temp = DHT11_Read_Data(&temper,&humi);
			if(temp ==0)
			{
				printf("temperature is %d\r\n",temper);
				printf("humidity is %d\r\n",humi);
				delay_ms(1000);
			}		
		};
}
void My_USART1()
{  
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART1_InitStrue;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1, ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;//PA9
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;    
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Pin =GPIO_Pin_10;//PA10
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;    
    GPIO_Init(GPIOA, &GPIO_InitStruct);    
    
    USART1_InitStrue.USART_BaudRate = 9600;
    USART1_InitStrue.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART1_InitStrue.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
    USART1_InitStrue.USART_Parity = USART_Parity_No;
    USART1_InitStrue.USART_StopBits=USART_StopBits_1;
    USART1_InitStrue.USART_WordLength = USART_WordLength_8b;    
    USART_Init( USART1, &USART1_InitStrue);
    USART_Cmd(USART1,ENABLE);    
}

int fputc(int ch, FILE *f)
{      
        USART_SendData(USART1, (uint8_t) ch);            
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);            
        return (ch);
}
