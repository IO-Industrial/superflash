/**
 *  @file: hex_data.h
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
#include <stdint.h>

namespace superflash {
namespace formats {

    //! \brief Data container for firmware file parsers
    //!
    //! This class implements a generic data container used by all firmware
    //! file decoders, parsers, etc.
    //!
    //! Regardless of the format of the file format that contains the firmware
    //! to be downloaded into an embedded device, they all share some
    //! common data attributes.  This class generalizes the data as a container
    //! that is used by the parser classes.
    //!
    //! \todo Change internal data structure from map to something more memory efficient.
    //! \todo Make template to allow data to be stored as words or bytes.
    class hex_data {

    public:
        //! \brief Default constructor
        hex_data()
        {
            _data.clear();
            _data.begin();
            _iterator = _data.begin();
        }

        //! \brief Copy constructor
        hex_data(const hex_data& src)
        {
            _data = src._data;
            _iterator = src._iterator;
        }

        //! \brief Assignment operator
        hex_data operator=(const hex_data& src)
        {
            // protect against self-assignment
            if (this == &src) {
                return *this;
            }
            _data = src._data;
            _iterator = src._iterator;
            return *this;
        }

        virtual ~hex_data()
        {
        }

        //! \brief Size of decoded data
        //!
        //! \returns
        //! This function returns the size of the decoded data.
        unsigned long size()
        {
            return static_cast<unsigned long>(_data.size());
        }

        //! \brief Check to see if the data container is empty
        //!
        //! \returns
        //! \retval true  - the container is empty - no data has been extracted.
        //! \retval false - there is data in the container.
        bool empty()
        {
            return _data.empty();
        }

        //! \brief Overloaded prefix increment operator
        //!
        //! Overloads the prefix increment operator to move interal iterator to
        //! next entry in the _data map
        hex_data& operator++()
        {
            ++_iterator;
            return (*this);
        }

        //! \brief Overloaded postfix increment operator
        //!
        //! Overloads the postfix increment operator to move interal iterator to
        //! next entry in the _data map
        const hex_data operator++(int)
        {
            hex_data tmp(*this);
            ++(*this);
            return (tmp);
        }

        //! \brief Overloaded prefix decrement operator
        //!
        //! Overloads the prefix decrement operator to move interal iterator to
        //! previous entry in the _data map
        hex_data& operator--()
        {
            --_iterator;
            return (*this);
        }

        //! \brief Overloaded postfix decrement operator
        //!
        //! Overloads the postfix decrement operator to move interal iterator to
        //! previous entry in the _data map
        const hex_data operator--(int)
        {
            hex_data tmp(*this);
            --(*this);
            return (tmp);
        }

        //! \brief Moves the address pointer to the first available address.
        //!
        //! The address pointer will be moved to the first available address in
        //! memory of the decoded file or of the data the user has inserted into
        //! memory for the purpose of encoding into the Intel HEX format.
        //!
        //! \sa end()
        //!
        //! \note This function has no effect if no file has been as yet decoded
        //! and no data has been inserted into memory.
        void begin()
        {
            if (_data.size() != 0) {
                _iterator = _data.begin();
            }
        }

        //! \brief Moves the address pointer to the last available address.
        //!
        //! The address pointer will be moved to the last available address in
        //! memory of the decoded file or of the data the user has inserted into
        //! memory for the purpose of encoding into the Intel HEX format.
        //!
        //! \sa begin()
        //!
        //! \note This function has no effect if no file has been as yet decoded
        //! and no data has been inserted into memory.
        void end()
        {
            if (!_data.empty()) {
                _iterator = _data.end();
                --_iterator;
            }
        }

        //! \brief Inserts desired byte at the desired address.
        //!
        //! Inserts byte of data at the desired address.
        //!
        //! \param data       - data byte to be inserted
        //! \param address    - address at which to insert data
        //!
        //! \retval true      - data insertion was successful
        //! \retval false     - data insertion failed
        //!
        bool insert(uint8_t data, unsigned long address)
        {
            std::pair<
                std::map<unsigned long, uint8_t>::iterator, bool>
                ret;

            ret = _data.insert(std::pair<unsigned long, uint8_t>(address, data));

            return (ret.second);
        }

        //! \brief Insert a block of data
        //!
        //! \param base_address - base address at which to insert data
        //! \param data         - pointer data bytes to be inserted
        //! \param size         - number of bytes to insert
        //!
        //! \retval true      - data insertion was successful
        //! \retval false     - data insertion failed
        bool insert(unsigned long base_address, uint8_t* data, int size)
        {
            unsigned long addr = base_address;
            uint8_t* ptr = data;

            for (int i = 0; i < size; i++) {
                if (insert(*ptr, addr)) {
                    addr++;
                    ptr++;
                } else {
                    return false;
                }
            }
            return true;
        }

        //! \brief Retrieve value at address pointed to by internal iterator
        //!
        bool getData(uint8_t* data)
        {
            bool ret = false;
            if (!_data.empty() && (_iterator != _data.end())) {
                *data = _iterator->second;
                ret = true;
            }
            return ret;
        }

        //! \brief Returns current address
        //!
        //! This function will return the current address pointed to by
        //! the internal iterator.
        //!
        //! \retval Current address that the internal iterator is pointing to.
        unsigned long getCurrentAddress()
        {
            return _iterator->first;
        }

        //! \brief get a copy of the iterator.
        std::map<unsigned long, uint8_t>::iterator getIterator()
        {
            return _iterator;
        }

        //! \brief Returns lowest address currently available in our map
        //!
        //! This function returns the first address that appears in memory
        //! if there is data available.  If no data is available, no data
        //! will be returned.
        //!
        //! \param address  pointer to address
        //!
        //! \retval true    - address exists and the returned value is valid
        //! \retval false   - address did not exist and return value is not valid.
        bool getStartAddress(unsigned long* address)
        {
            bool ret = false;
            if (_data.size() != 0) {
                std::map<unsigned long, uint8_t>::iterator it;
                it = _data.begin();
                *address = (*it).first;
                ret = true;
            }
            return ret;
        }

        //! \brief Returns highest address currently available in our map
        //!
        //! This function returns the first address that appears in memory
        //! if there is data available.  If no data is available, no data
        //! will be returned.
        //!
        //! \param address  pointer to address
        //!
        //! \retval true    - address exists and the returned value is valid
        //! \retval false   - address did not exist and return value is not valid.
        bool getEndAddress(unsigned long* address)
        {
            bool ret = false;
            if (_data.size() != 0) {
                std::map<unsigned long, uint8_t>::reverse_iterator it;
                it = _data.rbegin();
                *address = (*it).first;
                ret = true;
            }
            return ret;
        }

        //! \brief Returns the data from the desired address.
        //!
        //! Returns the data for the desired address. If the address has no data
        //! assigned to it, the function returns false, the pointer to data is not
        //! written and the class's address pointer remains unchanged. If the
        //! address has data assigned to it, the pointer to data will be written
        //! with the data found and the class's address pointer will be moved to
        //! this new location.
        //!
        //! \param data       - variable to hold data requested
        //! \param address    - address to be queried for valid data
        //!
        //! \retval true      - data was available and returned value is valid
        //! \retval false     - data was not available and returned valid is not
        //!                     valid
        bool getData(uint8_t* data, const unsigned long address)
        {
            bool found = false;
            std::map<unsigned long, unsigned char>::iterator iterator;
            if (!_data.empty()) {
                iterator = _data.find(address);
                if (iterator != _data.end()) {
                    found = true;
                    _iterator = iterator; // reset iterator to point to this value.
                    *data = iterator->second;
                }
            }
            return found;
        }

    protected:
        //!\brief Decoded data from intel hex file
        //!
        //! Thißs STL map contains address and the decoded data at that address.
        std::map<unsigned long, uint8_t> _data;

        //! \brief Iterator for the container holding the decoded data
        //!
        //! This iterator is used by the class to point to the location in memory
        //! currently being used to read or write data. If no file has been
        //! loaded into memory, it points to the start of _data.
        std::map<unsigned long, uint8_t>::iterator _iterator;
    };

}
}
