/*
 * \file imx_ivt.h
 *
 * Image Vector Table (IVT)
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
#ifndef _IMX_IVT_H_
#define _IMX_IVT_H_

#include <stdint.h>
 
/*
+ * IVT header definitions
+ * Security Reference Manual for i.MX 7Dual and 7Solo Applications Processors,
+ * Rev. 0, 03/2017
+ * Section : 6.7.1.1
+ */
#define IVT_HEADER_MAGIC	0xD1
#define IVT_TOTAL_LENGTH	0x20
#define IVT_HEADER_V1		0x40
#define IVT_HEADER_V2		0x41

struct ivt_header {
	uint8_t		magic;
	uint16_t	length;
	uint8_t		version;
} __attribute__((packed));

struct ivt {
	struct ivt_header hdr;	//!< IVT header above
	uint32_t entry;		//!< Absolute address of first instruction
	uint32_t reserved1;	//!< Reserved should be zero
	uint32_t dcd;		//!< Absolute address of the image DCD
	uint32_t boot;		//!< Absolute address of the boot data
	uint32_t self;		//!< Absolute address of the IVT
	uint32_t csf;		//!< Absolute address of the CSF
	uint32_t reserved2;	//!< Reserved should be zero 
};


#endif
