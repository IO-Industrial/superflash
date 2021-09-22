/*
 * \file transport.h
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
#include <string>

//! \brief Transport Device base class
class TransportDevice {
public:
    //! \brief Default constructor
    TransportDevice()
        : _device_fd(-1)
    {
    }
    TransportDevice(std::string& filename)
        : _device_filename(filename)
        , _device_fd(-1)
    {
    }
    TransportDevice(const char* filename)
        : _device_filename(filename)
        , _device_fd(-1)
    {
    }
    TransportDevice(char* filename)
        : _device_filename(filename)
        , _device_fd(-1)
    {
    }

    virtual int Open();
    virtual void Close();

    virtual ~TransportDevice() {};

protected:
    std::string _device_filename;
    int _device_fd;
};
