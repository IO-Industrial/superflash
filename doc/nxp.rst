NXP/Freescale
=============

In 2015, NXP merged with Freescale to become the largest automotive semiconductor supplier.
The combined portfolio has a large number of MCUs and SoCs, from 8-bit MCUs to muti-core ARM
processors.  They offer a variety of silicon families, which use a variety of mechanisms to
be programmed.

Supported Chips
---------------

The following Freescale/NXP chipsets are currently supported by this release:

+---------------+----------------------------------------------------------------------------+
| Family        | Description / Notes                                                        |
+===============+============================================================================+
| i.MX          | i.MX5/6/7/8 series over UART (Serial) and USB                              |
+---------------+----------------------------------------------------------------------------+
| Vybrid        | VF3xx, VF5xx, and VF6xx series over UART (Serial) and USB                  |
+---------------+----------------------------------------------------------------------------+

Supported Protocols
-------------------
The following Freescale/NXP protocols are currently supported by this release:

+---------------+----------------------------------------------------------------------------+
| Protocol      | Description / Notes                                                        |
+===============+============================================================================+
| UTP           | Freescale/NXP Update Transport Protocol; using SCSI generic commands and   |
|               | currently is only supported by Linux                                       |
+---------------+----------------------------------------------------------------------------+

Freescale/NXP UTP Protocol
--------------------------

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

Using UTP Utility
^^^^^^^^^^^^^^^^^

Superflash provides a stand-alone utility, "utp," that will send UTP messages to
your hardware device.  This requires that your device be booted into the 
manufacturing Linux image, or running a version of u-boot that is compiled
with the proper options.

You should be familiar with the mfgtool and use the ucl2.xml file as a guide
for formatting commands.  The utp utility can execute commands equivalent to 
what the MfgTool does with all the CMD state="Updater" commands. 

With U-Boot properly configured, executing "ums 0" will start accepting UTP
commands:

.. code-block:: text

    Autoboot in 3 seconds
    mydevice> ums 0
    GADGET DRIVER: usb_dnl_ums
    fsl-usb-udc: bind to driver

Once the device is accepting UTP messages, you can execute a script to do your
bidding.  

Here is a practical example: to avoid having to put the device into recovery mode, you can break into 
U-Boot, load and execute a kernel from memory.  This script can load your custom 
kernel on a vybrid tower development board (you will obviously have to use the correct paths and filenames for your system):

.. code-block:: text

    #!/bin/bash

    # Load device tree at 0x81000000
    sudo ./utp -d /dev/sg0 -c "pipeaddr addr=0x81000000" -f /home/me/timesys/twr_vf600/rfs/boot/twr_vf600.dtb
    # Load kernel at 0x8100000
    sudo ./utp -d /dev/sg0 -c "pipeaddr addr=0x82000000" -f /home/me/timesys/twr_vf600/rfs/boot/uImage
    # tell u-boot to boot.
    sudo ./utp -d /dev/sg0 -c "$ bootm 0x82000000 - 0x81000000"

Note: the commands are piped to a program executing on the device.  Depending on the device, kernel, or U-Boot
version, the commands may vary.

UTP Usage
^^^^^^^^^

.. code-block:: text

    USAGE: utp -d <device> -c <command> [-f filename] 
            -d      device (example: /dev/sg0)
            -c      command to be run on target device
            -f      file to be sent to target device 

