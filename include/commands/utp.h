/**
 *  @file: utp.h
 *
 *  Copyright (C) 2020  Joe Turner <joe@agavemountain.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef _UTP_H_
#define _UTP_H_
#include <stdint.h>

//! The UTP request structure is defined as a 16-byte SCSI CDB
#define UTP_CDB_SIZE            0x10

//! \brief UTP Command Timeout (in milliseconds)
//!
//! The device should reply BUSY for operations taking longer
//! than five (5) seconds.
#define UTP_COMMAND_TIMEOUT     (5 * 60 * 1000)

//! \brief Maximum data transmit block size.
#define UTP_MAX_DATA_SIZE       0x10000

//! \brief Number of times to poll if busy
#define UTP_BUSY_CHECK_COUNT    500

//! \brief Duration of sleep while polling (50ms)
#define UTP_BUSY_SLEEP          500000

//! \todo SCSI spec states that all values are stored in big-endian
//! format.  No translation is currently being done.  Code needs
//! to be implemented to account for endian-ness of the host and 
//! properly translate the endian-ness of the values.

#pragma pack(1)

//! \brief UTP SCSI CDB (Command Descriptor Block)
//!
//! UTP as a SCSI CDB (Command Descriptor Block)
//! \note per Per SCSI protocol, each field is sent in big-endian order. 
struct UTP_CDB
{
    //! \brief SCSI CDB Operation Code
    //! This value is always fixed as 0xF0 
    uint8_t operation_code;                 //! CDB[0]
    
    //! \brief UTP Message Type
    //!
    //! 0 = Poll
    //! 1 = Exec
    //! 2 = Get
    //! 3 = Put
    uint8_t UTP_message_type;               //! CDB[1]

    //! Each UTP transaction contains a 32-bit tag used to
    //! group messages belonging to the same UTP transaction.
    //! This is for sanity checking only, as UTP message from 
    //! multiple transactions cannot be interlealved.
    uint32_t UTP_message_tag;               //! CDB[2:5]

    uint32_t UTP_message_parameter_upper32; //! CDB[6:9]
    uint32_t UTP_message_parameter_lower32; //! CDB[10:13]
    uint16_t reserved;
};

//! \brief UTP Sense Reply Header
//!
//! \note per Per SCSI protocol, each field is sent in big-endian order. 
struct UTP_SCSI_SENSE_REPLY_HEADER
{
    //! \brief Respnose code
    //! Response code is fixed at 0x70
    uint8_t respose_code;

    uint8_t segment_number;

    //! \brief Sense Key
    //! The sense key for UTP replies is 0x09
    uint8_t sense_key;
    uint32_t UTP_reply_info_lower32;
    uint8_t addtional_sense_length;
    uint32_t UTP_reply_info_upper32;

    //! \brief Additional sense code
    //! Fixed with a value of 0x80
    uint8_t additional_sense_code;

    //! \brief Additional sense qualifier
    //! 
    //! UTP reply code (0=PASS, 1=EXIT, 2=BUSY, 3=SIZE)
    uint8_t UTP_reply_code;
};
#pragma pack()


enum UTP_MESSAGE_TYPE : unsigned char
{
    //! \brief Poll status
    //!
    //! Used to determine when an asynchronous device command is finished,
    //! and to query the UTP version.
    UTP_POLL = 0,

    //! \brief Exec
    //!
    //! Transfers a device command and its parameters
    UTP_EXEC = 1,

    //! \brief Get
    //!
    //! Transfers the command payload to the host (from the device).
    //! Payloads will be split into multiple 64KB messages.
    UTP_GET = 2, 

    //! \brief Put
    //!
    //! Transfers the command payload to the device (from the host).
    //! Payloads will be split into multiple 64KB messages.
    UTP_PUT = 3
};

//! \brief Reply Code
//!
//! Each UTP message either returns success or is followed by an
//! extended reply.  If a message completes without an error, the protocol
//! simply returns PASS in the CSW.  For extended replies, the CSW returns
//! FAIL and the complete reply is returned trhough fixed format sense
//! data.
enum UTP_REPLY_CODE : unsigned char
{
    //! \brief PASS reply
    //!
    //! The message completed successfully.  The result is returned in 
    //! the CSW (Command Status Wrapper), without a sense message.
    UTP_PASS = 0,

    //! \brief Exit reply
    //! The EXIT reply is used by the device to terminate the UTP
    //! transaction.  It can signal terminating errors, or reporting
    //! results that can be used to control the flow of the UCL.
    //!
    //! Sense[12-13] ASC+ASCQ = 0x8001
    //! Sense[03-06] Information = Result (0=PASS, >0 = Conditional result, <0 = Error).
    UTP_EXIT = 1,

    //! \brief BUSY reply
    //!
    //! The device is required to send back a BUSY response
    //! if an asynchronous command will take more than five (5) seconds.
    //!
    //! Sense[12-13] ASC+ASCQ = 0x8002
    //! Sense[03-06] Information = Progress countdown
    UTP_BUSY = 2,

    //! \brief SIZE reply
    //!
    //! The size reply is used for Device Read transactions to inform the host
    //! of the payload size.  After receiving a device command that returns
    //! payload data, the device would send a SIZE reply to the EXEC message
    //! so the host knows how much payload data to transfer.
    //!
    //! Sense[12-13] ASC+ASCQ = 0x8003
    //! Sense[03-06] Information = Size in bytes (64 bits)
    UTP_SIZE = 3,
};

#endif // #ifndef _UTP_H_
