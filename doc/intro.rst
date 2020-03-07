Introduction
============

Superflash is ultimately envisioned as a set standard of utilities to program/flash 
embedded System On Chip (SOCs), embedded development boards, AVRs, MCUs, flash, EEPROMs
and more.

Basic Concepts
--------------

Given the hurculean task of supporting a multitude of chips, development systems, programmers,
debuggers, file formats, and algorithms, it's necessary to generalize the components
of the system.

**Target board (or chip)**.  This can be a standalone chip programmed or development board,
and may support multiple avenues for programming (i.e., serial programming as well as 
JTAG).  Each board (or family of chips) has a configuration file that tells the
utilities necessary information on what the device is, how to find it, memory 
addresses, capapbilities, etc.

**Transport**.  This is a generalization of how the bits are transported
from the host into the target board, and refers to the connection between the host and
the target board/device.  It may be a built in USB-serial with a USB cable, a simple serial
cable, raw JTAG, a stand-alone JTAG programmer, or specialized programmer provided by a 
manufacturer.

**Programming protocol/algorithm**.  A target device may require a specialized protocol
to successfully program a bootloader into a device.  This includes Freescale/NXP's 
Serial Download Protocol (SDP), or something a generic as JTAG.

**Firmware files**.  These are the files that are to be transferred into the target
board/device.  Each manufacturer supports different file formats (Intel Hex, Motorola S Record,
ELF (Executable and Linkable Format), etc.).




