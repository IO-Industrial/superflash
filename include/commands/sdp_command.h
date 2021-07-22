/**
 *  @file: sdp_command.h
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
#pragma once
#include "commands/command.h"
#include "commands/sdp.h"

//! \brief Command interface abstract base class
//!
//! This is the base class for commands, which a part of command
//! design pattern.
//!
class SDPCommand : public Command {
public:
    //! \brief Default constructor
    SDPCommand() { }

    //! \brief Default virtual destructor
    virtual ~SDPCommand() {};

    //! \brief Execute a stand alone command
    //!
    //! \returns
    virtual int execute() { return 0; };

    //! \brief Execute Command against transport
    //!
    //! \param transport    pointer to transport device class
    //virtual int execute(TransportDevice *transport) = 0;

protected:
    struct sdp_command m_msg;
};

class SDPWriteFileCommand : public Command {
};

class SDPJumpCommand : public Command {
};

class SDPWriteDCDCommand : public Command {
};

class SDPStatusCommand : public Command {
};

class SDPWriteRegCommand : public Command {
};

class SDPReadRegCommand : public Command {
};
