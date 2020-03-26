/**
 *  @file: errors.cpp
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
#include "errors.h"
#include <stdio.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"

namespace {
    const char *sf_errors[] =
    {
        "OK",
        "Error, no transport device specified",
        "Error, opening transport device",
        "Error, sending UTP message",
        "Error, UTP reply is corrupted",
        "Error, device is busy",
        "Error, specified file does not exist",
        "Error, failed to initialize USB context",
        "Invalid error code.",
    };
}

void SF_ERROR(enum sf_ERROR error_no)
{
    int idx = error_no;
    // range check
    if ( (error_no < SF_OK) || (error_no >= SF_ERR_INVALID))
    {
        idx = SF_ERR_INVALID;
    }

    //printf("Error %d: %s\n", idx, sf_errors[idx]);
    spdlog::error("Error {}: {}\n", idx, sf_errors[idx]);
}