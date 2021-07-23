/**
 *  @file: utp.cpp
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
#include "config/global_config.h"
#include "errors.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/spdlog.h"
#include "version.h"
#include <getopt.h>
#include <iostream>

using namespace std;
// using namespace spdlog;

const char* usage[] = {
    "Usage: utp -d device -c command [-f file]",
    "\t-d\tdevice (example /dev/sg0)",
    "\t-c\tcommand to be run",
    "\t-f\tfile to be set",
    "\te.g. sudo ./utp -d /dev/sdb -c \"$ uname -r\"",
    ""
};

void print_usage()
{
    for (int i = 0; *usage[i]; i++) {
        printf("%s\n", usage[i]);
    }
}

int main(int argc, char** argv)
{
    int c;
    std::string device_name = "";
    std::string command = "";
    char* file_name = NULL;
    char* file_data = NULL;

    printf("UTP utility %s\n", SUPER_FLASH_RELEASE);

    GlobalConfiguration& config = GlobalConfiguration::instance();

    // Parse parameters
    while ((c = getopt(argc, argv, "c:d:f:")) != -1) {
        switch (c) {
        case 'c':
            command = optarg;
            break;
        case 'd':
            device_name = optarg;
            break;
        case 'f':
            file_name = optarg;
            break;
        default:
            print_usage();
            return 1;
        }
    }

    if (device_name.size() == 0) {
        SF_ERROR(SF_ERR_NO_TRANSPORT_SPEC);
        return 1;
    }

    SCSIGenericTransportDevice* dev = new SCSIGenericTransportDevice(device_name);
    if (dev->Open() < 0) {
        printf("Error: couldn't open device : %s\n", device_name.c_str());
        SF_ERROR(SF_ERR_OPENING_TRANSPORT);
        return 1;
    }

    if (command.size() == 0) {
        printf("No command specified.  Aborting.\n");
        return 1;
    }

    if (file_name) {
        utp_send_file(dev, command, std::string(file_name));
    } else {
        utp_send_command_with_wait(dev, command);
    }

    printf("Done.\n");

    dev->Close();
    delete dev;
    return 0;
}
