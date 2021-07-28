/*
 * \file usb_devices.cpp
 *
 * USB device definitions
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
#include "usb/usb_devices.h"
#include <cstddef>

namespace
{
    const uint32_t FREESCALE_PID = 0x15A2;
    const uint32_t SIGMATEL_PID = 0x066F;
    const uint32_t NXP_PID = 0x1fc9;
    const uint32_t BOUNDARY_DEVICES_PID = 0x3016;
    const uint32_t NETCHIP_TECH_PID = 0x0525;

    const char *IMX_6_STR = "imx.6";
}

namespace superflash
{
    namespace usb
    {

        // 15a2   Freescale Semiconductor, Inc.
        // 	0038  9S08JS Bootloader
        // 	003b  USB2CAN Application for ColdFire DEMOJM board
        // 	0042  OSBDM - Debug Port
        // 	004f  i.MX28 SystemOnChip in RecoveryMode
        // 	0052  i.MX50 SystemOnChip in RecoveryMode
        // 	0054  i.MX 6Dual/6Quad SystemOnChip in RecoveryMode
        // 	0061  i.MX 6Solo/6DualLite SystemOnChip in RecoveryMode

        struct sf_usb_device sf_usb_devices[] = {

            {.vid = FREESCALE_PID,
             .pid = 0x006a,
             .march_description = "Vybrid VFxxx SoC",
             .usb_hint = USB_HID,
             .max_transfer = 1024,
             .dcd_addr = 0x3f400000,
             .ram_start = 0x10000000},

        ///////////////////////////////////////////////////////////////////
        // untested below
#if 0
        // Sigmatel
        {
            .vid = SIGMATEL_PID,
            .pid = 0x3780,
            .march_description = "i.MX53 Arm Cortex A9, 256KB memory", 
            .usb_hint = USB_UNDEFINED
        },
        // Freescale Semiconductor
        {
            .vid = FREESCALE_PID,
            .pid = 0x0038,
            .march_description = "9S08JS Bootloader",
            .usb_hint = USB_UNDEFINED
        },
        { 
            .vid = FREESCALE_PID,
            .pid = 0x003b,
            .march_description = "9USB2CAN Application for ColdFire DEMOJM board",
            .usb_hint = USB_UNDEFINED
        },
        { 
            .vid = FREESCALE_PID,
            .pid = 0x0042,
            .march_description = "OSBDM - Debug Port",
            .usb_hint = USB_UNDEFINED
        },        
        {
            .vid = FREESCALE_PID,
            .pid = 0x004f,
            .march_description = "i.MX28 454MHz Arm926EJ-S 16KB/32KB Cache",
            .usb_hint = USB_UNDEFINED
             },
        { .vid = FREESCALE_PID,
            .pid = 0x0052,
            .march_description = "i.MX50 800MHz Arm Cortex A9" },
        { .vid = FREESCALE_PID,
            .pid = 0x0041,
            .march_description = "i.MX51 Arm Cortex A9" },
        { .vid = FREESCALE_PID,
            .pid = 0x004e,
            .march_description = "i.MX53 Arm Cortex A9" },


        { .vid = FREESCALE_PID,
            .pid = 0x0054,
            .march_description = IMX_6_STR },
        { .vid = FREESCALE_PID,
            .pid = 0x0061,
            .march_description = IMX_6_STR },
        { .vid = FREESCALE_PID,
            .pid = 0x006a,
            .march_description = IMX_6_STR },
        { .vid = FREESCALE_PID,
            .pid = 0x0071,
            .march_description = IMX_6_STR },
        { .vid = FREESCALE_PID,
            .pid = 0x007d,
            .march_description = IMX_6_STR },
        { .vid = FREESCALE_PID,
            .pid = 0x0080,
            .march_description = IMX_6_STR },
        { .vid = FREESCALE_PID,
            .pid = 0x0077,
            .march_description = "iMX 7" },
        { .vid = FREESCALE_PID,
            .pid = 0x012b,
            .march_description = "iMX8mq" },
        { .vid = FREESCALE_PID,
            .pid = 0x0134,
            .march_description = "iMX8mm" },
        { .vid = FREESCALE_PID,
            .pid = 0x013e,
            .march_description = "iMX8mn" },

        // Boundry Devices
        {
            .vid = BOUNDARY_DEVICES_PID,
            .pid = 0x1000,
            .march_description = "imx.8" },
        { .vid = BOUNDARY_DEVICES_PID,
            .pid = 0x1001,
            .march_description = IMX_6_STR },
        { .vid = BOUNDARY_DEVICES_PID,
            .pid = 0x1002,
            .march_description = IMX_6_STR },

        // Netchip Technology, Inc.
        {
            .vid = BOUNDARY_DEVICES_PID,
            .pid = 0xb4a4,
            .march_description = IMX_6_STR },
        { .vid = 0x1b67,
            .pid = 0x4ff,
            .march_description = IMX_6_STR },
        // NXP
        {
            .vid = NXP_PID,
            .pid = 0x0128,
            .march_description = IMX_6_STR },
        { .vid = NXP_PID,
            .pid = 0x0126,
            .march_description = "iMX7" },
#endif
            // Sentinel
            {
                .vid = 0,
                .pid = 0,
                .march_description = "",
            }};

        struct sf_usb_device *find(uint32_t vid, uint32_t pid)
        {
            struct sf_usb_device *ptr = NULL;

            for (int i = 0; (sf_usb_devices[i].vid > 0); i++)
            {
                if ((vid == sf_usb_devices[i].vid) && (pid == sf_usb_devices[i].pid))
                {
                    return &sf_usb_devices[i];
                }
            }

            return ptr;
        }

        struct sf_usb_device *usb_is_valid_device(USBDevice &dev)
        {
            struct sf_usb_device *ptr = NULL;

            for (int i = 0; (sf_usb_devices[i].vid > 0); i++)
            {
                if (dev.is_VID_PID(sf_usb_devices[i].vid, sf_usb_devices[i].pid))
                {
                    return &sf_usb_devices[i];
                }
            }

            return ptr;
        }

    }
}