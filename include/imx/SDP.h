/*
 * \file SDP.h
 *
 * Protypes and structures for Freescale/NXP's Serial Download Protocol (SDP)
 * (Applicable to i.MX/Vybrid series processors)
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
#include <portable.h>
#include <stdint.h>
#include <string.h>

namespace imx {

#pragma pack(1)
//! \brief Serial Download Protocol command
//! This structure contains the command that is
//! sent to the device.
struct SDP_Command {
  uint16_t command;
  uint32_t address;
  uint8_t format;
  uint32_t count;
  uint32_t data;
  uint8_t reserved;
};
#pragma pack()

//!\brief Serial Download Protocol (SDP) command object
//!
class SDPCommand {

public:
  //! \brief Serial Download Protocol (SDP) command enumeration
  //!
  //! This enumeration contains the command values.
  enum SDP_CMD : uint16_t {
    SDP_READ_REG = 0x0101,
    SDP_WRITE_REG = 0x0202,
    SDP_WRITE_FILE = 0x0404,
    SDP_ERROR_STATUS = 0x0505,
    SDP_CMD_HEADER = 0x6060,
    SDP_WRITE_DCD = 0x0a0a,
    SDP_JUMP_ADDRESS = 0x0b0b,
    SDP_SKIP_DCD_HEADER = 0x0c0c,
  };

  void jump(uint32_t header_address) {
    reset();
    _cmd.command = SDP_JUMP_ADDRESS;
    _cmd.address = BE32(header_address);
  }

  void read(uin32_t address, uint32_t count) {
    reset();
    _cmd.command = SDP_READ_REG;
    _cmd.address = BE32(address);
    _cmd.format = 0x20;
    _cmd.count = BE32(count);
    _cmd.data = 0;
  }

  void write(uint32_t address, uint32_t value) {
    reset();
    _cmd.command = SDP_WRITE_REG;
    _cmd.address = BE32(address);
    _cmd.format = 0x20;
    _cmd.count = BE32(4);
    _cmd.data = BE32(value);
  }

  void write_file(uint32_t address, uint32_t file_size, uint8_t type) {
    reset();
    _cmd.command = SDP_WRITE_FILE;
    _cmd.address = BE32(address);
    _cmd.count = BE32(file_size);
    _cmd.reserved = type;
  }

  void status() {
    reset();
    _cmd.command = SDP_ERROR_STATUS;
  }

  void dcd(uint32_t dcd_address, int length) {
    reset();
    _cmd.command = SDP_WRITE_DCD;
    _cmd.address = BE32(dcd_address);
    _cmd.count = BE32(length);
  }

  //! \brief Returns the size of the command.
  int size() const { return sizeof(struct SDP_Command); }

  void reset() {
    memset(static_cast<unsigned char *>(_cmd), 0, sizeof(struct SDP_Command));
  }

private:
  struct SDP_Command _cmd;
};

} // namespace imx
