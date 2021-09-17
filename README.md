<!--
 * @Author: JunQiLiu
 * @Date: 2021-09-07 12:47:01
 * @LastEditTime: 2021-09-18 02:04:26
 * @Description: 
 * @FilePath: \stm32f401ccu6_rtthread\README.md
 *  
-->
# STM32F401CCU6 rt-thread modbus工程模板

[![RTT_STM32F401](https://github.com/JassyL/stm32f401ccu6_rtthread/actions/workflows/scons.yml/badge.svg)](https://github.com/JassyL/stm32f401ccu6_rtthread/actions/workflows/scons.yml)
## 简介

本项目为目前市面上比较便宜的核心板 STM32F401CCU6 的rt-thread工程模板，配置了FinSH(命令行支持)、FAL(Flash 抽象层)、freemodbus(armink移植的freemodbus组件)、USB虚拟串口以及ADC等功能，可用于制作各类modbus RTU slave节点。

## 开发板介绍

开发板外观如下图所示：

![board](figures/board.png)

该核心板常用 **板载资源** 如下：

- MCU：STM32F401CCU6，主频 84MHz，256KB FLASH ，64KB RAM
- 常用外设
  - LED：2个，D0（红色，电源），D1（绿色，PC13）
  - 按键：1个，K0（PA0）
  - USB
## 外设支持

本 BSP 目前对外设的支持情况如下：

| **板载外设**      | **支持情况** | **备注**                              |
| :----------------- | :----------: | :------------------------------------- |
| USB 转串口        |   支持     |                                       |
| SPI Flash         |   暂不支持     |                                       |
| **片上外设**      | **支持情况** | **备注**                              |
| GPIO              |     支持     | |
| UART              |     支持     | UART1/2                            |
| SPI               |   暂不支持     |                               |
| I2C               |   暂不支持     |                              |
| RTC               |   支持   | 软件RTC                              |
| IWG               |   暂不支持   | 即将支持                              |
| ADC               |   支持   | 通道1\4\5\6\7\8\9\tempraure |

## 扩展包支持
|**包名称**|**支持情况**|**备注**|
|-|-|-|
|freemodbus|已支持RTU|使用UART2|
|ulog|已支持| |
|FAL|已支持| |
|easyflash|无法支持|只有一个128K扇区空余，不满足要求|
|USB CDC|支持| |


## 运行

下载程序成功之后，系统会自动运行。

连接开发板串口1(或开启USB虚拟串口)到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     4.0.4 build Sep 18 2021
 2006 - 2021 Copyright by rt-thread team
[D/FAL] (fal_flash_init:61) Flash device |             onchip_flash | addr: 0x08020000 | len                                                                                           : 0x00020000 | blk_size: 0x00020000 |initialized finish.
[I/FAL] ==================== FAL partition table ====================
[I/FAL] | name | flash_dev    |   offset   |    length  |
[I/FAL] -------------------------------------------------------------
[I/FAL] | ef   | onchip_flash | 0x00000000 | 0x00020000 |
[I/FAL] =============================================================
[I/FAL] RT-Thread Flash Abstraction Layer (V0.5.0) initialize success.
msh >01-01 08:00:00 D/MB_Slave md_s_pol: Modbus RTU Slave Init
```

使用 modbus poll 软件连接串口2,设置9600-8-1-N,示例只使用了10个保持寄存器，读取结果如下：
![](https://qiniu.datasheep.cn/20210918015535.png)


通过修改modbus地址对应的保持寄存器，板子会自动重启并启用新的地址：
![](https://qiniu.datasheep.cn/adcmodbus.gif)