/*
 * \file usb_bus.h
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
#include <iostream>

#include "usb/usb_config_descriptor.h"
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"

namespace superflash {
namespace usb {

    class USBDevice {

    public:
        USBDevice(libusb_device* device)
            : _device(device)
        {
        }

        //! \brief Get the number of the bus that a device is connected to.
        //!
        //! \returns
        //! This function returns the bus number.
        int get_bus_number()
        {
            return libusb_get_bus_number(_device);
        }

        //! \brief Get the address of the device on the bus it is connected to.
        //!
        //! \returns
        //! This function returns the device address
        int get_device_address()
        {
            return libusb_get_device_address(_device);
        }

        void increment_reference()
        {
            libusb_ref_device(_device);
        }

        void decrement_reference()
        {
            libusb_unref_device(_device);
        }

        int get_device_descriptor()
        {
            int rc = libusb_get_device_descriptor(_device, &_descriptor);
            if (rc < 0) {
                std::cerr << "failed to get device descriptor\n";
            }
            return rc;
        }

        bool is_VID_PID(uint16_t vendor_id, uint16_t product_id)
        {
            bool ret = false;
            if (!get_device_descriptor() && _descriptor.idVendor == vendor_id && _descriptor.idProduct == product_id) {
                ret = true;
            }

            return ret;
        }
        struct libusb_device* getDevice() const { return _device; }

        void dump()
        {
            get_device_descriptor();
            USBConfigDescriptor dconfig(_device);
            
            SPDLOG_TRACE("{:04x}:{:04x} (bus {}, device {}) bNumInterfaces:{}", 
                _descriptor.idVendor, _descriptor.idProduct,
                get_bus_number(), get_device_address(),
                dconfig.config->bNumInterfaces);           

            for (int j = 0; j < dconfig.config->bNumInterfaces; j++) {
                const struct libusb_interface *inter = &dconfig.config->interface[j];
                SPDLOG_TRACE("  alternates:{}", inter->num_altsetting);
                for (int k = 0; k < inter->num_altsetting; k++) {
                    const struct libusb_interface_descriptor *interdesc = &inter->altsetting[k];
                    SPDLOG_TRACE("    Interface Number: {}, Number of endpoints: {}",
                        interdesc->bInterfaceNumber, interdesc->bNumEndpoints
                    );
                    for (int l = 0; l < interdesc->bNumEndpoints; l++) {
                        const struct libusb_endpoint_descriptor *epdesc = &interdesc->endpoint[l];
                        SPDLOG_TRACE("      Descriptor Type: {:x}, EP Address: {}, wMaxPacketSize: {}",
                                epdesc->bDescriptorType, epdesc->bEndpointAddress, epdesc->wMaxPacketSize);
                    }
                }
            }
        }

    private:
        libusb_device_handle* handle_;
        struct libusb_device* _device = NULL;
        struct libusb_device_descriptor _descriptor;
    };

}
}
