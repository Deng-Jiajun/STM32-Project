#include "sys.h"

int main(void)
{
		delay_init();
		My_USART1();
		My_USART2(); 
	    NVIC_Config();
	    WIFI_Config(100);
		WIFI_Config2(100);
		while(1)			
		{
						
		
		};
}
