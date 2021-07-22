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

    enum eVENDORS {
        VENDOR_UNKNOWN,
        VENDOR_NXP,
    };

    enum ePROTOCOLS {
        UKNOWN_PROTOCOL = 0,
        UTP_USB = 0x01,
        SDP_UART = 0x2,
        SDP_USB = 0x4,
    };

    struct sf_usb_device {
        uint32_t vid;
        uint32_t pid;
        const char* march_description;

        uint32_t vendor;
        uint32_t protocols;
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