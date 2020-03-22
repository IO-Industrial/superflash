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
#include "usb/usb_defs.h"

//! \brief USB Context class
//!
//! It is possible that libusb may be used simultaneously from two independent 
//! libraries linked into the same executable. For example, if your application 
//! has a plugin-like system which allows the user to dynamically load a range 
//! of modules into your program, it is feasible that two independently 
//! developed modules may both use libusb.
//!
//! This is made possible through libusb's context concept. When you call 
//! ibusb_init(), you are (optionally) given a context. You can then pass this 
//! context pointer back into future libusb functions.
//!
//! In order to keep things simple for more simplistic applications, it is 
//! legal to pass NULL to all functions requiring a context pointer (as long 
//! as you're sure no other code will attempt to use libusb from the same process). 
//! When you pass NULL, the default context will be used. The default context 
//! is created the first time a process calls libusb_init() when no other 
//! context is alive. Contexts are destroyed during libusb_exit().
//!
//! Note: this concept was added in libusb 1.0; it does not exist in libusb
class USBContext
{
public:

    USBContext() : _usbcontext(NULL) {}
    USBContext(libusb_context *usbcontext) {
        _usbcontext = usbcontext;
    }

    libusb_context * getContext() { return _usbcontext; }

private:

    libusb_context *_usbcontext;

};
