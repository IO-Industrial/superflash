/**
 *  @file: superflash.cpp
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
#include <getopt.h>
#include <iostream>
#include <string>
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "usb/usb_bus.h"
#include "usb/usb_device.h"
#include "usb/usb_devices.h"
#include "config/board_config.h"

using namespace std;
using namespace superflash::usb;

void print_banner(void)
{
    cout << "superflash (C) 2020 Joe Turner; All rights reserved.\n\n";
}

void print_usage(void)
{
    cout << "Usage: superflash [OPTIONS...] \n"
            "\n"
            "Where OPTIONS are\n"
            "   -h --help		Show this help\n"
            "   -s --scanusb    Scan USB buses to identify devices"
            "\n";
}

void scan_usb()
{
    printf("Scan USB bus for devices.\n");
    USB usb;
    usb.initialize();

    std::vector<USBDevice> list = usb.get_device_list();
    for (int i = 0; i < list.size(); i++) {
        USBDevice dev = list[i];
        struct sf_usb_device *tmp = usb_is_valid_device(dev);
        if (tmp != NULL)
        {
            SPDLOG_TRACE("FOUND: {:04x}:{:04x} {}", tmp->vid, tmp->pid, tmp->march_description);
            dev.dump();
        }
    }

    usb.deinitialize();
}

static const struct option long_options[] = {
    { "help", no_argument, 0, 'h' },
    { "scanusb", no_argument, 0, 's' },
    { "board", required_argument, 0, 'b' },
    { 0, 0, 0, 0 },
};

int main(int argc, char** argv)
{
    int c;
    bool scanusb = 0;
    std::string boardconf = "";

    spdlog::set_level(spdlog::level::trace);

    print_banner();
    if (argc < 2)
    {
        print_usage();
        return 0;
    }

    while ((c = getopt_long(argc, argv, "hsb:", long_options, NULL)) != -1) {
        switch (c) {
        case 'h':
            print_usage();
            return 0;
        case 's':
            scanusb = 1;
            
            break;
        case 'b':
            boardconf = optarg;
            break;
        case ':': // missing option argument
            cerr << argv[0] << ": option '-" << (char)optopt
                 << "requires an argument. aborting.\n";
            return 1;
            break;
        case '?':
        default: // invalid option
            cerr << argv[0] << ": option '-" << (char)optopt << "is invalid: aborting.\n";
            return 1;
            break;
        }
    }

    if (scanusb == true) {
        scan_usb();
    }

    if (boardconf.size())
    {
      BoardConfig bcfg;
      bcfg.load(boardconf);
    }
}
