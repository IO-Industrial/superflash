/*
 * \file sg_transport.h
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
#include "transport/sg_transport.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#ifdef __linux__ 
#include <scsi/sg_lib.h>
#include <scsi/sg_io_linux.h>
#endif

int SCSIGenericTransportDevice::send(struct UTP_CDB *message, void *dxferp, int dxferp_len, struct UTP_SCSI_SENSE_REPLY_HEADER &reply)
{
	int ret = 0;
#ifdef __linux__ 
    struct sg_io_hdr sgio_hdr;
	memset(&sgio_hdr, 0, sizeof(sgio_hdr));
	sgio_hdr.sbp = (uint8_t *)&reply;
	sgio_hdr.interface_id = 'S';
	sgio_hdr.timeout = UTP_COMMAND_TIMEOUT;
	sgio_hdr.cmd_len = sizeof(struct UTP_CDB);
	sgio_hdr.cmdp = (unsigned char *)message;
	sgio_hdr.mx_sb_len = sizeof(struct UTP_SCSI_SENSE_REPLY_HEADER);
	sgio_hdr.dxfer_direction = SG_DXFER_TO_DEV;
	sgio_hdr.dxfer_len = dxferp_len;
	sgio_hdr.dxferp = dxferp;

	ret = ioctl(_device_fd, SG_IO, &sgio_hdr);
	if (ret < 0)
	{
		fprintf(stderr, "SG_IO ioctl error\n");
		Close();
	}
#else 
	// MAC doesn't support generic scsi operations without writing kernel code.
	fprintf(stderr, "Operation not supported under this operating system.\n");
    return ret;  
#endif
}

int SCSIGenericTransportDevice::send_sg(uint8_t *header, int headerlen, void *dxferp, int dxferp_len, uint8_t *reply_code)
{
	int ret = -1;
#ifdef __linux__ 
    struct sg_io_hdr sgio_hdr;
    const int SENSE_BUF_SIZE = 16;
	const int CMD_TIMEOUT         = (5 * 60 * 1000);

    uint8_t sensebuf[SENSE_BUF_SIZE] = {0};

    memset(&sgio_hdr, 0, sizeof(sgio_hdr));
	sgio_hdr.sbp = sensebuf;
	sgio_hdr.interface_id = 'S';
	sgio_hdr.timeout = CMD_TIMEOUT;
	sgio_hdr.cmd_len = headerlen;
	sgio_hdr.cmdp = (unsigned char *)header;
	sgio_hdr.mx_sb_len = SENSE_BUF_SIZE;
	sgio_hdr.dxfer_direction = SG_DXFER_TO_DEV;
	sgio_hdr.dxfer_len = dxferp_len;
	sgio_hdr.dxferp = dxferp;

	// Call IOCTL
	ret = ioctl(_device_fd, SG_IO, &sgio_hdr);
	if (ret < 0)
	{
		fprintf(stderr, "SG_IO ioctl error\n");
		Close();
	}
#else 
	// MAC doesn't support generic scsi operations without writing kernel code.
	fprintf(stderr, "Operation not supported under this operating system.\n");
    return ret;  
#endif
}

