/*
 * \file transport.cpp
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
#include "transport/transport.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int TransportDevice::Open()
{
    if (_device_fd >= 0) {
        // device is already open.  
        Close();
    }

    // Open device
	_device_fd = open(_device_filename.c_str(), O_RDONLY);
	if (_device_fd < 0)
	{
		std::cerr << "Error opening device: " << _device_filename << "\n";
	}
    return _device_fd;
}

void TransportDevice::Close()
{
    if (_device_fd < 0)
    {
        return;
    }
    close(_device_fd);
}

