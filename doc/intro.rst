Introduction
============

Each semiconductor manufacturer supplies tools for
flashing/programming their parts.  As a result, professionally
developing for multiple MCUs, MPUs, and SOCs requires multiple 
programmers, debuggers, IDEs, applications, and sometimes,
hacked together applications.  Over time, many of these tools
become hard to find, especially after parts reach end-of-life.

Worse yet, companies that make the IDEs, programmers, etc., will 
force you to purchase upgraded licenses in order to continue
programming devices.

Even within a manufacturer’s own semiconductor lineup, different
chips will require different utilities, configuration files, and
setups to flash their chips.

Some require bizarre and poorly documented scripting languages, 
sometimes in random formats.

Enough already.

Envisioned Use Cases
--------------------

Superflash is ultimately envisioned as a set standard of 
utilities to program/flash embedded System On Chip (SOCs),
embedded development boards, AVRs, MCUs, flash, EEPROMs
and more.

Ultimately, this project is envisioned to be used in the following
scenarios:

- Initial development, board bring up and development; and
- RMA/returns - unbricking devices for diagnostics; and
- Continous Integration and testing.

Basic Concepts
--------------

Given the herculean task of supporting a multitude of chips,
development systems, programmers, debuggers, file formats, and
algorithms, it's necessary to generalize the components
of the system.

**Target board (or chip)**.  This can be a standalone chip
programmed or development board, and may support multiple
avenues for programming (i.e., serial programming as well as
JTAG).  Each board (or family of chips) has a configuration file
that tells the utilities necessary information on what the
device is, how to find it, memory addresses, capabilities, etc.

**Transport**.  This is a generalization of how the bits are
Transported from the host into the target board, and refers to
the connection between the host and the target board/device.  
It may be a built in USB-serial with a USB cable, a simple serial
cable, raw JTAG, a stand-alone JTAG programmer, or specialized
programmer provided by a manufacturer.

**Programming protocol/algorithm**.  A target device may require
a specialized protocol to successfully program a bootloader onto a 
device.  This includes Freescale/NXP's Serial Download
Protocol (SDP), or something a generic as JTAG.

**Firmware files**.  These are the files that are to be
transferred into the target board/device.  Each manufacturer
supports different file formats (Intel Hex, Motorola S Record, 
ELF (Executable and Linkable Format), etc.).

What You Will Need
------------------

You will need to have some understanding of how your embedded device/target board
works.  You will also have to have the required cables.  In some cases schematics
may be helpful, as sometimes jumpers can be set to enable flash loading.

You will need to build the software required, whether it be a monolithic executable,
or the linux trifecta -- u-boot, device tree, and linux kernel.

Unfortunately, these are unique to the target board you are using.

Supported Protocols
-------------------

The following protocols and transports are supported in this
release:

+---------------+--------------+-------------------------------------------------------------+
| Protocol      | Transports   | Notes                                                       |
+===============+==============+=============================================================+
| Freescale UTP | SCSI generic | Freescale Update Transport Protocol (UTP) is only           |
|               |              | supported via SCSI generic commands (Linux ONLY).           |
+---------------+--------------+-------------------------------------------------------------+
| Freescale SDP | USB HID/BULK | Freescale Serial Download Protocol (SDP) is only            |
|               |              | supported via USB.                                          |
+---------------+--------------+-------------------------------------------------------------+

Acknowledgements
----------------

The UTP protocol is not well documented and very little is in
the public domain regarding the actual protocol.  This code
draws heavily from idioms from Digitalist Group's/Ixonos PLC's
utp_com utility and Freescale's uuc deamon.  The code was tested
on a Vybrid SOC development board and customized embedded
product based on the Vybrid SOC.
