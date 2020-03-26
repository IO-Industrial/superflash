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
#include "usb/usb_defs.h"
#include "usb/usb_context.h"
#include "usb/usb_device.h"
#include "usb/usb_device_list.h"
#include "errors.h"

//! \brief USB subsystem class
//!
//! This non-copyable class wraps the libUSB API.  
//!
class USB
{

public:
   
    USB() : _usbcontext(NULL) {}

    //! \brief Initialize libusb.
    //! This function must be called before calling any other libusb function.
    int initialize()
    {
        if (_usbcontext != NULL) return 0;    // already initialized.

        _usbcontext = NULL;
        int rc = libusb_init(&_usbcontext);
        if (rc != LIBUSB_SUCCESS) {
            SF_ERROR(SF_ERR_USB_INIT);
        } 
        //_context_ptr = std::shared_ptr<libusb_context>(ctx);
        return rc;
    }

    //! \brief 
    void deinitialize()
    {
        libusb_exit(NULL);
    }

    std::vector<USBDevice> get_device_list()
    {
        _device_list.clear();
        USBEnumerator enumerator(_context_ptr, _device_list);
        return _device_list;
    }

    bool search_by_vid_pid(uint16_t vendor_id, uint16_t product_id)
    {
        std::vector<USBDevice> list = get_device_list();
        for (int i=0;i<list.size();i++)
        {
            if (list[i].is_VID_PID(vendor_id, product_id)) {
                list[i].dump();
                return true;
            }
        }
        return false;
    }

private:
    USB( const USB& ) = delete; // non construction-copyable
    USB& operator=( const USB& ) = delete; // non copyable

    std::vector<USBDevice> _device_list;

    struct libusb_device *device = NULL;

    libusb_device **_devices;
    int _device_count;
    libusb_context *_usbcontext = NULL;
    
    std::shared_ptr<USBDevice> _usb_device;
    std::shared_ptr<libusb_context> _context_ptr;
};

