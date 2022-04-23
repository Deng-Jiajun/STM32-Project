#include "sys.h"

/*
 ! 为了发送中文，这个文件的编码格式是 GB2312
 ! In order to send Chinese, the encoding format of this file is GB2312
 */

/**
 * @brief LED 测试函数
 *
 * @note 预期效果：
 *       LED1 打开，0.5秒后 LED2 打开，0.5秒后 LED1 关闭，0.5秒后 LED2 关闭，
 *       0.5秒后 LED1 和 LED2 同时打开，0.5秒后 LED1 和 LED2 同时关闭
 */
void TEST_LED(void)
{
    /* 只有两个灯，搞不了流水灯 */

    /* delay 初始化 */
    delay_init();

    /* LED 初始化 */
    LED_Init();

    /* 开启 LED1 */
    LED_On(1);
    delay_ms(500);

    /* 开启 LED2 */
    LED_On(2);
    delay_ms(500);

    /* 关闭 LED1 */
    LED_Off(1);
    delay_ms(500);

    /* 关闭 LED2 */
    LED_Off(2);
    delay_ms(500);

    /* 同时开启 LED1 和 LED2 */
    LED_Toggle(1);
    LED_Toggle(2);

    delay_ms(500);

    /* 同时关闭 LED1 和 LED2 */
    LED_Toggle(1);
    LED_Toggle(2);
}

/* 按键按下标志位 */
extern uint8_t flag;
/**
 * @brief 按键测试函数
 * @note 预期效果：按下 KEY1，放开后 LED1 亮 2 秒后关闭
 */
void TEST_KEY(void)
{
    /*  delay 初始化 */
    delay_init();

    /* 初始化 LED */
    LED_Init();

    /* 初始化 delay */
    delay_init();

    /* 初始化按键 */
    KEY_GPIO_Config();

    while (1)
    {
        /* 按键扫描 */
        KEY_Scan();
        /* 如果按键按下 */
        if (flag == 1)
        {
            /* 点亮 LED1 2秒 */
            LED_On(1);
            delay_ms(500);
            delay_ms(500);
            delay_ms(500);
            delay_ms(500);

            /* 然后关闭 LED1 */
            LED_Off(1);

            flag = 0;
        }
    }
}

/**
 * @brief USART 测试函数
 * @note 预期效果：串口接收到数据后（通过串口）原样发出
 */
void TEST_USART1(void)
{
    char temp;
    USART1_Config();

    while (1)
    {
        temp = USART_ReceieByte(USART1);
        USART_SendByte(USART1, temp);
    }
}

/**
 * @brief printf 重定向测试函数（重定向到 USART1）
 * @note 预期效果：每秒发送两行字符串
 */
void TEST_Redirect_Printf(void)
{
    int count = 0;

    /*  delay 初始化 */
    delay_init();

    /* USART1 配置（初始化） */
    USART1_Config();
    while (1)
    {
        printf("你好，世界！Hello World!\r\n");
        printf("count = %d\r\n", count++);
        delay_ms(1000);
    }
}

/**
 * @brief OLED 测试函数
 * @note 预期效果：显示三行文字
 */
void TEST_OLED(void)
{
    int count = 0;

    /*  delay 初始化 */
    delay_init();

    /* OLED 初始化 */
    OLED_Init();

    /* OLED 清屏 */
    OLED_Clear();
    OLED_ShowString(1, 1, "Hello World!", 16);
    OLED_ShowString(1, 3, "count: ", 16);

    while (count != 10)
    {
        OLED_ShowNum(50, 3, count++, 16);
        delay_ms(1000);
        OLED_ShowNum(50, 5, count, 16);
    }
    OLED_Clear();
}

/**
 * @brief DHT11 测试函数
 *
 */
void TEST_DHT11(void)
{
    uint8_t temper;
    uint8_t humi;

    /*  delay 初始化 */
    delay_init();

    /* USART1 配置（初始化） */
    USART1_Config();

    /* DHT11 初始化 */
    DHT11_Init();

    /* OLED 初始化 */
    OLED_Init();
    /* OLED 清屏 */
    OLED_Clear();

    OLED_ShowString(1, 1, "temperature: ", 16);
    OLED_ShowString(1, 3, "humidity: ", 16);

    while (1)
    {
        if (DHT11_Read_Data(&temper, &humi))
        {
            printf("temperature is %d\r\n", temper);
            printf("humidity is %d\r\n", humi);
            OLED_ShowNum(12 * 8, 1, temper, 16);
            OLED_ShowNum(9 * 8, 3, humi, 16);
        }
        else
        {
            printf("temp的值不为0！\r\n");
        }
        
        /* 读取间隔不小于 1 秒 */
        delay_ms(1500);
    };
}
