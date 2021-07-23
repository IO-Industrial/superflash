/*
 * \file usb_devices.h
 *
 * USB device definitions
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
#include "usb/usb_device.h"
#include <stdint.h>

namespace superflash {
namespace usb {

    enum eUSB_CONTROL_HINT
    {
        USB_UNDEFINED,
        USB_HID,
        USB_BULK,
    };

    //! \brief Supported USB Device Structure
    struct sf_usb_device {
        uint32_t vid;
        uint32_t pid;
        const char* march_description;
        enum eUSB_CONTROL_HINT usb_hint;
        uint32_t max_transfer;
        uint32_t dcd_addr;
        uint32_t ram_start;
    };

    //! \brief Search for this device in our supported device array
    //!
    //! This function will search for the device in our supported
    //! device array.
    //!
    //! \param  vid
    //! \param  pid
    //!
    //! \returns
    //!
    //! If this device is supported, a pointer to the structure will be returned.
    //! However, if this combination of vid and pid cannot be found, a NULL
    //! will be returned.
    struct sf_usb_device* find(uint32_t vid, uint32_t pid);

    //! \brief Search for this device in our supported device array
    //!
    //! This function will search for the device in our supported
    //! device array.
    //!
    //! \param  dev USB device object
    //!
    //! \returns
    //!
    //! If this device is supported, a pointer to the structure will be returned.
    //! However, if this combination of vid and pid cannot be found, a NULL
    //! will be returned.
    struct sf_usb_device* usb_is_valid_device(USBDevice& dev);

}
}