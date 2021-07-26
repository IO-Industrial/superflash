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
#ifndef __SG_TRANSPORT_H_
#include "protocols/utp.h"
#include "transport/transport.h"

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
class SCSIGenericTransportDevice : public TransportDevice {
public:
    SCSIGenericTransportDevice(std::string& filename)
    {
        _device_filename = filename;
        _device_fd = -1;
    }

    //! \brief Send a UTP message via SCSI generic interface to the device
    //!
    //! \param header       pointer to the utp command structure
    //! \param dxferp       pointer to data
    //! \param dxferp_len   length of data
    //! \param reply        result of the UTP transaction as sense reply
    int send(struct UTP_CDB* message, void* dxferp, int dxferp_len, struct UTP_SCSI_SENSE_REPLY_HEADER& reply);

    //! \brief Send a command to via the SCSI generic interface to the device
    //!
    //! \param header       pointer to the utp command structure
    //! \param hdrsize      length of the utp command structure buffer
    //! \param dxferp       pointer to data
    //! \param dxferp_len   lenght of data
    //! \param reply_code   result of the UTP transaction
    //!
    //! \returns
    //! Usually, on success zero is returned.  On error, -1 is returned, and
    //! errno is set appropriately.
    int send_sg(uint8_t* header, int hdrsize, void* dxferp, int dxferp_len, uint8_t* reply_code);

private:
};

#endif