/*
 * \file USBAdapter.h
 *
 * libusb wrapper class.
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
#include <libusb.h>

class USB {

public:

    //! \brief Initialize libusb.
    //! This function must be called before calling any other libusb function.
    int init();

    //! \brief Deinitialize libusb. 
    //! Should be called after closing all open devices and before your application terminates. 
    void release();

    void print_devices(libusb_device **devices);

    bool enumerate_devices();

    //virtual bool OnEnumeratedDevice();
};
