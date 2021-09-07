<!--
 * @Author: JunQiLiu
 * @Date: 2021-09-07 12:47:01
 * @LastEditTime: 2021-09-07 13:50:32
 * @Description: 
 * @FilePath: \stm32f401ccu6c:\Doc\WorkDir\stm32f401ccu6_rtthread\README.md
 *  
-->
# STM32F401CCU6 rt-thread工程模板

[![RTT_STM32F401](https://github.com/JassyL/stm32f401ccu6_rtthread/actions/workflows/scons.yml/badge.svg)](https://github.com/JassyL/stm32f401ccu6_rtthread/actions/workflows/scons.yml)
## 简介

本项目为 STM32F401CCU6 核心板的rt-thread工程模板。
## 开发板介绍

【此处简单介绍一下开发板】

开发板外观如下图所示：

![board](figures/board.png)

该核心板常用 **板载资源** 如下：

- MCU：STM32F401CCU6，主频 84MHz，256KB FLASH ，64KB RAM
- 常用外设
  - LED：x个，DS0（红色，PB1），DS1（绿色，PB0）
  - 按键：x个，K0（兼具唤醒功能，PA0），K1（PC13）
- 常用接口：USB 转串口、SD 卡接口、以太网接口、LCD 接口等
- 调试接口，标准 JTAG/SWD
## 外设支持

本 BSP 目前对外设的支持情况如下：

| **板载外设**      | **支持情况** | **备注**                              |
| :----------------- | :----------: | :------------------------------------- |
| USB 转串口        |   暂不支持     |                                       |
| SPI Flash         |   暂不支持     |                                       |
| CAN               |   暂不支持   |                                       |
| **片上外设**      | **支持情况** | **备注**                              |
| GPIO              |     支持     | PA0, PA1... PK15 ---> PIN: 0, 1...176 |
| UART              |     支持     | UART1/x/x                             |
| SPI               |   暂不支持     | SPI1/x/x                              |
| I2C               |   暂不支持     | 软件 I2C                              |
| SDIO              |   暂不支持   | 即将支持                              |
| RTC               |   暂不支持   | 即将支持                              |
| PWM               |   暂不支持   | 即将支持                              |
| USB Device        |   暂不支持   | 即将支持                              |
| USB Host          |   暂不支持   | 即将支持                              |
| IWG               |   暂不支持   | 即将支持                              |
| xxx               |   暂不支持   | 即将支持                              |
| **扩展模块**      | **支持情况** | **备注**                              |
|     xxx 模块      |   支持   |                                      |


## 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

## 运行结果

下载程序成功之后，系统会自动运行，【这里写开发板运行起来之后的现象，如：LED 闪烁等】。

连接开发板对应串口到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     3.1.1 build Nov 19 2018
 2006 - 2018 Copyright by rt-thread team
msh >
```
## 进阶使用

此 BSP 默认只开启了 GPIO 和 串口1 的功能，如果需使用 SD 卡、Flash 等更多高级功能，需要利用 ENV 工具对BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

3. 输入`pkgs --update`命令更新软件包。

4. 输入`scons --target=mdk4/mdk5/iar` 命令重新生成工程。

本章节更多详细的介绍请参考 [STM32 系列 BSP 外设驱动使用教程](../docs/STM32系列BSP外设驱动使用教程.md)。

## 注意事项

- xxx

## 联系人信息

维护人:

-  [xxx](https://个人主页), 邮箱：<xxx@xxx.com>