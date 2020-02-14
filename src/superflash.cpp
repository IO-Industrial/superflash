#include <getopt.h>
#include <iostream>
#include "USBWrapper.h"

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
  usb.init();
  usb.enumerate_devices();
  usb.release();
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
