/*
 * \file soc_definitions.h
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
#include <string>

//! \brief Protocol/Bus enumeration
//!
//! This enumeration lays out the preferred transports/busses/protocols
//! to use to talk to the target device. 
enum eProtocolBus
{
    eUSB_HID,
    eUSB_BULK,
    eUART_SERIAL,
    eFLEX_CAN,
};

//! \brief SoC Device Profile
//!
//! This structure describes what a device is, for us to talk to it.
struct SoCDeviceProfile
{
    //! \brief Machine Architecture 
    //! Short description ot machine architecture
    //! example "vybrid"
    std::string march;

    //! \brief Machine Architecture description
    //! example: Vybrid VF610 SysRam0
    std::string march_description;

    //! \brief protocol/bus hint
    //!
    //! Hint to tell us how to address this device.
    enum eProtocolBus _protocol;
    
    uint32_t max_packet_size;

    uint32_t dcd_addr;

    uint32_t ram_address;

    uint32_t ram_size;

};

