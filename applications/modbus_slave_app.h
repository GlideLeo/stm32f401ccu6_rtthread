/*
 * @Author: JunQiLiu
 * @Date: 2021-09-11 09:20:49
 * @LastEditTime: 2021-09-11 09:34:59
 * @Description: 
 * @FilePath: \stm32f401ccu6_rtthread\applications\modbus_slave_app.h
 *  
 */
#ifndef __MODBUS_SLAVE_APP_H__
#define __MODBUS_SLAVE_APP_H__

#include <rtthread.h>

#include "mb.h"
#include "user_mb_app.h"

int modbusSlaveAppStart(void);
#endif
