#include "sys.h"

int main(void)
{
	uint8_t ack;
	delay_init();
	USART1_Config();
	IIC_Init();
	ack = IICAdress(0x3C);
	if (ack == 0)
	{
		printf("IICAdress 0x3C ACK\r\n");
	}
	else
	{
		printf("IICAdress 0x3C NACK\r\n");
	}

	ack = IICAdress(0x3D);
	if (ack == 0)
	{
		printf("IICAdress 0x3D ACK\r\n");
	}
	else
	{
		printf("IICAdress 0x3D NACK\r\n");
	}

	ack = IICAdress(0x3E);
	if (ack == 0)
	{
		printf("IICAdress 0x3E ACK\r\n");
	}
	else
	{
		printf("IICAdress 0x3E NACK\r\n");
	}

	while (1)
	{
	}
}
