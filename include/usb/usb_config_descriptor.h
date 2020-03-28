/*
 * \file usb_config_descriptor.h
 *
 * USB device class
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
#include "usb/usb_defs.h"

namespace superflash {
namespace usb {

    //! \brief USBConfigDescriptor object
    //!
    //! This destructor takes care of freeing the configuration descriptor
    class USBConfigDescriptor {
    public:
        struct libusb_config_descriptor* config;

        USBConfigDescriptor()
            : config(NULL)
        {
        }

        //! \brief Specialized constructor
        USBConfigDescriptor(libusb_device* device, uint8_t idx = 0)
        {
            getConfigDescriptor(device, idx);
        }

        int getConfigDescriptor(libusb_device* device, uint8_t idx = 0)
        {
            return libusb_get_config_descriptor(device, idx, &config);
        }

        //! Get the USB configuration descriptor for the currently active 
        //! configuration. This is a non-blocking function which does 
        //! not involve any requests being sent to the device.
        int getActiveConfigDescriptor(libusb_device* device)
        {
            return libusb_get_active_config_descriptor(device, &config);
        }

        //! \brief destructor
        //! Free configuration descriptor as required.
        ~USBConfigDescriptor()
        {
            if (config) {
                libusb_free_config_descriptor(config);
            }
        }

    private:
    };

}
}
