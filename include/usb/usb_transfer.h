/*
 * \file usb_transfer.h
 *
 * USB device transfer classes
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
#ifndef _USB_TRANSFER_H_
#define _USB_TRANSFER_H_
#include <stdint.h>

namespace superflash
{
    namespace usb
    {

        //! \brief USB Transaction structure
        //!
        //! This structure contains the data fields that are used by
        //! the different types of USB transfers.
        //!
        struct USBTransaction
        {
            uint8_t *data;        //!< pointer to buffer
            int length;           //!< size of buffer, or size of data.
            int transferred;      //!< transferred bytes
            unsigned int timeout; //!< timeout in ms
        };

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
        struct USBInterruptTransfer : USBTransaction
        {
            uint8_t endpoint;
        };

    }
}

#endif