/*
 * \file ivt_header.h
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
#pragma once

/* Command tags and parameters */
#define IVT_HEADER_TAG			0xD1
#define IVT_VERSION			0x40
#define IVT_VERSION_IMX8M		0x41
#define DCD_HEADER_TAG			0xD2
#define DCD_VERSION			0x40
#define DCD_VERSION_IMX8M		0x41

#pragma pack (1)
struct ivt_header {
        uint8_t tag;
        uint16_t length;
        uint8_t version;
};
#pragma pack ()