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
#include <unistd.h>
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include "config/board_config.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/spdlog.h"
#include "usb/usb_bus.h"
#include "usb/usb_device.h"
#include "usb/usb_devices.h"
#include "protocols/sdp.h"
#include "portable.h"
#include "arch/imx/imx_hab.h"

using namespace std;
using namespace superflash::usb;

bool g_wait = false;

void print_banner(void)
{
    cout << "superflash (C) 2020 Joe Turner; All rights reserved.\n\n";
}

void print_usage(void)
{
    cout << "Usage: superflash <command> [<args>]> \n\n"
            "\n"
            "These are common superflash commands used in various situations:\n\n"
            "   scan            Scan USB buses to identify devices\n"
            "   load            Load file into memory (and execute)\n"
            "   save            Read data from device and save to a file\n"
            "   info            provide info about the device\n"
            "   help            provides more detailed healp about a command\n"
            "\n";
}

void help_scan(void)
{
    cout << "SCAN:\n"
         << "    Scan the USB bus for supported devices.\n\n"
         << "SYNOPSIS:\n"
         << "    superflash scan [--wait]\n\n"
         << "OPTIONS:\n"
         << "        -w, --wait\n"
         << "            Wait until device is found, before exiting.\n\n";
}

int scan_usb(int argc, char **argv)
{
    int c;

    static const struct option long_options[] = {
        { "wait", no_argument, 0, 'w' },
        { 0, 0, 0, 0 },
    };

    while ((c = getopt_long(argc, argv, "w", long_options, NULL)) != -1) {
        switch (c) {
        case 'w':
            printf("Waiting for device.\n");
            g_wait = true;
            break;
        case ':': // missing option argument
            cerr << argv[0] << ": option '-" << (char)optopt
                 << "requires an argument. aborting.\n";
            return 1;
            break;

        default: // invalid option
            cerr << argv[0] << ": option '-" << (char)optopt << "is invalid: aborting.\n";
            return 1;
            break;
        }
    }

    spdlog::info("Scan USB bus for devices.");
    USB usb;
    usb.initialize();
    int retries = 1;

    while (retries > 0 || g_wait) {
        std::vector<USBDevice> list = usb.get_device_list();
        for (int i = 0; i < list.size(); i++) {
            USBDevice dev = list[i];
            struct sf_usb_device* tmp = usb_is_valid_device(dev);
            if (tmp != NULL) {
                SPDLOG_TRACE("FOUND: {:04x}:{:04x} {}", tmp->vid, tmp->pid, tmp->march_description);
                dev.dump();
                usb.deinitialize();
                return 0;
            }
        }
        retries--;
        usleep(25000);
    }

    spdlog::info("Found 0 supported devices.\n");
    usb.deinitialize();
    return 0;
}

static int do_command(USBDevice &dev, unsigned char *cmd, int cmd_size, int retry)
{
	int last, err = -4;

	SPDLOG_TRACE("sending command cmd={:02x} {:02x} {:02x} {:02x}", cmd[0], cmd[1],cmd[2],cmd[3]);
	while (retry) {
		err = dev.transfer_hid(1, (unsigned char *)cmd,
				cmd_size, 
                &last,
                0, 
                1024
                );
		if (err)
			spdlog::error("{} err={}, last_trans={}", __func__, libusb_error_name(err), last);
		if (!err)
			return 0;

		retry--;
	}

	return err;
}

static int do_response(USBDevice &dev, int report, unsigned int *result)
{
	unsigned char tmp[64] =  { 0 };
	int last_trans, err;

	err = dev.transfer_hid(report, tmp, sizeof(tmp), &last_trans, 0, 1024);
	SPDLOG_TRACE("report ({}) in err={}, last_trans={}  {:02x} {:02x} {:02x} {:02x}",
			report, err, last_trans, tmp[0], tmp[1], tmp[2], tmp[3]);

	/* At least 4 bytes required for a valid result */
	if (last_trans < 4)
		return -1;

	/*
	 * Most results are symetric, but likely are meant to be big endian
	 * as everything else is...
	 */
	*result = BE32(*((unsigned int*)tmp));

	return err;
}


// superflash info
int info(int argc, char **argv)
{
    SPDLOG_TRACE("info.");

    spdlog::info("Scan USB bus for devices.");
    USB usb;
    usb.initialize();
    int retries = 1;
    unsigned int hab_security;
    struct sdp_command cmd;

    while (retries > 0 || g_wait) {
        std::vector<USBDevice> list = usb.get_device_list();
        for (int i = 0; i < list.size(); i++) {
            USBDevice dev = list[i];
            struct sf_usb_device* tmp = usb_is_valid_device(dev);
            if (tmp != NULL) {
                spdlog::info("FOUND: {:04x}:{:04x} {}", tmp->vid, tmp->pid, tmp->march_description);
                spdlog::info("  Max USB transfer size : {}", tmp->max_transfer);
                spdlog::info("  DCD Address           : 0x{:x}", tmp->dcd_addr);
                spdlog::info("  RAM start address     : 0x{:x}", tmp->ram_start);
                if (!dev.open_device())
                {
                    spdlog::error("Could not open device vid={:04x} pid={:04x}", tmp->vid, tmp->pid);
                    return 1;
                };
                
                cmd.fill_status();
                int err = do_command(dev, (uint8_t *)&cmd, sizeof(cmd), 5);
                err = do_response(dev, 3, &hab_security);

	            spdlog::info("HAB security state: {} (0x{:08x})", hab_security == HAB_ENABLED ?
			        "production mode" : "development mode", hab_security);

                //SPDLOG_TRACE("sending command cmd={:02x} {:02x} {:02x} {:02x}\n", cmd[0], cmd[1],cmd[2],cmd[3]);
                dev.close_device();
                usb.deinitialize();
                return 0;
            }
        }
        retries--;
        usleep(25000);
    }

    spdlog::info("Found 0 supported devices.\n");
    usb.deinitialize();
    return 0;
}

int load_uboot_only(char *filename)
{
    SPDLOG_TRACE("Load u-boot file {} and execute u-boot.", filename);
    return 0;
}

// superflash load u-boot
// Load u-boot into device and jump.
// Load a file into 
int load(int argc, char **argv)
{
    SPDLOG_TRACE("CMD: load [load file (and execute)] argc={}.", argc);
    if (argc == 2)
    {
        // future: lookup options from configuration files in ~/.superflash
        spdlog::error("autoloading not supported yet.");
        return 1;
    }

    // if only one argument is supplied it must be a file
    // ex: superflash load u-boot.imx.  We are going to pull the 
    // address from the u-boot image.
    if (argc == 3)
    {
        return load_uboot_only(argv[2]);
    }


    return 0;
}

int save(int argc, char **argv)
{
    SPDLOG_TRACE("save");
    return 0;
}

int verify(int argc, char **argv)
{
    SPDLOG_TRACE("verify.");
    return 0;
}

int help(int argc, char **argv)
{
    SPDLOG_TRACE("CMD: help argc={}.", argc);

    if (argc == 2)
    {
        cout << "HELP:\n"
            << "    Displays information about commands, operations, and options.\n\n"
            << "SYNOPSIS:\n"
            << "    superflash help <operation>\n"
            << "    superflash help scan\n"
            << " \n"
            << "OPTIONS:\n"
            << "        scan\n"
            << "            scan usb bus for devices.\n\n";
    }
    else
    {
        if (argc==3)
        {
            if (strcmp("scan", argv[2]) == 0) help_scan();
        }
        else
        {
           spdlog::error("Unknown command; try 'superflash help'");
        }
    }

    return 0;
}

struct _jump_table {
    const char* command;
    int (*function)(int ac, char** av);
};

struct _jump_table jump_table[] = {
    { "scan", scan_usb },
    { "save", save },
    { "info", info },
    { "verify", info },
    { "load", load },
    { "help", help },
    { "", NULL }
};

int execute_jump_table(int ac, char** av)
{
    for (int i = 0; *jump_table[i].command; i++) {
        if (strcmp(av[1], jump_table[i].command) == 0) {
            return jump_table[i].function(ac, av);
        }
    }

    spdlog::error("unrecognized command : {}", av[1]);
    return 1;
}

int main(int argc, char** argv)
{
    std::string boardconf = "";

    spdlog::set_level(spdlog::level::trace);

    print_banner();
    if (argc < 2) {
        print_usage();
        return 0;
    }

    return execute_jump_table(argc, argv);

}

