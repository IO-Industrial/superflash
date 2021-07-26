/*
 * \file imx_hab.h
 *
 * High Assurance Boot (HAB)
 *
 * \copyright  Copyright (C) 2021  Joe Turner <joe@agavemountain.com>
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
#ifndef _IMX_HAB_H_
#define _IMX_HAB_H_

//! \brief High Assurance Boot (HAB)
//!
//! The HAB library is a sub-component of the boot ROM on i.MX processors. 
//! It is responsible for verifying the digital signatures included as 
//! part of the product software and ensures that, when the processor is 
//! configured as a secure device, no unauthenticated code is allowed to run.
//!
//!  The HAB library can not only be used to authenticate the first stage 
//! of the boot chain, but the other components of the boot chain as well 
//! such as the Linux kernel.
enum eHAB
{
    HAB_UNKNOWN = -1,
    HAB_ENABLED = 0x12343412,
    HAB_DISABLED = 0x56787856
};

#endif