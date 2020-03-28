/*
 * \file usb_context.h
 *
 * USB context class
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

    //! \brief USB Context class
    //!
    //! This class wraps a libusbcontext pointer.  This pointer is a concept of 
    //! libusb, created when the library is initialized. 
    //!
    //! Since it is possible that libusb may be used simultaneously from two independent
    //! libraries linked into the same executable, this is used by libusb to make 
    //! sure that there aren't any collisions. 
    //!
    //! This pointer and any allocated memory are owned by libusb.  Contexts are
    //! destroyed during libusb_exit.
    //!
    //! Note: this concept was added in libusb 1.0; it does not exist in libusb
    class USBContext {
    public:

        //! \brief Default constructor
        USBContext()
            : _usbcontext(NULL)
        {
        }

        //! \brief Specialized constructor
        //!
        //! \param  ctx  - pointer to libusb usbcontext 
        //!
        USBContext(libusb_context* ctx)
        {
            _usbcontext = ctx;
        }

        //! \brief Set current USB context
        //!
        //! \retval libusb_context pointer
        void setContext(libusb_context* ctx)
        {
            _usbcontext = ctx;
        }

        //! \brief Get current USB context
        //!
        //! \retval libusb_context pointer
        libusb_context* getContext() const { return _usbcontext; }

    private:
        libusb_context* _usbcontext;
    };

}
}
