# 文件描述

## Library

全部的库函数文件

\Libraries\STM32F10x_StdPeriph_Driver 下的 inc 和 src，共 23 对，46 个文件（`.c` +`. h`）

## Start

### 内核寄存器

\Libraries\CMSIS\CM3\CoreSupport

`core_cm3.c`

`core_cm3.h`

### STM32 启动文件

\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\startup\arm

`startup_stm32f10x_cl.s`

`startup_stm32f10x_hd.s`

`startup_stm32f10x_hd_vl.s`

`startup_stm32f10x_ld.s`

`startup_stm32f10x_ld_vl.s`

`startup_stm32f10x_md.s`

`startup_stm32f10x_md_vl.s`

`startup_stm32f10x_xl.s`

### 标准头文件

\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\

`stm32f10x.h` （寄存器地址，类似 reg51.h）

`system_stm32f10x.c`（时钟配置相关）

`system_stm32f10x.h`（时钟配置相关）



## User

用户程序（包括 `main.c`）



来自 \Project\STM32F10x_StdPeriph_Template

1. `stm32f10x_conf.h` （配置库函数头文件包含关系（以及一个所有库都需要的用于参数检查的函数定义））
2. `stm32f10x_it.c`（中断函数配置相关）
3. `stm32f10x_it.h`（中断函数配置相关）

# 注意要点

要设置 Include Path

要设置宏定义 `USE_STDPERIPH_DRIVER`