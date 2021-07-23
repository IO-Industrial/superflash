## References / Resources

### MSP430 / MSP432 / CC2000

- **[mspdebug](https://github.com/dlbeer/mspdebug)** - MSPDebug is a free debugger for use with MSP430 MCUs. It supports
FET430UIF, eZ430, RF2500 and Olimex MSP430-JTAG-TINY programmers, as
well as many other compatible devices. It can be used as a proxy for
gdb or as an independent debugger with support for programming,
disassembly and reverse engineering.

- **[Bootloader (BSL) for MSP low-power microcontrollers](http://www.ti.com/tool/MSPBSL)**

- **[Over-the-Air Download Code Example](http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/simple_msp432_sdk_bluetooth_plugin/1_00_00_84/exports/docs/examples/rtos/MSP_EXP432P401R/bluetooth/oad_firmware_update/README.html)** -

- **[SLAU647N: MSP Debuggers](http://www.ti.com/lit/ug/slau647n/slau647n.pdf)** - describes the use and the features of the debug probes for MSP430™ and SimpleLink™
MSP432™ microcontrollers (MCUs). 
- **[SPRABV4C: Serial Flash Programming of C2000™ Microcontrollers](http://www.ti.com/lit/an/sprabv4c/sprabv4c.pdf)** - A flash kernel is loaded using one of the ROM loaders
and is then executed and used to program the target device’s flash with the end application. This
document details one possible implementation for C2000 devices and provides PC utilities to evaluate the
solution with.
- **[cc-tool](https://github.com/scott-42/cc-tool)** cc-tool provides support for Texas Instruments CC Debugger

### AVR

- **[dfu-programmer](https://dfu-programmer.github.io/)** - dfu-programmer is a multi-platform command-line programmer for 
Atmel (8051, AVR, XMEGA & AVR32) chips with a USB bootloader supporting ISP.

- **[avrdude](https://www.nongnu.org/avrdude/)** - avr downloader/uploader

- **[Atmel AVR911: AVR Open Source Programmer](http://ww1.microchip.com/downloads/en/AppNotes/doc2568.pdf)** -

- **[AVR109: Self Programming](http://ww1.microchip.com/downloads/en/Appnotes/doc1644.pdf)** - This application note describes how an AVR with the Store Program Memory (SPM)
instruction can be configured for Self-programming. 

### iMX

- **[imx_usb_loader](https://github.com/boundarydevices/imx_usb_loader)** - i.MX/Vybrid recovery utility; This utility allows 
to download and execute code on Freescale i.MX5/i.MX6/i.MX7 and Vybrid SoCs through the Serial Download Protocol (SDP). 
Depending on the board, there is usually some kind of recovery button to bring the SoC into serial download boot mode, 
check documentation of your hardware.  The utility support USB and UART as serial link.

- **[mfgtools/uuu](https://github.com/NXPmicro/mfgtools)** - Freescale/NXP I.MX Chip image deploy tools.

- **[utp_com](https://github.com/ixonos/utp_com.git)** - utp_com tool is used to send commands to hardware via Freescale's UTP protocol.

### Other

- **[CMake Toolchain files](https://github.com/chintal/toolchains)** - Chintalagiri Shashank's CMake toolchain files for
cross compiling with gcc toolchains for msp430, propeller, and AVR.

- **[BOSSA](https://github.com/shumatech/BOSSA)** - BOSSA is a flash programming utility for Atmel's SAM family of flash-based 
ARM microcontrollers. The motivation behind BOSSA is to create a simple, easy-to-use, open source utility to replace 
Atmel's SAM-BA software. BOSSA is an acronym for Basic Open Source SAM-BA Application to reflect that goal. 

