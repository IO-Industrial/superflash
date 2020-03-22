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
#include "usb/usb_bus.h"
#include "usb/usb_device.h"

using namespace std;

void print_banner(void) {
  cout << "superflash (C) 2020 Joe Turner; All rights reserved.\n\n";
}

void print_usage(void) {
  cout << "Usage: superflash [OPTIONS...] \n"
          "\n"
          "Where OPTIONS are\n"
          "   -h --help		Show this help\n"
          "   -s --scanusb    Scan USB buses to identify devices"
          "\n";
}

void scan_usb()
{
  USB usb;
  usb.initialize();

  std::vector<USBDevice> list = usb.get_device_list();
  for (int i=0;i<list.size();i++)
  {
    USBDevice dev = list[i];
    dev.dump();
  }

  //usb.enumerate_devices();

  usb.deinitialize();
}

static const struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {"scanusb", no_argument, 0, 's'},
    {0, 0, 0, 0},
};

int main(int argc, char **argv) {
  int c;
  bool scanusb = 0;

  print_banner();
  while ((c = getopt_long(argc, argv, "hs", long_options, NULL)) !=
         -1) {
    switch (c) {
    case 'h':
      print_usage();
      return 0;
    case 's':
      scanusb = 1;
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

  if (scanusb == true)
  {
    scan_usb();
  }
}
