**具体 readme 在下面的两个文件夹里**

- HCDZ 的所有程序都是 stm32f103c6（目的是和 Proteus 配套，因为 Proteus 8.9 SP3 没有 stm32f103c）
- JKDZHX 的 LED 和 Button 也都是 stm32f103c6 和 Proteus 8.9 SP3，但是因为需要的OLED原件 Proteus 8.9 SP3 没有，所以升级到了 Proteus 8.13 SP0，后续的其他程序也会修改为 **stm32f103c8**
- c8 和 c6 程序基本通用，它们的区别在于闪存大小不同导致的部分规格有所不同（c8 比 c6 多一些），同时启动文件(.s) 也需要修改（c6 是 ld(Low-Density)，c8 是 md(Medium-Density)）
