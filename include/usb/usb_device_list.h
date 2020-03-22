/*
 * \file usb_bus.h
 *
 * USB bus class
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
#include "usb/usb_device.h"


//! \brief USB device enumerator / device list
//!
//! This class will get a list of USB devices, and populate the given
//! vector (convert the fixed array of pointers into an STL vector),
//! with the device pointers.
//!
//! The destructor will free the device list, guaranteeing
//! that it gets released.
class USBEnumerator
{
public:
    USBEnumerator(std::shared_ptr<libusb_context> context, std::vector<USBDevice> &devices)
    {
        devices.clear();
        int count = libusb_get_device_list(context.get(), &_devices);

        for (int i=0; i< count; i++)
        {
            devices.push_back(_devices[i]);
        }
    }

    ~USBEnumerator()
    {
        libusb_free_device_list(_devices, false);
    }

private:
    libusb_device **_devices;
};


