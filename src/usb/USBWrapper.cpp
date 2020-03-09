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
#include <iostream>
#include <stdio.h>
#include "usb/USBWrapper.h"

using namespace std;

int USB::init()
{
    return libusb_init(NULL);
}

void USB::release()
{
    libusb_exit(NULL);
}

void USB::print_devices(libusb_device **devices)
{
    int i=0;
    libusb_device *device = devices[i];
    struct libusb_config_descriptor *config;
    struct libusb_device_descriptor descriptor;

    while (device)
    {
        device = devices[i++];
        if(!device) break;

        if (libusb_get_device_descriptor(device, &descriptor) < 0)
        {
            cerr << "failed to get device descriptor\n";
            return;
        }

        libusb_get_config_descriptor(device, 0, &config);
        printf("%04x:%04x (bus %d, device %d) bNumInterfaces:%i\n",
			descriptor.idVendor, descriptor.idProduct,
			libusb_get_bus_number(device), libusb_get_device_address(device),
			config->bNumInterfaces);
		for (int j = 0; j < config->bNumInterfaces; j++) {
			const struct libusb_interface *inter = &config->interface[j];
			printf("  alternates:%i\n", inter->num_altsetting);
			for (int k = 0; k < inter->num_altsetting; k++) {
				const struct libusb_interface_descriptor *interdesc = &inter->altsetting[k];
				printf("    Interface Number: %i, Number of endpoints: %i\n",
						interdesc->bInterfaceNumber, interdesc->bNumEndpoints);
				for (int l = 0; l < interdesc->bNumEndpoints; l++) {
					const struct libusb_endpoint_descriptor *epdesc = &interdesc->endpoint[l];
					printf("      Descriptor Type: %x, EP Address: %i, wMaxPacketSize: %i\n",
							epdesc->bDescriptorType, epdesc->bEndpointAddress, epdesc->wMaxPacketSize);
				}
			}
		}
		libusb_free_config_descriptor(config);
    }


}

bool USB::enumerate_devices()
{
    libusb_device **devices;
    int count = libusb_get_device_list(NULL, &devices);
    if (count < 0)
    {
        cerr << "No USB devices found.\n";
        return false;
    }

    print_devices(devices);
    libusb_free_device_list(devices, 1);
    return true;
}
