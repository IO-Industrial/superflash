/**
 *  @file: utp_command.cpp
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
#include "commands/utp_command.h"
#include "bytesex.h"
#include "protocols/utp.h"
#include "errors.h"
#include "file_utilities.h"
#include <arpa/inet.h>
#include <assert.h>
#include <fstream>
#include <iterator>
#include <memory>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <vector>

int UTPCommand::send(SCSIGenericTransportDevice* dev, void* data, int length)
{
    assert(dev);
    int rc = dev->send(&m_msg, data, length, m_reply);
    m_replyCode = m_reply.UTP_reply_code;
    return rc;
}

void UTPCommand::reset()
{
    memset(&m_msg, 0, sizeof(UTP_CDB));
    memset(&m_reply, 0, sizeof(m_reply));
    m_replyCode = 0;
}

bool UTPCommand::isReplyGood() const
{

    hexdump((void*)&m_reply, sizeof(m_reply));

    if ((m_reply.respose_code == 0x70) && (m_reply.additional_sense_code == 0x80) && (m_reply.sense_key == 0x09)) {
        return true;
    }

    // SF_ERROR(SF_ERR_RECV_CORRUPTED_SENSE);
    return false;
}

int UTPExecCommand::execute(SCSIGenericTransportDevice* transport)
{
    reset();
    m_msg.operation_code = 0xF0;
    m_msg.UTP_message_type = UTP_EXEC;
    m_msg.UTP_message_parameter_upper32 = 0;
    m_msg.UTP_message_parameter_lower32 = 0;
    m_msg.reserved = 0;

    printf("Sending EXEC CDB:\n");
    hexdump(&m_msg, sizeof(m_msg));
    printf("* command: %s\n", _command.c_str());

    int rc = send(transport, (void*)_command.c_str(), _command.length());
    if (rc < 0) {
        SF_ERROR(SF_ERR_SEND_UTP);
        return rc;
    };

    isReplyGood();

    return m_replyCode;
}

int UTPExecSendSize::execute(SCSIGenericTransportDevice* transport)
{
    reset();
    m_msg.operation_code = 0xF0;
    m_msg.UTP_message_type = UTP_EXEC;
    m_msg.UTP_message_parameter_upper32 = 0;
    m_msg.UTP_message_parameter_lower32 = htonl(file_size);
    m_msg.reserved = 0;

    printf("Sending EXEC / SIZE CDB:\n");
    hexdump(&m_msg, sizeof(m_msg));

    int rc = send(transport, (void*)_command.c_str(), _command.length());
    if (rc < 0) {
        SF_ERROR(SF_ERR_SEND_UTP);
        return rc;
    };

    isReplyGood();

    return m_replyCode;
}

int UTPPutSend::execute(SCSIGenericTransportDevice* transport)
{
    reset();
    m_msg.operation_code = 0xF0;
    m_msg.UTP_message_type = UTP_PUT;
    m_msg.UTP_message_parameter_upper32 = 0;
    m_msg.UTP_message_parameter_lower32 = 0;
    m_msg.reserved = 0;

    printf("Sending PUT CDB:\n");
    hexdump(&m_msg, sizeof(m_msg));

    int rc = send(transport, (void*)data, data_size);

    if (rc < 0) {
        SF_ERROR(SF_ERR_SEND_UTP);
        return rc;
    };

    isReplyGood();

    return m_replyCode;
}

int UTPPollCommand::execute(SCSIGenericTransportDevice* transport)
{
    reset();
    m_msg.operation_code = 0xF0;
    m_msg.UTP_message_type = UTP_POLL;
    m_msg.UTP_message_parameter_upper32 = 0;
    m_msg.UTP_message_parameter_lower32 = 0;
    m_msg.reserved = 0;

    printf("Sending POLL CDB:\n");
    hexdump(&m_msg, sizeof(m_msg));

    int rc = send(transport, NULL, 0);
    if (rc < 0) {
        SF_ERROR(SF_ERR_SEND_UTP);
        return rc;
    };

    isReplyGood();

    return m_replyCode;
}

int UTPVersion::execute(SCSIGenericTransportDevice* transport)
{
    reset();
    m_msg.operation_code = 0xF0;
    m_msg.UTP_message_type = UTP_POLL;
    m_msg.UTP_message_parameter_upper32 = 0;
    m_msg.UTP_message_parameter_lower32 = htonl(0x1);
    m_msg.reserved = 0;

    printf("Sending CDB:\n");
    hexdump(&m_msg, sizeof(m_msg));

    int rc = send(transport, NULL, 0);
    if (rc < 0) {
        SF_ERROR(SF_ERR_SEND_UTP);
        return rc;
    };

    isReplyGood();

    m_version = ntohl(m_reply.UTP_reply_info_lower32);
    printf("UTP VERSION = 0x%x\n", m_version);

    // For version query, the reply should be EXIT with the version
    // code.
    return m_replyCode;
}

int utp_wait_for_busy(SCSIGenericTransportDevice* transport)
{
    int result = 0;

    for (int i = 0; i < UTP_BUSY_CHECK_COUNT; i++) {
        usleep(UTP_BUSY_SLEEP);
        UTPPollCommand poll;
        result = poll.execute(transport);
        if (result <= 0) {
            break;
        }

        if (i == UTP_BUSY_CHECK_COUNT - 1) {
            SF_ERROR(SF_ERR_DEVICE_BUSY);
            return -1;
        }
    }

    return result;
}

int utp_send_command_with_wait(SCSIGenericTransportDevice* transport, std::string command)
{
    int result = 0;

    UTPExecCommand exec(command);
    result = exec.execute(transport);
    if (result == UTP_PASS) {
        return result;
    }

    if (result == UTP_EXIT) {
        printf("command returned EXIT.\n");
        return result;
    }

    result = utp_wait_for_busy(transport);
    return result;
}

int utp_send_file(SCSIGenericTransportDevice* transport, std::string command, std::string filename)
{
    int result = 0;

    // check that the file exists
    if (!doesFileExist(filename)) {
        SF_ERROR(SF_ERR_FILE_DOES_NOT_EXIST);
        return -1;
    }

    int file_size = getFileSize(filename);

    // read the file into memory
    std::vector<unsigned char> data = load_file_into_vector(filename);
    printf("*** Sending file : %s (%d bytes / %zd bytes)\n", filename.c_str(), file_size, data.size());

    // send size
    UTPExecSendSize exec(command);
    exec.file_size = file_size;
    result = exec.execute(transport);
    printf("result = %d\n", result);
    if (result == UTP_BUSY) {
        result = utp_wait_for_busy(transport);
    }

    // send the file chunk by chunk until we are done.
    UTPPutSend put;

    int data_written = 0;
    uint8_t* file_data = data.data();

    while (data_written < file_size) {
        printf("%d out of %d bytes written to device.\n", data_written, file_size);

        UTPPutSend put;
        int write_size = file_size - data_written > UTP_MAX_DATA_SIZE ? UTP_MAX_DATA_SIZE : file_size - data_written;
        printf("Writing %d bytes\n", write_size);
        put.data = file_data + data_written;
        put.data_size = write_size;
        result = put.execute(transport);
        printf("result = %d\n", result);
        if (result < 0) {
            fprintf(stderr, "Send_cmd failed (put_send)\n");
            break;
        }

        if (result == UTP_BUSY) {
            result = utp_wait_for_busy(transport);
        }

        data_written += write_size;
    }
    return result;
}