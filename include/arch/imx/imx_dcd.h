/*
 * \file imx_dcd.h
 *
 * Device Configuration Data (DCD)
 *
 * \copyright  Copyright (C) 2021  Joe Turner <joe@agavemountain.com>
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */
#ifndef _IMX_DCD_H_
#define _IMX_DCD_H_
#include <stdint.h>

#define DCD_HEADER_MAGIC        0xD2
#define DCD_VERSION             0x40
#define DCD_VERSION_IMX8M       0x41

#define DCD_CMD_WRITE           0xC1    //!< Write Data Command
#define DCD_CMD_CHECK           0xCF    //!< Check Data Command
#define DCD_CMD_NOP             0xC0    //!< NOP Command
#define DCD_CMD_UNLOCK          0xB2    //!< Unlock Command


#pragma pack (1)
struct dcd_header {
        uint8_t magic;
        uint16_t length;
        uint8_t version;
};
#pragma pack ()

#endif
