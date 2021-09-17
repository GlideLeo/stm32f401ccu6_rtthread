/*
 * @Author: JunQiLiu
 * @Date: 2021-04-26 01:34:14
 * @LastEditTime: 2021-09-11 18:19:24
 * @Description: 
 * @FilePath: \stm32f401ccu6_rtthread\applications\fal_cfg.h
 *  
 */
/*
 * File      : fal_cfg.h
 * This file is part of FAL (Flash Abstraction Layer) package
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-17     armink       the first version
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include <rtconfig.h>
#include <board.h>


#define STM32_FLASH_START_ADRESS_16K		((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define FLASH_SIZE_GRANULARITY_16K			(4 * 16 * 1024)

#define STM32_FLASH_START_ADRESS_64K		((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define FLASH_SIZE_GRANULARITY_64K			(1 * 64 * 1024)

#define STM32_FLASH_START_ADRESS_128K		((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define FLASH_SIZE_GRANULARITY_128K			(1 * 128 * 1024)

/* ===================== Flash device Configuration ========================= */
extern const struct fal_flash_dev stm32f4_onchip_flash;

/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &stm32f4_onchip_flash,                                           \
}
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
#define FAL_PART_TABLE                                                               \
{                                                                                    \
    {FAL_PART_MAGIC_WROD,        "ef",     "onchip_flash",	 0,     128 * 1024, 0}, \
}
#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* _FAL_CFG_H_ */
