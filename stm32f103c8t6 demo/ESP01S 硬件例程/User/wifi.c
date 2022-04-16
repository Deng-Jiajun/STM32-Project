#include "sys.h"

void WIFI_Config(int time)
{
	memset(WiFi_RX_BUF,0,1024);
	WiFi_RxCounter = 0;
	while(time--)
	{
		delay_ms(100);
		if(strstr(WiFi_RX_BUF,"ready"))
			break;
		u1_printf ("%d ",time); 
	}
	u1_printf ("\r\n");
	if(time>0)
       u1_printf ("复位成功!\r\n"); 
    else
       u1_printf ("复位失败!\r\n");

}

void WIFI_Config2(int time)
{
	memset(WiFi_RX_BUF,0,1024);
	WiFi_RxCounter = 0;
	u2_printf("AT+CWMODE=1\r\n"); 
	while(time--)
	{
		delay_ms(100);
		if(strstr(WiFi_RX_BUF,"OK"))
			break;
		u1_printf ("%d ",time); 
	}
	u1_printf ("\r\n");
	if(time>0)
       u1_printf ("配置WIFI模式成功!\r\n"); 
    else
       u1_printf ("配置WIFI模式失败!\r\n");

}
