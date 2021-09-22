/*
 * \file usb_enumerator.h
 *
 * USB device list enumerator
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
#include <memory>
#include <vector>

#include "usb/usb_context.h"
#include "usb/usb_device.h"
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/spdlog.h"

namespace superflash {
namespace usb {

    //! \brief USB device enumerator
    //!
    //! This class will get a list of USB devices, and populate the given
    //! vector (convert the fixed array of pointers into an STL vector),
    //! with the device pointers.
    //!
    //! The destructor will free the device list, guaranteeing
    //! that it gets released.
    //!
    class USBEnumerator {
    public:
        //! \brief Specialized constructor
        //!
        //! \param context  - Shared pointer to libusb context object
        //! \param devices  - reference to vector of USBDevice objects
        USBEnumerator(USBContext& context, std::vector<USBDevice>& devices)
        {
            devices.clear();
            _devices = NULL;

            libusb_context* _usbcontext = context.getContext();
            int count = libusb_get_device_list(_usbcontext, &_devices);
            SPDLOG_TRACE("Found {} usb devices", count);
            for (int i = 0; i < count; i++) {
                devices.push_back(_devices[i]);
            }
        }

        //! \brief destructor
        ~USBEnumerator()
        {
            libusb_free_device_list(_devices, false);
        }

    private:
        libusb_device** _devices;
    };

}
}
