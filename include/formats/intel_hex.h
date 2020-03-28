/**
 *  @file: intel_hex.h
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
#include <map>
#include <iostream>
#include "formats/hex_data.h"

namespace superflash {
namespace formats {

//! \brief Intel HEX file class
//!
//! The Intel Hexadecimal Object file format, (a.k.a, Intel hex format, or Intellec Hex)
//! is a file format that contains binary information in ASCII text form.
//!
//! The file is line based, where lines of ASCII text are seperated by line feed or carriage
//! returns (or both).
//!
//! Each line is record.
//!
//! A record consists of six fields that appear from left to right:
//! # Start code ':'
//! Byte count (two hex digits) indicating the number of bytes (hex digit pairs) in the 
//! data field.  Maximum byte count is 255 (0xFF); 16 (0x10) and 32 (0x20) are most commonly 
//! used.
class intel_hexfile : public hex_data
{

public:

    struct HEX_FLAGS
    {
        int hasStartSegment:1;
        int hasLinearAddress:1;
        int eof:1;
    };

    enum HEX_RECORD_TYPE
    {
        //! \brief Data record type
        //!
        //! This record contains data and a 16-bit starting address for the data.  The
        //! byte count specifies the number of data bytes in the record. 
        HEX_DATA = 0,
        
        //! \brief End Of File record type
        //!
        //! This record type MUST occur exactly once per file in the last line of the file.
        //! The data field is empty (byte count is 00) and the address field is typicaly 0000.
        HEX_EOF = 1,
        
        //! \brief Extended Segment Address Record
        //!
        //! The data field contains a 16-bit segment base address; byte count is always 02; 
        //! address field is typically 000 and ignored.  The segment address from the most recent
        //! ESA record is multipolied by 16 and added to each subsequent data record address to form
        //! the physical starting address for data.
        HEX_EXT_SEG = 2,

        //! \brief 
        //!
        //! For 80x86 processors, specifies the initial content of the CS:IP registers (i.e., the 
        //! starting execution address). The address field is 0000, the byte count is always 04, 
        //! the first two data bytes are the CS value, the latter two are the IP value.
        HEX_START_SEG =3,

        //! Allows for 32 bit addressing (up to 4GiB). The record's address field is ignored 
        //! (typically 0000) and its byte count is always 02. The two data bytes (big endian) 
        //! specify the upper 16 bits of the 32 bit absolute address for all subsequent type 00 
        //! records; these upper address bits apply until the next 04 record. The absolute address 
        //! for a type 00 record is formed by combining the upper 16 address bits of the most 
        //! recent 04 record with the low 16 address bits of the 00 record. If a type 00 record 
        //! is not preceded by any type 04 records then its upper 16 address bits default to 0000.
        HEX_EXT_LINEAR = 4,

        //! The address field is 0000 (not used) and the byte count is always 04. The four data 
        //! bytes represent a 32-bit address value (big-endian). In the case of 80386 and higher 
        //! CPUs, this address is loaded into the EIP register.
        HEX_START_LINEAR = 5,
    };

    bool isValid(std::string &line);
    
private:

    friend std::ostream& operator<<(std::ostream& sout, intel_hexfile& hex);
    friend std::istream& operator>>(std::istream& sin, intel_hexfile& hex);
};

//! \brief Input stream overload operator
//!
//! Operator overloaded to decoded data streamed in from a file, cin, etc.
std::istream& operator>>(std::istream& sin, intel_hexfile& src);
std::ostream& operator<<(std::ostream& sout, intel_hexfile& hex);
}
}