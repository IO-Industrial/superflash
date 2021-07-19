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

## The envisioned usage:

```
# Scan usb bus for known devices in our database
$ superflash scan --bus=usb
No known devices found.

# Scan usb bus for known devices in our database
$ superflash scan --bus=usb
Found: NXP/Freescale Vybrid SOC (march=vybrid)

# Write a u-boot boot loader to the device;
# wait 30 seconds for the device to show up on the
# usb bus, and then download.
$ superflash load-u-boot --bus=usb --march=vybrid --usb-wait=30 --file=my-u-boot

# Read u-boot from the device and save it to a file
$ superflash save-u-boot --bus=usb --march=vybrid --usb-wait=30 --file=u-boot-backup.img
...waiting for USB
Found: NXP/Freescale Vybrid SOC (march=vybrid)
.. downloading
--march=msp430 --bus=usb --file=myfile.hex
$ superflash --march=vybrid --bus=usb --
```

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