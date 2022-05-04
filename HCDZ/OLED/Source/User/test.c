#include "sys.h"

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
    USART1_Init();

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
    USART1_Init();
    while (1)
    {
        printf("Hello World!\r\n");
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
    OLED_ShowStr(0, 0, "Hello World!");
    OLED_ShowStr(1, 0, "count: ");

    /* 中文显示测试 */
    OLED_ShowChineseChar(2, 0, 0); /* "中", 0 */
    OLED_ShowChineseChar(2, 1, 1); /* "文", 1 */
    OLED_ShowChineseChar(2, 2, 2); /* "显", 2 */
    OLED_ShowChineseChar(2, 3, 3); /* "示", 3 */
    OLED_ShowChineseChar(2, 4, 4); /* "测", 4 */
    OLED_ShowChineseChar(2, 5, 5); /* "试", 5 */
    OLED_ShowChineseChar(2, 6, 6); /* "！", 6 */

    OLED_ShowStr(3, 0, "abcdefgh12345678");

    while (count != 10)
    {
        OLED_ShowNum(1, 7, count++);
        delay_ms(500);
    }
    /* OLED 清屏 */
    OLED_Clear();

    /* 数字显示测试 */
    OLED_ShowNum(0, 0, 0);
    OLED_ShowNum(0, 1, 123456789);
    OLED_ShowNum(1, 0, -2147483647);
    OLED_ShowNum(2, 0, INT32_MIN);
    OLED_ShowNum(3, 0, INT32_MAX);

    while (count != 30)
    {
        OLED_ShowNum(1, 14, count++);
        delay_ms(500);
    }
    /* OLED 清屏 */
    OLED_Clear();
}

/**
 * @brief DHT11 测试函数
 * @note 预期结果：串口 和 OLED 显示温湿度
 */
void TEST_DHT11(void)
{
    uint8_t temper;
    uint8_t humi;

    /*  delay 初始化 */
    delay_init();

    /* USART1 配置（初始化） */
    USART1_Init();

    /* DHT11 初始化 */
    DHT11_Init();

    /* OLED 初始化 */
    OLED_Init();
    /* OLED 清屏 */
    OLED_Clear();

    OLED_ShowStr(0, 0, "temperature: ");
    OLED_ShowStr(1, 0, "humidity: ");

    while (1)
    {
        if (DHT11_Read_Data(&temper, &humi))
        {
            printf("temperature is %d\r\n", temper);
            printf("humidity is %d\r\n", humi);
            OLED_ShowNum(0, 13, temper);
            OLED_ShowNum(1, 10, humi);
        }
        else
        {
            printf("temp != 0\r\n");
        }

        /* 读取间隔不小于 1 秒 */
        delay_ms(1500);
    }
}

/**
 * @brief 参数检查测试函数
 * @note 预期结果：串口输出错误提示信息
 */
void TEST_ASSERT_FAIL(void)
{
    /*  delay 初始化 */
    delay_init();

    /* USART1 配置（初始化） */
    USART1_Init();

    /* printf 输出测试 */
    printf("----- test assert fail -----\r\n");

    /* 打开一个非法地址的外设的时钟 */
    RCC_APB2PeriphClockCmd(0x10200000, ENABLE);

    /* 报错信息👇 */
    // Wrong parameter svalue: file ..\Source\Libraries\STM32F10x_StdPeriph_Driver\src\stm32f10x_rcc.c on line 1098
    /* 没有预想中的提示在 test.c 的某一行，但是可以知道是外设地址出错 */

    /* 这个可以指定在具体的位置👇 */
    // ! 想看到这句的报错需要注释上面那句，因为 assert_failed 会执行死循环
    assert_param(IS_BOOL_TYPE_PARAM(12345));
    /* 说明 assert_failed 只能指定到具体是哪句参数判断的语句引发的报错 */
}

/**
 * @brief IIC 测试函数
 * 由于 IIC 本身内容不多，所以只测试能不能找到 IIC 总线上的 OLED(从机地址 0x3C)
 * @note 预期结果：串口输出 0x3C ACK，其他两个为 NACK
 */
void TEST_IIC(void)
{
    delay_init();
    USART1_Init();
    IIC_Init();

    if (IIC_Check_Address(0x3C) == IIC_ACK)
        printf("IICAddress 0x3C ACK\r\n");
    else
        printf("IICAddress 0x3C NACK\r\n");

    if (IIC_Check_Address(0x3D) == IIC_ACK)
        printf("IICAddress 0x3D ACK\r\n");
    else
        printf("IICAddress 0x3D NACK\r\n");

    if (IIC_Check_Address(0x3E) == IIC_ACK)
        printf("IICAddress 0x3E ACK\r\n");
    else
        printf("IICAddress 0x3E NACK\r\n");

    while (1)
    {
    }
}
