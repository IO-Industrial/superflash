/**
 *  @file: binfile.h
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
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <vector>

namespace superflash {
namespace formats {

class simple_bin_file
{
public:

    int load(const std::string& filename)
    {
        std::ifstream fin { filename, std::ios::binary };
        fin.seekg(0, fin.end);
        size_t len = fin.tellg();
        fin.seekg(0, fin.beg);

        _data.resize(len);
        fin.read((char*)_data.data(), len);
        return _data.size();
    }

private:

    std::vector<uint8_t> _data;

    friend std::ostream& operator<<(std::ostream& sout, simple_bin_file& hex);
    friend std::istream& operator>>(std::istream& sin, simple_bin_file& hex);
    
};

//! \brief Input stream overload operator
//!
//! Operator overloaded to decoded data streamed in from a file, cin, etc.
std::istream& operator>>(std::istream& sin, simple_bin_file& src);
std::ostream& operator<<(std::ostream& sout, simple_bin_file& hex);

}
}

