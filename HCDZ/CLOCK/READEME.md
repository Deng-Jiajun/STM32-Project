# 准备工作

通过 EIDE 内置模板 `STM32F1 Quickstart` 建立

默认芯片是 stm32f103c**8**，Proteus 只有 stm32f103c**6**

需要修改启动文件为 `startup_stm32f10x_ld.s`

同时修改预处理器定义为 `STM32F10X_LD`

修改 main.c

```c
#include "stm32f10x.h"

#define LED_PERIPH RCC_APB2Periph_GPIOC
#define LED_PORT GPIOC
#define LED_PIN GPIO_Pin_13

int main()
{
    GPIO_InitTypeDef gpioDef;
    RCC_APB2PeriphClockCmd(LED_PERIPH, ENABLE);
    gpioDef.GPIO_Mode = GPIO_Mode_Out_PP;
    gpioDef.GPIO_Pin = LED_PIN;
    gpioDef.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(LED_PORT, &gpioDef);
    GPIO_ResetBits(LED_PORT, LED_PIN);

    while (1)
    {

    }
}
```

测试电灯，有效

# 时钟

HSE(High Speed External)

HSI(High Speed Internal)

LSI(Low Speed Internal)

LSE(Low Speed External)

PLL

# 总结

总的来说，没什么内容，就是引入了一个 delay 文件

# 其他问题

KEIL PROJECT 是因为导出的项目有点问题，没办法仿真调试，加上去的

比较尴尬的是，测试结果发现晶振频率不能改，实验结果也不符合预期