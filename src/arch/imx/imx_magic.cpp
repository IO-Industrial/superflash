/**
 *  @file: imx_magic.cpp
 *
 *  Copyright (C) 2021  Joe Turner <joe@agavemountain.com>
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
#include "arch/imx/imx_magic.h"

uint8_t magic[] = { 0x23, 0x45, 0x45, 0x23 };

uint8_t vybrid_can_magic[] = { 0x67, 0x89, 0x89, 0x67};

uint8_t vybrid_HAB_development[] = { 0x56, 0x78, 0x78, 0x56 };
uint8_t vybrid_HAD_production[] = { 0x12, 0x34, 0x34, 0x12 };