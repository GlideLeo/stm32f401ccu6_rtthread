/*
 * @Author: JunQiLiu
 * @Date: 2022-04-08 11:10:26
 * @LastEditTime: 2022-04-08 12:24:30
 * @Description: 
 * @FilePath: \stm32f401ccu6_rtthread\applications\input_app.c
 *  
 */
#include "input_app.h"
#define READ_PIN_1    GET_PIN(B, 1)
#define READ_PIN_2    GET_PIN(B, 2)
#define READ_PIN_3    GET_PIN(B, 3)
#define READ_PIN_4    GET_PIN(B, 4)



extern USHORT usSRegHoldBuf[S_REG_HOLDING_NREGS];

void ioInputGetValueEntry(void *parameter)
{
		rt_pin_mode(READ_PIN_1, PIN_MODE_INPUT_PULLUP );
		rt_pin_mode(READ_PIN_2, PIN_MODE_INPUT_PULLUP );
		rt_pin_mode(READ_PIN_3, PIN_MODE_INPUT_PULLUP );
		rt_pin_mode(READ_PIN_4, PIN_MODE_INPUT_PULLUP );
    while(1)
    {
        usSRegHoldBuf[5] = rt_pin_read(READ_PIN_1);
        usSRegHoldBuf[6] = rt_pin_read(READ_PIN_2);
        usSRegHoldBuf[7] = rt_pin_read(READ_PIN_3);
        usSRegHoldBuf[8] = rt_pin_read(READ_PIN_4);
        rt_thread_delay(50);
    }
}
