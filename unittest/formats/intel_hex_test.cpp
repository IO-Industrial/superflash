
/**
 *  @file: intel_hex_test.h
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
#include "formats/intel_hex.h"
#include "gtest/gtest.h"
#include <stdio.h>

using namespace superflash::formats;

//! example test file with four data records followed by an end-of-file record:
const char* test_hex_file[] = {
    ":10010000214601360121470136007EFE09D2190140\n",
    ":100110002146017E17C20001FF5F16002148011928\n",
    ":10012000194E79234623965778239EDA3F01B2CAA7\n",
    ":100130003F0156702B5E712B722B732146013421C7\n",
    ":00000001FF\n",
    "",
};

const char* text_hex_file2[] = {
    ":020000020000FC\n",
    ":020000040000FA\n",
    ":1000000000FF0004000400040004000400040004D5\n",
    ":1000100000040004000400040004000400040004C0\n",
    ":1000200000040004000400040004000400040004B0\n",
    ":1000300000040004000400040004000400040004A0\n",
    ":100040000004000400040004000400040004000490\n",
    ":100050000004000400040004000400040004000480\n",
    ":100060000004000400040004000400040004000470\n",
    ":100070000004000400040004000400040004000460\n",
    ":100080000004000400040004000400040004000450\n",
    ":100090000004000400040004000400040004000440\n",
    ":1000A0000004000400040004000400040004000430\n",
    ":1000B0000004000400040004000400040004000420\n",
    ":1000C0000004000400040004000400040004000410\n",
    ":1000D0000004000400040004000400040004000400\n",
    ":1000E00000040004000400040004000400040004F0\n",
    ":1000F00000040004000400040004000400040004E0\n",
    ":020000020010EC\n",
    ":1000000000040004000400040004000400040004D0\n",
    ":1000100000040004000400040004000400040004C0\n",
    ""
};

//! Checksum should be E2
const char* hex_chksum = ":0300300002337A1E\n";

namespace {
// Tests the Increment() method.

TEST(IntelHex, default_ctor)
{
    intel_hexfile hex;
    ASSERT_TRUE(hex.empty());
    ASSERT_EQ(hex.size(), 0);
}

}; // namespace