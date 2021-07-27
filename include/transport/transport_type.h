/*
 * \file transport_type.h
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
#ifndef _TRANSPORT_TYPE_H_
#define _TRANSPORT_TYPE_H_


//! \brief Transport Type
//!
//! This enumeration contains the transport type, which gives us a 
//! hint as to how to program the device (USB, serial, can, ethernet, etc.)
enum TRANS_TYPE {
    
    TRANS_UNKNOWN,  //!< unknown transfer type
    TRANS_USB_HID,  //!< USB Human Interface Device (HID)
    TRANS_USB_BULK  //!< USB Bulk transfer
};

#endif