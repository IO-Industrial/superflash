/**
 *  @file: formats.h
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

namespace superflash {

/**
 * \defgroup formats Firmware Files
 * @brief Classes for parsing, converting, or generating firmware files
 *
 *  Firmware files are executable and linkable files, usually processed to a binary (.bin) or
 *  text file represented binary (.hex).  There are various file formats supported by various
 *  manufacturers.
 * 
 * File Format   | Description
 * ------------- | -----------
 * Raw binary    | Raw binary file without addressing or segmentation
 * Intel Hex     | Intel hex file format
 */

/** 
 * \brief Firmware File Formats
 * 
 *  Firmware files are executable and linkable files, usually processed to a binary (.bin) or
 *  text file represented binary (.hex).  There are various file formats supported by various
 *  manufacturers.
 *
 *  This namespace contains clases for parsing, converting, or generating firmware
 *  files.
 *
 *  # Supported file formats
 *
 *  Intel Hex file format.  Intel hex file format is a text based file where executable code is
 *  encoded in hexadecimal ASCII records that contain addresses and code.
 * 
 * \ingroup formats
 */
namespace formats {

}
/*! @} End of Doxygen Groups*/

}
