/*
 * \file portable.h
 *
 * Macros and functions to aid in portability between platforms
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
#include <stdint.h>

#ifdef __GNUC__
  #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define BE32(x) __builtin_bswap32(x)
    #if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 8))
      #define BE16(x) __builtin_bswap16(x)
    #else
        #define BE16(x)                                                                \
        ({                                                                           \
            typeof(x) __x = (x);                                                       \
            (((__x << 8) & 0xffff) | ((__x >> 8) & 0xff));                             \
        })
    #endif
  #else
    #define BE32(x) x
    #define BE16(x) x
  #endif
#endif

