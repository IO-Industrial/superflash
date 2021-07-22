/*
 * \file imx_magic.h
 *
 * UART MAGIC SEQUENCE
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
#include <stdint.h>

//! \brief MAGIC Sequence for UART
//!
//! While SDP protocol is the same over serial as it is over USB, 
//! the UART code will push a "magic" bytes to tell the target device we
//! are attempting to talk to it with SDP.   The target device will
//! respond with magic bytes as the ack.
extern uint8_t uart_magic[] ;

//! \brief MAGIC Sequence for Vybrid CAN
//!
//! Send a packet with pattern 0x67898967 to the CAN-device. While sending any packet to the
//! device, ensure the host ID is always set as 0x14. After sending the packet, configure the receive
//! message buffer to receive a response packet from the CAN-device, ensuring that the device ID is
//! always set to 0x04. Implement the echo-retry flow control mechanism for a system defined retry
//! count.
//!
//! Once the host receives back the same pattern 0x67898967 from the device, the host reaches a state
//! called “associated”.
extern uint8_t vybrid_can_magic[] ;

extern uint8_t vybrid_HAB_development[] ;
extern uint8_t vybrid_HAD_production[] ;