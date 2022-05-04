#include "sys.h"

bool WiFi_Send_AT_Instruction(char *command, char *positive_response, uint8_t wait_time);
/* 不对外暴露的函数👆 */

/**
 * @brief WiFi 模块初始化
 *
 */
void WiFi_Init(void)
{
    /* WiFi 模块复位 */
    printf("reseting WiFi module...\r\n");
    if (WiFi_Send_AT_Instruction("AT+RST", "ready", 10))
    {
        printf("WiFi module rested successfully!\r\n\r\n");
    }
    else
    {
        printf("WiFi module rested failed!\r\n\r\n");
    }

    /* 配置 WiFi 模式 */
    printf("configuring WiFi module...\r\n");
    if (WiFi_Send_AT_Instruction("AT+CWMODE=1", "OK", 5))
    {
        printf("WiFi module configured successfully!\r\n\r\n");
    }
    else
    {
        printf("WiFi module configured failed!\r\n\r\n");
    }

    /* 重启 WiFi 模块 */
    printf("restarting WiFi module...\r\n");
    if (WiFi_Send_AT_Instruction("AT+RST", "ready", 10))
    {
        printf("WiFi module restarted successfully!\r\n\r\n");
    }
    else
    {
        printf("WiFi module restarted failed!\r\n\r\n");
    }

    /* 取消自动连接 */
    printf("disabling auto-connect...\r\n");
    if (WiFi_Send_AT_Instruction("AT+CWAUTOCONN=0", "OK", 5))
    {
        printf("auto-connect disabled successfully!\r\n\r\n");
    }
    else
    {
        printf("auto-connect disabled failed!\r\n\r\n");
    }

    /* 连接到 AP */
    printf("connecting to AP...\r\n");

    if (WiFi_Send_AT_Instruction(AT_COMMAND_CONNECT_AP, "OK", 10))
    {
        printf("WiFi module connected to AP successfully!\r\n\r\n");
    }
    else
    {
        printf("WiFi module connected to AP failed!\r\n\r\n");
    }

    /* 设置为单连接模式 */
    printf("setting WiFi module to single-connection mode...\r\n");
    if (WiFi_Send_AT_Instruction("AT+CIPMUX=0", "OK", 5))
    {
        printf("WiFi module set to single-connection mode successfully!\r\n\r\n");
    }
    else
    {
        printf("WiFi module set to single-connection mode failed!\r\n\r\n");
    }

    /* 设置为透传模式 */
    printf("enabling WiFi module to pass-through mode...\r\n");
    if (WiFi_Send_AT_Instruction("AT+CIPMODE=1", "OK", 5))
    {
        printf("WiFi module enabled to pass-through mode successfully!\r\n\r\n");
    }
    else
    {
        printf("WiFi module enabled to pass-through mode failed!\r\n\r\n");
    }

    /* 建立 TCP 通信 */
    printf("establishing TCP connection...\r\n");
    if (WiFi_Send_AT_Instruction(AT_COMMAND_ESTABLISH_TCP_CONNECTION, "OK", 10))
    {
        printf("TCP connection established successfully!\r\n\r\n");
    }
    else
    {
        printf("TCP connection established failed!\r\n\r\n");
    }

    /* 进入透传模式（准备开始发送数据） */
    printf("entering pass-through mode...\r\n");
    if (WiFi_Send_AT_Instruction("AT+CIPSEND", "\r\nOK\r\n\r\n>", 5))
    {
        printf("pass-through mode enabled successfully!\r\n\r\n");
    }
    else
    {
        printf("pass-through mode enabled failed!\r\n\r\n");
    }
}

/**
 * @brief 向 WiFi 模块（通过串口）发送 AT 指令
 *
 * @param command 要发送的 AT 指令
 * @param positive_response 预期响应包含的字符串
 * @param wait_time 等待时间（单位：s）
 *
 * @retval true 得到预期响应
 * @retval false 未得到预期响应
 */
bool WiFi_Send_AT_Instruction(char *command, char *positive_response, uint8_t wait_time)
{
    /* 等待时间（wait_time） 以秒为单位，每 100ms 检查一次缓冲区，所以 ×10 */
    wait_time *= 10;

    /* 输入缓冲区清零 */
    memset(WiFi_Rx_Buffer, 0, WIFI_RX_BUFFER_SIZE);
    WiFi_Rx_Length = 0;

    /* 发送 AT 指令 */
    USART2_Printf("%s\r\n", command);

    /* wait_time == 0 时跳出循环 */
    while (--wait_time)
    {
        // printf("Waiting respond...%d\r\n", wait_time);
        // printf("%d ", wait_time);
        delay_ms(100);
        if (strstr(WiFi_Rx_Buffer, positive_response))
        {
            break;
        }
    }

    /* 在倒计时前内收到预期响应，则返回 true，否则返回 false */
    if (wait_time)
    {
        return true;
    }
    else
    {
        return false;
    }
}
