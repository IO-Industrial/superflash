/**
 *  @file: file_utilities.cpp
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
#ifndef _FILE_UTILITIES_HPP_
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <vector>

//! \brief checks to see if a file exists
//!
//! \param filename     path and filename of the file to look for
//! \returns
//!     true if the file exists, else false.
inline bool doesFileExist(const std::string& filename)
{
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

//! \brief checks to see if a directory exists
//!
//! \param path     path and name of the directory to look for
//! \returns
//!     true if the directory exists, else false.
inline bool doesDirectoryExist(const std::string& path)
{
    struct stat buffer;
    return ((stat(path.c_str(), &buffer) == 0) && (buffer.st_mode & S_IFDIR));
}

inline size_t getFileSize(const std::string& filename)
{
    struct stat buffer;
    if (stat(filename.c_str(), &buffer) == 0) {
        return buffer.st_size;
    }
    return -1;
}

inline std::vector<unsigned char> load_file_into_vector(const std::string& filename)
{
    std::ifstream fin { filename, std::ios::binary };
    fin.seekg(0, fin.end);
    size_t len = fin.tellg();
    fin.seekg(0, fin.beg);

    std::vector<unsigned char> coll(len);
    fin.read((char*)coll.data(), len);
    return coll;
}

#endif