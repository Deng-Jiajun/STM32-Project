#include "iic.h"

/**
 * SCL �ߵ�ƽ����������Ч��������Ҫ��֤�� SCL ����ǰ�� SDA Ҫ׼����
 * ������/ֹ�źţ�Ҫ�� SDA ����ǰ�������� SCL
 * ! ���ǣ�����ǰ SDA �ĵ�ƽ��ȻҪ������ SCL ǰ��׼����
 */

/**
 * @brief IIC ��ʼ������ʼ�� SCL �� SDA �� GPIO��
 *
 * @note SCL �� PB6��SDA �� PB7
 */
void IIC_Init(void)
{
    /* ��ʼ�� SCL �� SDA �� GPIO Ϊ���ģʽ*/
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* ���� SCL �� SDA */
    IIC_SCL = 1;
    IIC_SDA = 1;
}

/**
 * @brief ������ʼ�ź�
 *
 * @note SCL �ߵ�ƽ�ڼ䣬SDA �ɸߵ�������
 *
 */
void IIC_Start(void)
{
    /* ���� SDA Ϊ���ģʽ */
    SDA_OUT();
    /* ���� SDA �� SCL */
    IIC_SDA = 1; // Ҫ������ SCL ǰ�� SDA Ϊ�ߵ�ƽ
    IIC_SCL = 1;
    /* ����һ��ʱ�� */
    delay_us(4);
    /* ���� SDA���� �� �ͣ� */
    IIC_SDA = 0;
    /* �ٳ���һ��ʱ�䣨��֤�γ���ʼ�źţ� */
    delay_us(4);
    /* ���� SCL��׼���շ����� */
    IIC_SCL = 0;
}

/**
 * @brief ����ֹͣ�ź�
 *
 * @note SCL �ߵ�ƽ�ڼ䣬SDA �ɵ͵�������
 *
 */
void IIC_Stop(void)
{
    /* ���� SDA Ϊ���ģʽ */
    SDA_OUT();
    /* ���� SCL �� SDA */
    IIC_SCL = 0;
    IIC_SDA = 0; // Ҫ������ SCL ǰ�� SDA Ϊ�͵�ƽ
    /* ����һ��ʱ�� */
    delay_us(4);

    /* ������ SCL�������� SDA���� �� �ͣ� */
    IIC_SCL = 1;
    IIC_SDA = 1;
    /* �ٳ���һ��ʱ�䣨��֤�γ�ֹͣ�źţ� */
    delay_us(4);
}

/**
 * @brief д��һ���ֽڣ�byte, 8bit��������
 *
 * @param data Ҫд�������
 * @return uint8_t �յ���Ӧ���ź�
 * @retval 0 �յ�Ӧ���ź�
 * @retval 1 û���յ�Ӧ���ź�
 */
uint8_t IIC_Send_Data(uint8_t data)
{
    /* �յ���Ӧ���ź� */
    uint8_t ack;

    uint8_t mask;

    /* ���� SDA Ϊ���ģʽ */
    SDA_OUT();

    /* ��λȡ�������ͣ������λ��ʼ�� */
    for (mask = 0x80; mask != 0; mask >>= 1)
    {
        if (mask & data)
        {
            /* д�� 1 */
            IIC_SDA = 1;
        }
        else
        {
            /* д�� 0 */
            IIC_SDA = 0;
        }
        /* ά�� SDA һ��ʱ�� */
        delay_us(4);

        /* Ȼ������ SCL��ά��һ��ʱ�� */
        IIC_SCL = 1;
        delay_us(4);

        /* ������ SCL����һλ������� */
        IIC_SCL = 0;
    }
    /* ���ݷ�����ϣ����ӻ�Ӧ�� */

    /* ���� SDA Ϊ����ģʽ */
    SDA_IN();
    /* �ͷ� SDA���� */
    IIC_SDA = 1;
    /* �ȴ��ӻ�Ӧ�� */
    delay_us(4);

    /* ���� SCL����ȡӦ���ź� */
    IIC_SCL = 1;
    ack = READ_SDA;

    /* ά��һ��ʱ�������� SCL�����ִ��������9 ��λͨ���� IIC ���ߣ� */
    delay_us(4); // ���ʱ��Ӧ�ÿ���һ���ڶ� ack ֮ǰ��һ����֮�󣬲������岻��
    IIC_SCL = 0;

    /* ����Ӧ���ź� */
    return ack;
}

/**
 * @brief ��֤�ӻ��Ƿ����
 *
 * @param addr �ӻ��ĵ�ַ
 * @return uint8_t �յ���Ӧ���ź�
 * @retval 0 �յ�Ӧ���źţ��ӻ�����
 * @retval 1 û���յ�Ӧ���źţ��ӻ�������
 */
uint8_t IIC_Check_Address(uint8_t address)
{
    /* �յ���Ӧ���ź� */
    uint8_t ack;

    /* ������ʼ�ź� */
    IIC_Start();

    /* д��ӻ���ַ������Ӧ���ź� */
    /* ��ַ�ڸ� 7 λ����������һλ���� 8 λΪ 0����ʾдģʽ */
    ack = IIC_Send_Data(address << 1);

    /* ����ֹͣ�ź� */
    IIC_Stop();

    /* ����Ӧ���ź� */
    return ack;
}
