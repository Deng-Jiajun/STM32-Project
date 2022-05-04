#ifndef __WIFI_H
#define __WIFI_H

#include "sys.h"

#define WIFI_RX_BUFFER_SIZE USART2_RX_BUFFER_SIZE // WiFi 模块 输入缓冲区大小
#define WiFi_Rx_Buffer USART2_Rx_Buffer           // WiFi 模块 输入缓冲区
#define WiFi_Rx_Length USART2_Rx_Length           // WiFi 模块 输入缓冲区当前缓冲规模

#define AP_SSID LGGRAM  // AP 的 SSID
#define AP_PWD 12345678 // AP 的 密码
/* 👆用上面两个参数凑出下面这个 AT 指令👇（上面两个宏定义暂时没有实际作用）*/
#define AT_COMMAND_CONNECT_AP "AT+CWJAP_DEF=\"LGGRAM\",\"12345678\""
/* 👆 用于连接 AP 的 AT 指令 */

#define TCP_SERVER_IP 192.168.0.195
#define TCP_SERVER_PORT 8080
/* 👆用上面两个参数凑出下面这个 AT 指令👇（上面两个宏定义暂时没有实际作用）*/
#define AT_COMMAND_ESTABLISH_TCP_CONNECTION "AT+CIPSTART=\"TCP\",\"192.168.0.195\",8080"
/* 👆 用于建立 TCP 通信的 AT 指令 */

void WiFi_Init(void);

#endif
