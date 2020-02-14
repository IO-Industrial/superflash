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
#ifdef __linux__ 
#include <scsi/sg_lib.h>
#include <scsi/sg_io_linux.h>
#endif

//! \brief Transport Device base class
class TransportDevice
{
public:

    virtual int Open(std::string &filename);
    void Close();
    virtual ~TransportDevice() {};

private:
    std::string _device_filename;
    int _device_fd;
};

class SerialTransportDevice : public TransportDevice
{

};

#ifdef __linux__ 
//! \brief SCSI Generic I/O transport
//!
//! Access the device through the linux SCSI Generic 
//! driver.
//!
//! Compatibility note: Mac OS X does not allow applications to send 
//! SCSI or ATA commands to storage devices unless the application 
//! developer also provides an in-kernel device driver that supports 
//! the commands. The SCSI Architecture Model family allows only one 
//! logical unit driver to control a device at a time and provides 
//! in-kernel logical unit drivers for storage devices (as listed in 
//! “SCSI Architecture Model Family Device Support”). Similarly, 
//! the ATA family does not allow applications to send ATA commands 
//! directly to ATA or SATA (Serial ATA) devices.
class SCSIGenericTransportDevice : public TransportDevice
{
public:

private:
    struct sg_io_hdr sgio_hdr;
};
#endif