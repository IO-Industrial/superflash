Command Line Utilities
======================

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

