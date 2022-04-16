#ifndef __WIFI_H__
#define __WIFI_H__

#include "sys.h"
#define WiFi_RxCounter    USART2_RxCounter    
#define WiFi_RX_BUF       USART2_RxBuff       

void WIFI_Config(int time);
void WIFI_Config2(int time);
#endif

