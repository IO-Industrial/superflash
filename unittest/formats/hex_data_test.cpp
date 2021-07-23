/**
 *  @file: hex_data_test.h
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
#include "formats/hex_data.h"
#include "gtest/gtest.h"
#include <stdio.h>

using namespace superflash::formats;

TEST(HexData, default_ctor_no_data)
{
    hex_data hex;
    ASSERT_TRUE(hex.empty());
    ASSERT_EQ(hex.size(), 0);
}

TEST(HexData, assign_no_data)
{
    hex_data hex;
    ASSERT_TRUE(hex.empty());
    ASSERT_EQ(hex.size(), 0);

    hex_data hex2 = hex;
    ASSERT_TRUE(hex2.empty());
    ASSERT_EQ(hex2.size(), 0);
}

TEST(HexData, insert)
{
    hex_data hex;
    ASSERT_TRUE(hex.empty());
    ASSERT_EQ(hex.size(), 0);

    ASSERT_TRUE(hex.insert(0xa, 0x1234));

    ASSERT_TRUE(!hex.empty());
    ASSERT_EQ(hex.size(), 1);

    // inserting second time should fail.
    ASSERT_FALSE(hex.insert(0xa, 0x1234));
}

TEST(HexData, get_data)
{
    hex_data hex;
    uint8_t dataval;

    ASSERT_TRUE(hex.empty());
    ASSERT_EQ(hex.size(), 0);

    ASSERT_TRUE(hex.insert(0xa, 0x1234));

    ASSERT_TRUE(!hex.empty());
    ASSERT_EQ(hex.size(), 1);

    ASSERT_TRUE(hex.getData(&dataval, 0x1234));
    ASSERT_EQ(dataval, 0xa);

    // attempt to get data for invalid address should fail.
    ASSERT_FALSE(hex.getData(&dataval, 0x4321));
}

TEST(HexData, get_address)
{
    hex_data hex;
    uint8_t dataval;
    unsigned long addr;

    ASSERT_TRUE(hex.empty());
    ASSERT_EQ(hex.size(), 0);

    // should return false if empty.
    ASSERT_FALSE(hex.getStartAddress(&addr));
    ASSERT_FALSE(hex.getEndAddress(&addr));

    ASSERT_TRUE(hex.insert(0xa, 0x1234));
    ASSERT_TRUE(hex.insert(0xb, 0x1235));

    ASSERT_TRUE(hex.getStartAddress(&addr));
    ASSERT_EQ(addr, 0x1234);

    ASSERT_TRUE(hex.getEndAddress(&addr));
    ASSERT_EQ(addr, 0x1235);
}
