/*
 * @Author: JunQiLiu
 * @Date: 2021-09-07 12:47:01
 * @LastEditTime: 2021-09-11 12:21:29
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
#include "adc_app.h"

/* defined the LED0 pin: PB1 */
#define LED0_PIN    GET_PIN(C, 13)

int main(void)
{
    int count = 1;
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);

    modbusSlaveAppStart();

    rt_thread_t adc_tid;
    adc_tid = rt_thread_create("M_Slave",
                            adcGetValueEntry, RT_NULL,
                            1024,
                            15, 10);
    if (adc_tid != RT_NULL)
		rt_thread_startup(adc_tid);

    while (count++)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
    

    return RT_EOK;
}
