/**
 *  @file: utp_command.h
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
#ifndef __UTP_COMMAND_H_
#define __UTP_COMMAND_H_
#include "commands/command.h"
#include "transport/sg_transport.h"
#include <string>

//! \brief UTP Command
//!
//! This command class encapsulates a singular UTP command
//! to be sent to the SCSI generic interface for the device.
//!
//! There are two possible uses of this command, send a single
//! command, or send a file (with a command specifiying the address)
//!
//!
//! \code{.cpp}
//! SCSIGenericTransport *pdev = new SCSIGenericTransport("/dev/sg0");
//! if (pdev->Open() < 0) {
//!     printf("Error opening transport.\n");
//! }
//! else
//! {
//!     UTPVersion ver;
//!     if (ver.execute(pdev) == UTP_EXIT) {
//!         printf("UTP version %d\n", ver.version);
//!     }
//!     else {
//!         printf("unexpected return value.\n");
//!     }
//! }
//!  \endcode
class UTPCommand : public Command {

public:
    //! \brief Default constructor
    UTPCommand() { }

    //! \brief specialized constructor
    //!
    //! \param device_name  path of SCSI device
    //! \param cmd          UTP command text string
    //! \param file_name    path and name of the file to be sent to device
    UTPCommand(const std::string& cmd, const std::string& file_name);

    //! \brief Execute a stand alone command
    //!
    //! \returns
    virtual int execute() { return 0; };

    //! \brief Execute Command against transport
    //!
    //! \param transport    pointer to transport device class
    virtual int execute(SCSIGenericTransportDevice* dev) { return 0; };

    int getReplyCode() const { return (m_replyCode); }
    bool isBusy() const { return (m_replyCode == UTP_BUSY); }
    bool isExit() const { return (m_replyCode == UTP_EXIT); }
    bool isSize() const { return (m_replyCode == UTP_SIZE); }

    bool isReplyGood() const;
    void reset();

protected:
    int send(SCSIGenericTransportDevice* dev, void* data, int length);
    struct UTP_CDB m_msg;
    struct UTP_SCSI_SENSE_REPLY_HEADER m_reply;
    uint8_t m_replyCode;
};

//! \brief UTP exec command
//!
//! This is the command that will be sent to the device.  It is a
//! text string.  While there is no documentation I could find, there
//! several commands that are generally supported: pipe, pollpipe, pipeaddr.
//! Commands prefixed with a dollar sign ($) are shell commands.
//!
//! "?"
//! "!<type>"
//! "$ <shell command>"
//!
//! "pipeaddr addr=0x81000000"
//!
//! \param cmd  command string to send to target device
//!
//! \returns
//! This function returns true if the transaction succeeded; else this
//! function will return false if an error occured.
class UTPExecCommand : public UTPCommand {
public:
    //! \brief specialized constructor
    //!
    //! \param cmd          UTP command text string
    UTPExecCommand(const std::string& cmd)
        : _command(cmd)
    {
    }

    //! \brief Execute UTP command
    //!
    //! \returns
    //! This function may return UTP_EXIT, UTP_BUSY or UTP_PASS
    virtual int execute(SCSIGenericTransportDevice* transport);

    //! \brief UTP command
    //!
    //! This is the command that will be sent to the device.  It is a
    //! text string.  While there is no documentation I could find, there
    //! several commands that are generally supported: pipe, pollpipe, pipeaddr.
    //! Commands prefixed with a dollar sign ($) are shell commands.
    //!
    //! "?"
    //! "!<type>"
    //! "$ <shell command>"
    //!
    //! "pipeaddr addr=0x81000000"
    std::string _command;
};

//! \brief UTP exec command
//!
//! \param cmd  command string to send to target device
//!
//! \returns
//! This function returns true if the transaction succeeded; else this
//! function will return false if an error occured.
class UTPExecSendSize : public UTPCommand {
public:
    //! \brief specialized constructor
    //!
    //! \param cmd          UTP command text string
    UTPExecSendSize(const std::string& cmd)
        : _command(cmd) {};

    //! \brief Execute UTP command
    //!
    //! \returns
    virtual int execute(SCSIGenericTransportDevice* transport);

    uint32_t file_size;
    std::string _command;
};

//! \brief UTP exec command
//!
//! \param cmd  command string to send to target device
//!
//! \returns
//! This function returns true if the transaction succeeded; else this
//! function will return false if an error occured.
class UTPPutSend : public UTPCommand {
public:
    //! \brief Execute UTP command
    //!
    //! \returns
    //! This function may return UTP_EXIT, UTP_BUSY or UTP_PASS
    virtual int execute(SCSIGenericTransportDevice* transport);

    void* data;
    int data_size;
};

//! \brief UTP POLL command
//!
//! A Poll command is used to determine when an asynchronous device
//! command is finished.  It is also used to query the UTP version.
//!
class UTPPollCommand : public UTPCommand {
public:
    //! \brief Execute UTP command
    //!
    //! This function will format the CDB to query the status of
    //! UTP state machine on the target device.
    //!
    //! \param  transport   pointer to transport device class
    //!
    //! \returns
    //! This function may return UTP_EXIT, UTP_BUSY or UTP_PASS
    virtual int execute(SCSIGenericTransportDevice* transport);
};

//! \brief UTP command to query UTP version on target device
class UTPVersion : public UTPCommand {
public:
    //! \brief Execute UTP poll command to query version.
    //!
    //! This function will format the CDB to query the UTP version
    //! from the target device.
    //!
    //! \param  transport   pointer to transport device class
    //!
    //! \returns
    //!
    //! Per documentation, this should only return UTP_EXIT.
    virtual int execute(SCSIGenericTransportDevice* transport);

    //! \brief UTP version on target device
    uint32_t m_version;
};

int utp_send_command_with_wait(SCSIGenericTransportDevice* transport, std::string command);
int utp_send_file(SCSIGenericTransportDevice* transport, std::string command, std::string filename);
#endif