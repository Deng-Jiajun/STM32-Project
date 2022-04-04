#include "stm32f10x_gpio.h"

// 设置某个 P 口的某个引脚为高电平
void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIOx->BSRR |= GPIO_Pin; // 为什么这么写？去看 GPIO_Pin_x 针脚定义
}

// 设置某个 P 口的某个引脚为低电平
void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIOx->BRR |= GPIO_Pin; // 要不然就直接设置 BRR
}

// GPIO_Init 初始化函数
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct)
{
    uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
    uint32_t tmpreg = 0x00, pinmask = 0x00;

    /*-------------- GPIO Mode Configuration | GPIO 模式配置 ---------------*/

    // 把输入参数 GPIO_Mode 的低四位暂存在 currentmode
    currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F);

    // bit4 是 1 表示输出，bit4 是 0 则是输入
    // 判断 bit4 是 1 还是 0，即判断是输入模式还是输出模式
    if ((((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x10)) != 0x00)
    {
        /* Output mode 输出模式，则设置输出速度 */
        currentmode |= (uint32_t)GPIO_InitStruct->GPIO_Speed;
    }
    /*------ GPIO CRL Configuration | GPIO CRL 寄存器配置 -------------*/
    /* Configure the eight low port pins | 配置低 8 位引脚（Pin0 ~ Pin7） */
    if (((uint32_t)GPIO_InitStruct->GPIO_Pin & ((uint32_t)0x00FF)) != 0x00)
    {
        // 低 8 位里有 1，说明是低 8 位的某个引脚

        // 先备份 CRL 寄存器的值
        tmpreg = GPIOx->CRL;

        // 循环，从 Pin0 开始寻找具体的 Pin（0~7）
        for (pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            // pos的值为 1左移pinpos位
            pos = ((uint32_t)0x01) << pinpos;

            /* Get the port pins position */
            /* 令 pos 与输入参数 GPIO_Pin 作位与运算，为下面的判断作准备 */
            currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
            // 其实就是判断 currentpin==pos
            // 但是它们的类型不一样（uint16_t和uint32_t），所以先做与运算

            // 若 currentpin=pos，则找到目标引脚（pos = 0,1,2..7）
            if (currentpin == pos)
            {
                // pinpos 的值左移两位（乘以 4）因为寄存器中 4位 配置一个引脚
                pos = pinpos << 2;

                /* Clear the corresponding low control register bits */
                /* 把控制这个引脚的 4 个寄存器位清零，其它寄存器位不变
                   再把 4 个 1 挪到要清零的对应位置，取反，赋值 */
                pinmask = ((uint32_t)0x0F) << pos;
                tmpreg &= ~pinmask;

                /* Write the mode configuration in the corresponding bits */
                // 向寄存器写入将要配置的引脚的模式（暂存 tmpreg）
                tmpreg |= (currentmode << pos);

                /* 在 F1 系列没有专门设置输入上拉或者下拉的寄存器，属于伪上/下拉
                   在 F4 系列里面有专门的寄存器进行设置 */
                /* Reset the corresponding ODR bit */
                // 判断是否为下拉输入模式，是的话就把对应的 ODR 位置 0
                if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
                {
                    // 下拉输入模式，引脚默认置 0，对 BRR 寄存器写 1 可对引脚置 0（低电平）
                    // BRR 里一位代表一个引脚，所以把 1 左移 pinpos 位即可
                    GPIOx->BRR = (((uint32_t)0x01) << pinpos);
                }

                /* Set the corresponding ODR bit*/
                // 判断是否为上拉输入模式，是的话就把对应的 ODR 位置 1
                //（高八位和低八位的 if else 写法还不一样，挺离谱的）
                if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
                {
                    //上拉输入模式，引脚默认值为 1，对 BSRR 寄存器写 1 可对引脚置 1（高电平）
                    // BSRR 里一位代表一个引脚，所以把 1 左移 pinpos 位即可
                    GPIOx->BSRR = (((uint32_t)0x01) << pinpos);
                }
            }
        }
        // 把前面处理后的暂存值写入到 CRL 寄存器中
        GPIOx->CRL = tmpreg;
    }
    /*------ GPIO CRH Configuration | GPIO CRH 寄存器配置 -------------*/
    /* Configure the eight high port pins | 配置高 8 位引脚（Pin8 ~ Pin15） */
    if (GPIO_InitStruct->GPIO_Pin > 0x00FF)
    {
        //  比 0x00FF 大，说明是高 8 位的某个引脚

        // 先备份 CRH 寄存器的值
        tmpreg = GPIOx->CRH;

        // 循环，从 Pin8 开始寻找具体的 Pin（8~15）
        for (pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            // pos的值为 1左移 pinpos+8 位
            pos = (((uint32_t)0x01) << (pinpos + 0x08));

            /* Get the port pins position */
            /* 令 pos 与输入参数 GPIO_Pin 作位与运算，为下面的判断作准备 */
            currentpin = ((GPIO_InitStruct->GPIO_Pin) & pos);
            // 其实就是判断 currentpin==pos
            // 但是它们的类型不一样（uint16_t和uint32_t），所以先做与运算

            // 若 currentpin=pos，则找到目标引脚（pos = 8,9,10..15）
            if (currentpin == pos)
            {

                // pinpos 的值左移两位（乘以 4）因为寄存器中 4位 配置一个引脚
                pos = pinpos << 2;

                /* Clear the corresponding high control register bits */
                /* 把控制这个引脚的 4 个寄存器位清零，其它寄存器位不变
                   再把 4 个 1 挪到要清零的对应位置，取反，赋值 */
                pinmask = ((uint32_t)0x0F) << pos;
                tmpreg &= ~pinmask;

                /* Write the mode configuration in the corresponding bits */
                // 向寄存器写入将要配置的引脚的模式（暂存 tmpreg）
                tmpreg |= (currentmode << pos);

                /* 在 F1 系列没有专门设置输入上拉或者下拉的寄存器，属于伪上/下拉
                   在 F4 系列里面有专门的寄存器进行设置 */
                /* Reset the corresponding ODR bit*/
                // 判断是否为下拉输入模式，是的话就把对应的 ODR 位置 0
                if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
                {
                    // 下拉输入模式，引脚默认置 0，对 BRR 寄存器写 1 可对引脚置 0（低电平）
                    // BRR 里一位代表一个引脚，所以把 1 左移 pinpos 位即可
                    GPIOx->BRR = (((uint32_t)0x01) << (pinpos + 0x08));
                }

                /* Set the corresponding ODR bit*/
                // 判断是否为上拉输入模式，是的话就把对应的 ODR 位置 1
                if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
                {
                    //上拉输入模式，引脚默认值为 1，对 BSRR 寄存器写 1 可对引脚置 1（高电平）
                    GPIOx->BSRR = (((uint32_t)0x01) << (pinpos + 0x08));
                }
            }
        }
        // 把前面处理后的暂存值写入到 CRH 寄存器中
        GPIOx->CRH = tmpreg;
    }
}
