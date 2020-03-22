/*
 * \file usb_bus.h
 *
 * USB device class
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
#include <iostream>

class USBConfigDescriptor
{
public:
    struct libusb_config_descriptor *config;

    USBConfigDescriptor(libusb_device *device)
    {
        libusb_get_config_descriptor(device, 0, &config);
    }

    ~USBConfigDescriptor(){
        libusb_free_config_descriptor(config);
    }

};

class USBDevice
{

public:

    USBDevice(libusb_device *device) : _device(device) {}

    //! \brief Get the number of the bus that a device is connected to.
    //! 
    //! \returns
    //! This function returns the bus number.
    int get_bus_number() {
        return libusb_get_bus_number(_device);
    }

    //! \brief Get the address of the device on the bus it is connected to.
    //!
    //! \returns
    //! This function returns the device address
    int get_device_address() {
        return libusb_get_device_address(_device);
    }

    void increment_reference()
    {
        libusb_ref_device(_device);
    }

    void decrement_reference()
    {
        libusb_unref_device(_device);
    }

    int get_device_descriptor()
    {
        int rc = libusb_get_device_descriptor(_device, &_descriptor);
        if (rc < 0)
        {
            std::cerr << "failed to get device descriptor\n";
        }
        return rc;
    }

    bool is_VID_PID(uint16_t vendor_id, uint16_t product_id) {
        bool ret = false;
        if (!get_device_descriptor() &&
            _descriptor.idVendor == vendor_id &&
            _descriptor.idProduct == product_id)
            {
                ret = true;
            }
        
        return ret;
    }
    struct libusb_device *getDevice() const { return _device; }

    void dump()
    {
        get_device_descriptor();
        USBConfigDescriptor dconfig(_device);
        printf("%04x:%04x (bus %d, device %d) bNumInterfaces:%i\n",
			_descriptor.idVendor, _descriptor.idProduct,
			get_bus_number(), get_device_address(),
			dconfig.config->bNumInterfaces);
    }

//     void USB::print_devices(libusb_device **devices)
// {
//     int i=0;
//     libusb_device *device = devices[i];
//     struct libusb_config_descriptor *config;
//     struct libusb_device_descriptor descriptor;

//     while (device)
//     {
//         device = devices[i++];
//         if(!device) break;

//         if (libusb_get_device_descriptor(device, &descriptor) < 0)
//         {
//             cerr << "failed to get device descriptor\n";
//             return;
//         }

//         libusb_get_config_descriptor(device, 0, &config);
//         printf("%04x:%04x (bus %d, device %d) bNumInterfaces:%i\n",
// 			descriptor.idVendor, descriptor.idProduct,
// 			libusb_get_bus_number(device), libusb_get_device_address(device),
// 			config->bNumInterfaces);
// 		for (int j = 0; j < config->bNumInterfaces; j++) {
// 			const struct libusb_interface *inter = &config->interface[j];
// 			printf("  alternates:%i\n", inter->num_altsetting);
// 			for (int k = 0; k < inter->num_altsetting; k++) {
// 				const struct libusb_interface_descriptor *interdesc = &inter->altsetting[k];
// 				printf("    Interface Number: %i, Number of endpoints: %i\n",
// 						interdesc->bInterfaceNumber, interdesc->bNumEndpoints);
// 				for (int l = 0; l < interdesc->bNumEndpoints; l++) {
// 					const struct libusb_endpoint_descriptor *epdesc = &interdesc->endpoint[l];
// 					printf("      Descriptor Type: %x, EP Address: %i, wMaxPacketSize: %i\n",
// 							epdesc->bDescriptorType, epdesc->bEndpointAddress, epdesc->wMaxPacketSize);
// 				}
// 			}
// 		}
// 		libusb_free_config_descriptor(config);
//     }


private:

	libusb_device_handle *handle_;
    struct libusb_device *_device = NULL;
    struct libusb_device_descriptor _descriptor;
};

