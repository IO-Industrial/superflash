# superflash

This is intended to be a universal flash loader utility for embedded SOCs and MCUs.  

Current status: 
This is currently a work in progress, and if you are looking for a flash utility, 
the utility is currently non-functional.

## Roadmap:

The initial release will support:
- Mac OSX and Linux (Ubuntu)
- Freescale/NXP SOCs, impelmenting Serial Download Protocol (SDP) and UTP protocols; and
- two buses will be implemented: USB and Serial; and
- the ability to read/write u-boot in recovery mode; and
- the ability to write a linux kernel into system memory and execute; and
- the ability to write files to the emmc/nand flash (if available).

Future releases:
- Multiple device programming at once
- AVRs and MCUs (Texas Instruments MSP430)
- JTAG support

## Building documentation
This project uses sphinx to generate documentation.  To build the documentation:
```
$ mkdir build
$ cd build
$ cmake -DBUILD_DOCS=ON ..
$ make
```

## Installing Required Packages on Ubuntu

```
sudo apt-get install libusb-1.0-0-dev
sudo apt-get install libsgutils2-dev
```

## Installing Required Packages on Mac OS-X

```
brew install libusb
```

