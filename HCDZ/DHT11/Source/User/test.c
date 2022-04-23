#include "sys.h"

/*
 ! Ϊ�˷������ģ�����ļ��ı����ʽ�� GB2312
 ! In order to send Chinese, the encoding format of this file is GB2312
 */

/**
 * @brief LED ���Ժ���
 *
 * @note Ԥ��Ч����
 *       LED1 �򿪣�0.5��� LED2 �򿪣�0.5��� LED1 �رգ�0.5��� LED2 �رգ�
 *       0.5��� LED1 �� LED2 ͬʱ�򿪣�0.5��� LED1 �� LED2 ͬʱ�ر�
 */
void TEST_LED(void)
{
    /* ֻ�������ƣ��㲻����ˮ�� */

    /* delay ��ʼ�� */
    delay_init();

    /* LED ��ʼ�� */
    LED_Init();

    /* ���� LED1 */
    LED_On(1);
    delay_ms(500);

    /* ���� LED2 */
    LED_On(2);
    delay_ms(500);

    /* �ر� LED1 */
    LED_Off(1);
    delay_ms(500);

    /* �ر� LED2 */
    LED_Off(2);
    delay_ms(500);

    /* ͬʱ���� LED1 �� LED2 */
    LED_Toggle(1);
    LED_Toggle(2);

    delay_ms(500);

    /* ͬʱ�ر� LED1 �� LED2 */
    LED_Toggle(1);
    LED_Toggle(2);
}

/* �������±�־λ */
extern uint8_t flag;
/**
 * @brief �������Ժ���
 * @note Ԥ��Ч�������� KEY1���ſ��� LED1 �� 2 ���ر�
 */
void TEST_KEY(void)
{
    /*  delay ��ʼ�� */
    delay_init();

    /* ��ʼ�� LED */
    LED_Init();

    /* ��ʼ�� delay */
    delay_init();

    /* ��ʼ������ */
    KEY_GPIO_Config();

    while (1)
    {
        /* ����ɨ�� */
        KEY_Scan();
        /* ����������� */
        if (flag == 1)
        {
            /* ���� LED1 2�� */
            LED_On(1);
            delay_ms(500);
            delay_ms(500);
            delay_ms(500);
            delay_ms(500);

            /* Ȼ��ر� LED1 */
            LED_Off(1);

            flag = 0;
        }
    }
}

/**
 * @brief USART ���Ժ���
 * @note Ԥ��Ч�������ڽ��յ����ݺ�ͨ�����ڣ�ԭ������
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
 * @brief printf �ض�����Ժ������ض��� USART1��
 * @note Ԥ��Ч����ÿ�뷢�������ַ���
 */
void TEST_Redirect_Printf(void)
{
    int count = 0;

    /*  delay ��ʼ�� */
    delay_init();

    /* USART1 ���ã���ʼ���� */
    USART1_Config();
    while (1)
    {
        printf("��ã����磡Hello World!\r\n");
        printf("count = %d\r\n", count++);
        delay_ms(1000);
    }
}

/**
 * @brief OLED ���Ժ���
 * @note Ԥ��Ч������ʾ��������
 */
void TEST_OLED(void)
{
    int count = 0;

    /*  delay ��ʼ�� */
    delay_init();

    /* OLED ��ʼ�� */
    OLED_Init();

    /* OLED ���� */
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
 * @brief DHT11 ���Ժ���
 *
 */
void TEST_DHT11(void)
{
    uint8_t temper;
    uint8_t humi;

    /*  delay ��ʼ�� */
    delay_init();

    /* USART1 ���ã���ʼ���� */
    USART1_Config();

    /* DHT11 ��ʼ�� */
    DHT11_Init();

    /* OLED ��ʼ�� */
    OLED_Init();
    /* OLED ���� */
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
            printf("temp��ֵ��Ϊ0��\r\n");
        }
        
        /* ��ȡ�����С�� 1 �� */
        delay_ms(1500);
    };
}
