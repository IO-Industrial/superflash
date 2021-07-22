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
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/spdlog.h"

#include "errors.h"
#include "usb/usb_context.h"
#include "usb/usb_defs.h"
#include "usb/usb_device.h"
#include "usb/usb_enumerator.h"
#include <memory>
#include <vector>

namespace superflash {

/**
 * \defgroup usb USB classes
 * @brief Classes for discovering, enumerating and communicating with USB devices
 *
 * \todo add documentation.
 */

/** 
 * \brief usb namespace
 * 
 * This namespace contains code to discover, enumerate, and communicate with 
 * USB devices.
 * 
 * \ingroup usb
 */
namespace usb {

    //! \brief USB subsystem class
    //!
    //! This non-copyable class wraps the libUSB API.
    //!
    class USB {

    public:
        //! \brief Default constructor
        USB()
        {
        }

        //! \brief Initialize libusb.
        //! This function must be called before calling any other libusb function.
        int initialize()
        {
            if (_usbctx.getContext() != NULL) {
                spdlog::warn("libusb context already initialized.");
                return 0;
            }

            libusb_context* ctx = NULL;
            int rc = libusb_init(&ctx);
            if (rc != LIBUSB_SUCCESS) {
                SF_ERROR(SF_ERR_USB_INIT);
                spdlog::error(libusb_strerror(static_cast<enum libusb_error>(rc)));
            }
            _usbctx.setContext(ctx);

            return rc;
        }

        //! \brief
        void deinitialize()
        {
            libusb_exit(NULL);
        }

        std::vector<USBDevice> get_device_list()
        {
            _device_list.clear();
            USBEnumerator enumerator(_usbctx, _device_list);
            return _device_list;
        }

        bool search_by_vid_pid(uint16_t vendor_id, uint16_t product_id)
        {
            std::vector<USBDevice> list = get_device_list();
            for (int i = 0; i < list.size(); i++) {
                if (list[i].is_VID_PID(vendor_id, product_id)) {
                    list[i].dump();
                    return true;
                }
            }
            return false;
        }

    private:
        USB(const USB&) = delete; // non construction-copyable
        USB& operator=(const USB&) = delete; // non copyable

        std::vector<USBDevice> _device_list;

        struct libusb_device* device = NULL;

        libusb_device** _devices;
        int _device_count;
        //libusb_context* _usbcontext = NULL;

        std::shared_ptr<USBDevice> _usb_device;
        USBContext _usbctx;
    };

}
/*! @} End of Doxygen Groups*/
}
