/*
 * \file usb_handle.cpp
 *
 * USB device handle
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
#include "usb/usb_handle.h"
#include "usb/usb_defs.h"
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/spdlog.h"

namespace superflash
{
    namespace usb
    {

        bool USBDeviceHandle::claim_interface(int interface)
        {
            if (libusb_claim_interface(_handle, 0))
            {
                spdlog::error("failed to claim interface.");
                return false;
            }
            return true;
        }

            bool USBDeviceHandle::set_configuration(int configuration)
            {
                return (libusb_set_configuration(_handle, configuration));
            }
            bool USBDeviceHandle::get_configuration(int *configuration)
            {
                return (libusb_get_configuration(_handle, configuration) == 0);
            }

        bool USBDeviceHandle::release_interface(int interface)
        {
            return false;
        }

        bool USBDeviceHandle::is_driver_active(int interface)
        {
            return (libusb_kernel_driver_active(_handle, interface) == 1);
        }

        bool USBDeviceHandle::detach_driver(int interface)
        {
            return (libusb_detach_kernel_driver(_handle, interface));
        }
        bool USBDeviceHandle::reset_device()
        {
            return (libusb_reset_device(_handle) == 0);
        }

        int USBDeviceHandle::HID_read(void *buff, size_t size, size_t *return_size)
        {
            int ret;
            int actual;
            const uint8_t ep_in = 0x81;

            ret = interrupt_transfer(
                ep_in,
                (uint8_t *)buff,
                size,
                &actual,
                _timeout);

            *return_size = actual;

            if (ret < 0)
            {
                spdlog::error("HID(Read): {}", libusb_error_name(ret));
                return ret;
            }
            return 0;
        }

        int USBDeviceHandle::HID_write(void *buff, size_t size, int out_endpoint)
        {
            int ret;
            uint8_t *p = (uint8_t *)buff;
            int actual_size;

            ret = interrupt_transfer(
                out_endpoint,
                p,
                size,
                &actual_size,
                1000);

            if (ret < 0)
            {
                spdlog::error("HID(Write): {}", libusb_error_name(ret));
                return ret;
            }
            return 0;
        }

        int USBDeviceHandle::HID_write(void *buff, size_t size)
        {
            int ret;
            uint8_t *p = (uint8_t *)buff;
            int actual_size;
            const int report = 9;
            ret = control_transfer(
                LIBUSB_ENDPOINT_OUT | LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_INTERFACE,
                HID_SET_REPORT,
                (HID_REPORT_TYPE_OUTPUT << 8) | p[0],
                0,
                p,
                size,
                1000);

            if (ret < 0)
            {
                spdlog::error("HID(Write): {}", libusb_error_name(ret));
                return ret;
            }
            return 0;
        }

        int USBDeviceHandle::control_transfer(uint8_t request_type, uint8_t request, uint16_t value, uint16_t index,
                             uint8_t *data, uint16_t length, unsigned int timeout)
        {
            return libusb_control_transfer(_handle, request_type, request, value, index,
                             data, length, timeout);
        }

        int USBDeviceHandle::interrupt_transfer(uint8_t endpoint, uint8_t *data, int length, int *transferred, unsigned int timeout)
        {
            return libusb_interrupt_transfer(_handle, endpoint, data, length, transferred, timeout );
        }
    } // usb
} // superflash