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
#include <libusb-1.0/libusb.h>
#include "usb/usb_config_descriptor.h"
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/spdlog.h"

namespace superflash {
namespace usb {

#define EP_IN	0x80

    //! \brief USB Device Object
    //!
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
                spdlog::error("failed to get device descriptor");
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

        int getVID() const
        {
            return _descriptor.idVendor;
        }

        int getPID() const
        {
            return _descriptor.idProduct;
        }

        struct libusb_device* getDevice() const { return _device; }

        libusb_device_handle* getHandle() const { return _handle; }

        void dump()
        {
            get_device_descriptor();
            USBConfigDescriptor dconfig(_device);

            SPDLOG_TRACE("{:04x}:{:04x} (bus {}, device {}) bNumInterfaces:{}",
                _descriptor.idVendor, _descriptor.idProduct,
                get_bus_number(), get_device_address(),
                dconfig.config->bNumInterfaces);

            for (int j = 0; j < dconfig.config->bNumInterfaces; j++) {
                const struct libusb_interface* inter = &dconfig.config->interface[j];
                SPDLOG_TRACE("  alternates:{}", inter->num_altsetting);
                for (int k = 0; k < inter->num_altsetting; k++) {
                    const struct libusb_interface_descriptor* interdesc = &inter->altsetting[k];
                    SPDLOG_TRACE("    Interface Number: {}, Number of endpoints: {}",
                        interdesc->bInterfaceNumber, interdesc->bNumEndpoints);
                    for (int l = 0; l < interdesc->bNumEndpoints; l++) {
                        const struct libusb_endpoint_descriptor* epdesc = &interdesc->endpoint[l];
                        SPDLOG_TRACE("      Descriptor Type: {:x}, EP Address: {}, wMaxPacketSize: {}",
                            epdesc->bDescriptorType, epdesc->bEndpointAddress, epdesc->wMaxPacketSize);
                    }
                }
            }
        }

        //! \brief Open USB device and claim interface
        //!
        //! \returns
        //! \retval false   error has occurred trying to open and claim the usb interface.
        //! \retval true    success.
        bool open_device()
        {
            SPDLOG_TRACE("Trying to open device.");
            int err;
            int config = 0;

            // retry up to 50 times and sleep 500ms in between retries.
            for (int retries = 0; retries < 50; retries++) {
                _handle = NULL;
                err = libusb_open(_device, &_handle);
                if (_handle)
                    break;

                usleep(500000);
            }

            if (!_handle) {
                spdlog::error("Could not open the device.");
                return false;
            }

            libusb_get_configuration(_handle, &config);
            SPDLOG_TRACE("bConfigurationValue = 0x{:x}", config);

            if (libusb_kernel_driver_active(_handle, 0)) {
                libusb_detach_kernel_driver(_handle, 0);
            }

            if (libusb_claim_interface(_handle, 0)) {
                spdlog::error("failed to claim interface.");
                return false;
            }

            SPDLOG_TRACE("interface 0 claimed.");

            return true;
        }

        //! \brief Close the USB device
        void close_device()
        {
            if (_handle)
            {
                libusb_release_interface(_handle, 0);
                libusb_close(_handle);
                _handle = NULL;
            }
            SPDLOG_TRACE("closed USB device.");
        }

        //! \brief Initiate bulk transfer
        //!
        //! Per imx_usb: 
        //!
        //!     For Bulk class drivers, the device is configured as
        //!     EP0IN, EP0OUT control transfer
        //!     EP1OUT - bulk out
        //!     (max packet size of 512 bytes)
        //!     EP2IN - bulk in
        //!     (max packet size of 512 bytes)
        //!
        //! \param report
        //! \param data
        //! \param length
        //! \param last
        //! 
        //! \returns
        //! \retval 0 on success (and populates transferred) 
        //! \retval LIBUSB_ERROR_TIMEOUT if the transfer timed out (and populates transferred) 
        //! \retval LIBUSB_ERROR_PIPE if the endpoint halted 
        //! \retval LIBUSB_ERROR_OVERFLOW if the device offered more data, see Packets and overflows 
        //! \retval LIBUSB_ERROR_NO_DEVICE if the device has been disconnected 
        //! \retval LIBUSB_ERROR_BUSY if called from event handling context 
        //! \retval LIBUSB_ERROR_INVALID_PARAM if the transfer size is larger than the operating system and/or hardware can support (see Transfer length limitations) 
        //!                                     another LIBUSB_ERROR code on other failures 
        int transfer_bulk(int report, uint8_t *data, unsigned int length, int *last)
        {
            const int timeout = 1000;
            int err;
            *last = 0;
            err = libusb_bulk_transfer(_handle,
                (report < 3) ? 1 : 2 + EP_IN, data, length, last, timeout);
        
            return err;
        }

        //! \brief HID transfer
        //!
        //! Per imx_usb:
        //!     For HID class drivers, 4 reports are used to implement
        //!     Serial Download protocol(SDP)
        //!     Report 1 (control out endpoint) 16 byte SDP comand
        //!     (total of 17 bytes with 1st byte report id of 0x01
        //!     Report 2 (control out endpoint) data associated with report 1 commands
        //!     (max size of 1025 with 1st byte of 0x02)
        //!     Report 3 (interrupt in endpoint) HAB security state
        //!     (max size of 5 bytes with 1st byte of 0x03)
        //!     (0x12343412 production)
        //!     (0x56787856 engineering)
        //!     Report 4 (interrupt in endpoint) date associated with report 1 commands
        //!     (max size of 65 bytes with 1st byte of 0x04)
        //!
        //! \param report
        //! \param data
        //! \param length
        //! \param last
        //! 
        int transfer_hid(int report, uint8_t *data, unsigned int length, int *last, bool use_ep1, int max_transfer)
        {
            const int timeout = 1000;
            int err;
            unsigned char tmp[1028];

            SPDLOG_TRACE("report={}, cnt={:x}", report, length);
            tmp[0] = (uint8_t)report;

            if (report < 3)
            {
                memcpy(&tmp[1], data, length);
                if (report == 2) {
                    length = max_transfer;
                }

                if (!use_ep1)
                {
                    err = libusb_control_transfer(_handle,
                        CTRL_OUT,
                        HID_SET_REPORT,
                        (HID_REPORT_TYPE_OUTPUT << 8) | report,
                        0,
                        tmp, length + 1, timeout);
                    *last = (err > 0) ? err - 1 : 0;       
                }
                else
                {
                    *last = 0;
                    err = libusb_interrupt_transfer(_handle, 1,
                        tmp, length + 1, last, timeout);
                    if (err < 0) {
                        spdlog::error("{}}: read error({}) cnt={}, last_trans={}, {:02x} {:02x} {:02x} {:02x}",
                            __func__, err,
                            length, *last, data[0], data[1], data[2], data[3]);
                    }
                    if (*last)
                        *last -= 1;
                    SPDLOG_TRACE("{}: last_trans={}\n", __func__, *last);
                }

                if (err > 0) err = 0;
            }
            else
            {
                // Report 4 - interrupt in endpoint
                *last = 0;
                memset(&tmp[1], 0, length);
                err = libusb_interrupt_transfer(_handle, 1 + EP_IN, tmp, length + 1, last, timeout);
		        SPDLOG_TRACE("libusb_interrupt_transfer, err={}, trans={}", err, *last);
                if (err >= 0)
                {
                    if (tmp[0] == (uint8_t) report) 
                    {
                        if (*last > 1) 
                        {
                            *last -= 1;
                            memcpy(data, &tmp[1], *last);
                        }
                    }
                    else
                    {
                        spdlog::warn("Unexpected report {} err={}, cnt={}, last_trans={}, {:02x} {:02x} {:02x} {:%02x}",
                        tmp[0], err, length, *last, tmp[0], tmp[1], tmp[2], tmp[3]);
                        err = 0;
                    }
                }

            }
            return err;
        }

    private:
        libusb_device_handle* _handle = NULL;
        struct libusb_device* _device = NULL;
        struct libusb_device_descriptor _descriptor;
    };

}
}
