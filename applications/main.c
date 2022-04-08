/*
 * @Author: JunQiLiu
 * @Date: 2021-09-07 12:47:01
 * @LastEditTime: 2022-04-08 12:24:25
 * @Description: 
 * @FilePath: \stm32f401ccu6_rtthread\applications\main.c
 *  
 */
/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "modbus_slave_app.h"
#include "user_mb_app.h"
#include "adc_app.h"
#include "input_app.h"
#include <vconsole.h>
#include <fal.h>
extern USHORT usSRegHoldBuf[S_REG_HOLDING_NREGS];

#define LOG_TAG     "main"    
#define LOG_LVL     LOG_LVL_INFO  
#include <ulog.h>

/* defined the LED0 pin: PB1 */
#define LED0_PIN    GET_PIN(C, 13)

#define WDT_DEVICE_NAME    "wdt"    /* 看门狗设备名称 */

static rt_device_t wdg_dev;         /* 看门狗设备句柄 */

static void idle_hook(void)
{
    /* 在空闲线程的回调函数里喂狗 */
    rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, NULL);
}


static int wdtStart(void)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t timeout = 1;        /* 溢出时间，单位：秒 */
    char device_name[RT_NAME_MAX];

    rt_strncpy(device_name, WDT_DEVICE_NAME, RT_NAME_MAX);
    /* 根据设备名称查找看门狗设备，获取设备句柄 */
    wdg_dev = rt_device_find(device_name);
    if (!wdg_dev)
    {
        rt_kprintf("find %s failed!\n", device_name);
        return RT_ERROR;
    }

    /* 设置看门狗溢出时间 */
    ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
    if (ret != RT_EOK)
    {
        rt_kprintf("set %s timeout failed!\n", device_name);
        return RT_ERROR;
    }
    /* 启动看门狗 */
    ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_START, RT_NULL);
    if (ret != RT_EOK)
    {
        rt_kprintf("start %s failed!\n", device_name);
        return -RT_ERROR;
    }
    /* 设置空闲线程回调函数 */
    rt_thread_idle_sethook(idle_hook);

    return ret;
}

static rt_device_t vcom_shell_device = NULL;
void change_shell(void)
{
    vcom_shell_device = rt_device_find("vcom");
    if (vcom_shell_device)
    {
        vconsole_switch(vcom_shell_device);
    }
}


int main(void)
{
    int count = 1;
    uint8_t readBuf[8];
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    
    // change_shell();
    fal_init();
    wdtStart();
    fal_partition_read(fal_partition_find("ef"),127*1024,readBuf,8);
    if(readBuf[0] == 0xff)
    {
        usSRegHoldBuf[1] = 1;
    }
    else
    {
        usSRegHoldBuf[1] = readBuf[0];
    }
    
    modbusSlaveAppStart();
    LOG_I("modbus slave address is %d",usSRegHoldBuf[1]);
    rt_thread_t io_input_tid;
    io_input_tid = rt_thread_create("IO_INPUT",
                            ioInputGetValueEntry, RT_NULL,
                            1024,
                            15, 10);
    if (io_input_tid != RT_NULL)
    	rt_thread_startup(io_input_tid);

    // rt_thread_t adc_tid;
    // adc_tid = rt_thread_create("M_Slave",
    //                         adcGetValueEntry, RT_NULL,
    //                         1024,
    //                         15, 10);
    // if (adc_tid != RT_NULL)
	// 	rt_thread_startup(adc_tid);

    // fal_partition_erase(fal_partition_find("ef"),0,8);
    // fal_partition_write(fal_partition_find("ef"),0,testBuf,8);
    // fal_partition_read(fal_partition_find("ef"),127*1024,readBuf,8);
    // rt_kprintf("read: %02x %02x %02x %02x %02x %02x %02x %02x\n",readBuf[0],readBuf[1],readBuf[2],readBuf[3],readBuf[4],readBuf[5],readBuf[6],readBuf[7]);

    while (count++)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
    
    return RT_EOK;
}
