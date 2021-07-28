/*
 * \file usb_handle.h
 *
 * USB device handle class
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
#include <libusb-1.0/libusb.h>
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/spdlog.h"

namespace superflash
{
    namespace usb
    {

        //! \brief USB Device Handle
        //!
        //! A "handle" is a generic identifier for an arbitrary device or piece of information.
        //! In the case of USB, a "USB handle" is an identifier for a USB device.
        //! It is passed to further USB API functions in order to interact with
        //! the USB device.
        //!
        //! This class wraps a USB handle, a device handle is used to perform I/O and other
        //! operations. When finished with a device handle, you should call libusb_close().
        class USBDeviceHandle
        {

        public:
            USBDeviceHandle() : _handle(NULL)
            {
            }

            libusb_device_handle *getHandle() const
            {
                return _handle;
            }

            void set_handle(libusb_device_handle *handle)
            {
                _handle = handle;
            }

            void close_handle()
            {
                libusb_close(_handle);
                _handle = NULL;
            }

            void close_and_release()
            {
                if (_handle)
                {
                    SPDLOG_TRACE("releasing interface");
                    release_interface(0);
                    close_handle();
                    _handle = NULL;
                }
            }

            //! \brief Claim USB interface
            //!
            //! Claim an interface on a given device handle. You must claim
            //! the interface you wish to use before you can perform I/O
            //! on any of its endpoints.
            //!
            //! It is legal to attempt to claim an already-claimed interface. This
            //! function does not cause any requests to be sent over the bus.
            //!
            //! \returns
            //! \retval false   and error has occurred
            //! \retval true    success
            bool claim_interface(int interface);

            //! \brief Release a USB interface
            //!
            //! Release an interface previously claimed by claim_interface.
            //! You should release all claimed interfaces before closing a
            //! device handle.
            //!
            //! A SET_INTERFACE control request will be sent to the device.
            //!
            //! \returns
            //! \retval false   and error has occurred
            //! \retval true    success
            bool release_interface(int interface);

            bool is_driver_active(int interface);
            bool detach_driver(int interface);

            //! \brief Perform USB reset to reinitialize a device
            //!
            //! The system will attempt to restore the previous configuration
            //! and alternate settings after the reset has completed.
            //!
            //! If the reset fails, the descriptors change, or the previous state
            //! cannot be restored, the device will appear to be disconnected
            //! and reconnected. This means that the device handle is no
            //! longer valid (you should close it) and rediscover the device.
            //!
            //! This is a blocking function which usually incurs a noticeable delay.
            bool reset_device();
            bool clear_halt();
            bool set_configuration(int configuration);
            bool get_configuration(int *configuration);
            libusb_device *get_device();

            ////////////////////////////////////////////////////////////////////////////
            // Synchronous I/O

            //! \brief Perform an USB control transfer
            //!
            //! Control Transfers are bi-directional transfers reserved for the host
            //! to send and request configuration information to and from the
            //! device using the IN and OUT Endpoint 0.
            //!
            //! Each Control Transfer consists of 2 to several transactions. The
            //! maximum packet size for the control endpoint data is:
            //!
            //! - 8 bytes for low-speed
            //! - 8, 16, 32, or 64 bytes for full-speed
            //! - 64 bytes for high-speed
            //!
            //! \returns
            //! On success, returns the number of bytes transferred.
            //!
            int control_transfer(uint8_t request_type, uint8_t request, uint16_t value, uint16_t index,
                                 uint8_t *data, uint16_t length, unsigned int timeout);

            //! \brief Perform a bulk transfer
            //!
            //!
            //! \returns
            //! This function returns 0 for success, an error for any other value.
            int bulk_transfer(uint8_t endpoint, uint8_t *data, int length, int *transferred, unsigned int timeout);

            //! \brief Perform a USB interrupt transfer.
            //!
            //! Interrupt Transfers have a limited latency to or from a device. In USB,
            //! an Interrupt Transfer, or Interrupt Pipe, has a defined polling rate
            //! between:
            //!
            //! - 1ms and 255ms for full and low-speed
            //! - 125μs to 4096ms for high-speed endpoints.
            //!
            //! The maximum packet size for the interrupt endpoint data is:
            //!
            //! - 64 or less bytes for full-speed
            //! - 1024 or less bytes for high-speed
            //!
            //! \param endpoint the address of a valid endpoint to communicate with
            //! \param data  pointer to data buffer for either input/output (depending on endpoint)
            //! \param length
            //!         For bulk reads, the maximum number of bytes to receive into the receive buffer;
            //!         for bulk writes, the number of bytes from data to be sent.
            //! \param transferred  output location for the number of bytes actually transferred.
            //! \param timeout  timeout in milliseconds. 0 = unlimited.
            //!
            //! \returns
            //! This function returns 0 for success, an error for any other value.
            int interrupt_transfer(uint8_t endpoint, uint8_t *data, int length, int *transferred, unsigned int timeout);

            int HID_read(void *buff, size_t size, size_t *return_size);
            int HID_write(void *buff, size_t size, int out_endpoint);
            int HID_write(void *buff, size_t size);

        private:
            libusb_device_handle *_handle;
            unsigned int _timeout;
        };

    } // usb
} // superflash
