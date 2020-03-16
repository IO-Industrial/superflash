/**
 *  @file: errors.h
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
#ifndef _ERRORS_H_
#define _ERRORS_H_

enum sf_ERROR
{
    SF_OK = 0,
    SF_ERR_NO_TRANSPORT_SPEC,
    SF_ERR_OPENING_TRANSPORT, 
    SF_ERR_SEND_UTP,
    SF_ERR_RECV_CORRUPTED_SENSE,
    SF_ERR_DEVICE_BUSY,
    SF_ERR_FILE_DOES_NOT_EXIST,

    SF_ERR_INVALID
};

void SF_ERROR(enum sf_ERROR error_number);

#endif 