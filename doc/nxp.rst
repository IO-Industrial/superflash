NXP/Freescale
=============

In 2015, NXP merged with Freescale to become the largest automotive semiconductor supplier.
The combined portfolio has a large number of MCUs and SoCs, from 8-bit MCUs to muti-core ARM
processors.  They offer a variety of silicon families, which use a variety of mechanisms to
be programmed.

Long ago, Freescale provided MFGTools / sb_loader (Windows only) binaries to flash empty devices 
leveraging the USB recovery feature of the i.MX family.  In 2010, Boundary Devices developed its 
own Linux-based tool called imx-usb-loader, with the following features:

- Loading bootloader / recovering devices over USB recovery (SDP) protocol
- Loading any binary in RAM over USB for flashing purposes

In 2018, NXP decided to unify their tools, creating a new one from scratch called UUU.  However,
it doesn't support some legacy devices.  It is important to note that Boundary Devices no longer 
actively maintains the imx-usb-loader project.



Vybrid Family
^^^^^^^^^^^^^
Vybrid SoCs are asymmetrical multiprocessors with ARM cores.  There are several variants, but 
all come with an ARM Cortex-A5.  The variants come with or without an additional ARM Cortex-M4
with shared memory.

Supported Protocols
-------------------
The following Freescale/NXP protocols are currently supported by this release:

+---------------+----------------------------------------------------------------------------+
| Protocol      | Description / Notes                                                        |
+===============+============================================================================+
| UTP           | Freescale/NXP Update Transport Protocol; using SCSI generic commands and   |
|               | currently is only supported by Linux.  (Older devices)                     |
+---------------+----------------------------------------------------------------------------+
| SDP           | Freescale/NXP Serial Download Protocol; via USB                            |
+---------------+----------------------------------------------------------------------------+

Freescale/NXP UTP Protocol
^^^^^^^^^^^^^^^^^^^^^^^^^^

The Freescale Update Transport Protocol (UTP) is a protocol
defined for delivering device update commands over USB, carried
over Bulk Only Transport (BOT) of the Mass Storage Class (MSC).  

On the host side, it is implemented on top of an MSC stack that
supports vendor specific SCSI commands. The UTP messages are implemented 
using a vendor-specific 16-byte SCSI Command Descriptor Block (CDB). 
The extended UTP reply is returned through a standard SCSI REQUEST_SENSE 
command.

This was one of the primary methods of programming devices with 
Freescale's manufacturing tool (mfgtool), and appears to be still 
supported.

With the utp utility, you can manipulate the board and pipe bash commands 
from your terminal without having to actually type anything directly on the 
device. 

Freescale/NXP SDP Protocol
^^^^^^^^^^^^^^^^^^^^^^^^^^

The Freescale/NXP Serial Download Protocol (SDP) was adopted for the iMX line of chips.
Each device is somewhat unique in how to enable the device to be able to enable/intepret
SDP.  Sometimes it is fuses, or jumpers.  Some devices will allow programming over CAN, USB, 
or Serial UART.  These can alse be enabled/disabled during production flashing.