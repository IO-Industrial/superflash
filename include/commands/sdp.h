/**
 *  @file: sdp.h
 *
 *  Copyright (C) 2020  Joe Turner <joe@agavemountain.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once
#include <stdint.h>

#define SDP_READ_REG     0x0101
#define SDP_WRITE_REG    0x0202
#define SDP_WRITE_FILE   0x0404
#define SDP_ERROR_STATUS 0x0505
#define SDP_WRITE_DCD    0x0a0a
#define SDP_JUMP_ADDRESS 0x0b0b

#pragma pack (1)

//! \brief Serial Download Protocol Command Stucture
//!
//! This 16-Byte SDP command structure is the packet format,
//! for six commands.
//!
struct sdp_command {

	//! \brief COMMAND_TYPE
	//!
	//! Commands supported:
	//!
	//! 0x0101 READ_REGISTER
	//! 0x0202 WRITE_REGISTER
	//! 0x0404 WRITE_FILE
	//! 0x0505 ERROR_STATUS
	//! 0x0A0A DCD_WRITE
	//! 0x0B0B JUMP_ADDRESS
	//!
	uint16_t cmd;

	//! \brief ADDRESS
	//!
	//! Only relevant for READ_REGISTER, WRITE_REGISTER,
	//! WRITE_FILE, DCD_WRITE and JUMP_ADDRESS commands.
	//!
	//! For READ_REGISTER and WRITE_REGISTER commands,
	//! this field is the address to a register.
	//!
	//! For WRITE_FILE and JUMP_ADDRESS commands, this field
	//! is an address to internal or external memory address.
	uint32_t addr;

	//! \brief FORMAT
	//!
	//! 0x08 for 8-bit access
	//! 0x10 for 16-bit access
	//! 0x20 for 32-bit access
	//!
	//! Only relavent for READ_REGISTER and WRITE_REGISTER.
	uint8_t format;

	//! \brief DATA COUNT
	//!
	//! Size of data to read or write.  Only relavent for
	//! WRITE_FILE, READ_REGISTER, WRITE_REGISTER, and DCD_WRITE
	//! commands.  For WRITE_FILE and DCD_WRITE commands DATA COUNT
	//! is in byte units.
	uint32_t cnt;
	
	//! \brief DATA
	//! 
	//! Value to write.  Only relavent for WRITE_REGISTER command.
	uint32_t data;

	//! \brief RESERVED
	//!
	//! Not used in Vybrid ROM
	uint8_t rsvd;
};
#pragma pack ()

