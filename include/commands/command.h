/**
 *  @file: command.h
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
#ifndef __COMMAND_H_
#define __COMMAND_H_
#include "transport/transport.h"

//! \brief Command interface abstract base class
//!
//! This is the base class for commands, which a part of command 
//! design pattern.
//!
class Command
{
public:

    //! \brief Default virtual destructor
    virtual ~Command() {};

    //! \brief Execute a stand alone command
    //!
    virtual int execute() = 0;

    //! \brief Execute Command against transport
    //!
    //! \param transport    pointer to transport device class
    //virtual int execute(TransportDevice *transport) = 0;
};


#endif