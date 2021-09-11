/*
 * @Author: JunQiLiu
 * @Date: 2021-09-11 11:02:55
 * @LastEditTime: 2021-09-11 13:55:56
 * @Description: 
 * @FilePath: \stm32f401ccu6_rtthread\applications\adc_app.c
 *  
 */
#include "adc_app.h"

#define LOG_TAG     "ADC"    
#define LOG_LVL     LOG_LVL_DBG  
#include <ulog.h>

#define ADC_DEV_NAME        "adc1"      /* ADC 设备名称 */
#define ADC_DEV_CHANNEL     5           /* ADC 通道 */
#define REFER_VOLTAGE       330         /* 参考电压 3.3V,数据精度乘以100保留2位小数*/
#define CONVERT_BITS        (1 << 12)   /* 转换位数为12位 */

static int adc_vol_test(int argc, char *argv[])
{
    rt_adc_device_t adc_dev;
    rt_uint32_t value, vol;
    rt_err_t ret = RT_EOK;
    rt_uint8_t channelNumber = 1;

    if (argc < 2)
    {
        rt_kprintf("Usage: adc_vol_test 0/1/2/3...\n");
        return -1;
    }
    else
    {
        channelNumber = *argv[1]-0x30;
    }

    /* 查找设备 */
    adc_dev = (rt_adc_device_t)rt_device_find(ADC_DEV_NAME);
    if (adc_dev == RT_NULL)
    {
        rt_kprintf("adc sample run failed! can't find %s device!\n", ADC_DEV_NAME);
        return RT_ERROR;
    }
    
    /* 使能设备 */
    ret = rt_adc_enable(adc_dev, channelNumber);

    /* 读取采样值 */
    value = rt_adc_read(adc_dev, channelNumber);
    rt_kprintf("the value is :%d \n", value);

    /* 转换为对应电压值 */
    vol = value * REFER_VOLTAGE / CONVERT_BITS;
    rt_kprintf("the voltage is :%d.%02d \n", vol / 100, vol % 100);

    /* 关闭通道 */
    ret = rt_adc_disable(adc_dev, channelNumber);

    return ret;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(adc_vol_test, adc voltage convert test);


extern USHORT usSRegHoldBuf[S_REG_HOLDING_NREGS];

void adcGetValueEntry(void *parameter)
{
    rt_adc_device_t adc_dev;
    rt_uint32_t value;
    rt_int32_t temperature;
    adc_dev = (rt_adc_device_t)rt_device_find(ADC_DEV_NAME);
    if (adc_dev == RT_NULL)
    {
        LOG_E("adc sample run failed! can't find %s device!\n", ADC_DEV_NAME);
    }
    
    while(1)
    {
        for(int i = 4; i < 10; i++)
        {
            /* 使能设备 */
            rt_adc_enable(adc_dev, i);
            /* 读取采样值 */
            value = rt_adc_read(adc_dev, i);
            usSRegHoldBuf[i] = value * 3300 / 4096;
            /* 关闭通道 */
            rt_adc_disable(adc_dev, i);   
        }
        /*读取内部温度*/
        rt_adc_enable(adc_dev, 16);
        value = rt_adc_read(adc_dev, 16);
        temperature = value * 3300 / 4096 ;
        // rt_kprintf("voltage is %d\n",(int)(temperature));
        temperature = (temperature - 760)*4 +250;
        // rt_kprintf("temperature is %d\n",temperature);
        usSRegHoldBuf[0] = temperature;
        rt_adc_disable(adc_dev, 16);

        rt_thread_delay(500);
    }
    
}