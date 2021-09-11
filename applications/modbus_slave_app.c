/*
 * @Author: JunQiLiu
 * @Date: 2021-09-11 09:20:34
 * @LastEditTime: 2021-09-11 12:20:43
 * @Description: 
 * @FilePath: \stm32f401ccu6_rtthread\applications\modbus_slave_app.c
 *  
 */
#include "modbus_slave_app.h"

#define LOG_TAG     "MB_Slave"    
#define LOG_LVL     LOG_LVL_DBG  
#include <ulog.h>

#define SLAVE_ADDR      81
#define PORT_NUM        2
#define PORT_BAUDRATE   9600
#define PORT_PARITY     MB_PAR_NONE

#define MB_POLL_THREAD_PRIORITY  10
#define MB_SEND_THREAD_PRIORITY  RT_THREAD_PRIORITY_MAX - 1

#define MB_POLL_CYCLE_MS 100

extern USHORT usSRegHoldBuf[S_REG_HOLDING_NREGS];

static void send_thread_entry(void *parameter)
{
    USHORT         *usRegHoldingBuf;
    usRegHoldingBuf = usSRegHoldBuf;
    rt_base_t level;

    while (1)
    {
        /* Test Modbus Master */
        level = rt_hw_interrupt_disable();

        usRegHoldingBuf[3] = (USHORT)(rt_tick_get() / 100);

        rt_hw_interrupt_enable(level);

        rt_thread_mdelay(1000);
    }
}


static void mb_slave_poll(void *parameter)
{
    if (rt_strstr(parameter, "RTU"))
    {
#ifdef PKG_MODBUS_SLAVE_RTU
        eMBInit(MB_RTU, SLAVE_ADDR, PORT_NUM, PORT_BAUDRATE, PORT_PARITY);
        LOG_D("Modbus RTU Slave Init");
#else
        rt_kprintf("Error: Please open RTU mode first");
#endif
    }
    else if (rt_strstr(parameter, "ASCII"))
    {
#ifdef PKG_MODBUS_SLAVE_ASCII
        eMBInit(MB_ASCII, SLAVE_ADDR, PORT_NUM, PORT_BAUDRATE, PORT_PARITY);
#else
        rt_kprintf("Error: Please open ASCII mode first");
#endif
    }
    else if (rt_strstr(parameter, "TCP"))
    {
#ifdef PKG_MODBUS_SLAVE_TCP
        eMBTCPInit(0);
#else
        rt_kprintf("Error: Please open TCP mode first");
#endif
    }
    else
    {
        rt_kprintf("Error: unknown parameter");
    }
    eMBEnable();
    while (1)
    {
        eMBPoll();
        rt_thread_mdelay(MB_POLL_CYCLE_MS);
    }
}


int modbusSlaveAppStart(void)
{
    rt_thread_t tid1 = RT_NULL;//, tid2 = RT_NULL;

    tid1 = rt_thread_create("md_s_poll", mb_slave_poll, "RTU", 1024, MB_POLL_THREAD_PRIORITY, 10);
    if (tid1 != RT_NULL)
    {
        rt_thread_startup(tid1);
    }
    else
    {
        goto __exit;
    }

    // tid2 = rt_thread_create("md_s_send", send_thread_entry, RT_NULL, 512, MB_SEND_THREAD_PRIORITY, 10);
    // if (tid2 != RT_NULL)
    // {
    //     rt_thread_startup(tid2);
    // }
    // else
    // {
    //     goto __exit;
    // }

    return RT_EOK;

__exit:
    if (tid1)
        rt_thread_delete(tid1);
    // if (tid2)
    //     rt_thread_delete(tid2);

    return -RT_ERROR;
}
