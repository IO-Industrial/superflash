Configuration
=============

Considering the enormity of the task of supporting a single, proprietary, xml files, 
custom scripting languages and configuration files.  A superflash configuration file
contains information about the target device/board, which transport to use, and what
protocols to use.

A simple paragraph.

.. code-block:: text

    // example configuration file
    
    // declare the transport.  Superflash will look for this
    // value with "_transport" appended.  For example, if the 
    // transport="usb", superflash will look for "usb_transport".
    transport="usb"

    // protocol hint.
    protocol="sdp"

    // USB transport, using HID transfers.
    usb_transport=
    {
        transfer="HID"
        vid=0xAABB
        pid=0xCCDD
    }
    
    // SCSI generic transport (you should probably avoid this).
    sg_transport=
    {
        device="/dev/sg0"
    }

    // The device configuration.  This tells the utilities what
    // kind of device, where registers are, and other information
    // necessary to program the device.
    device =
    {
        name = "my custom development board"
        max_packet_size=1024
        dcd_addr=0x3f007000

        // RAM address ranges.  In this example, there are two
        // RAM address ranges:
        ram = ( {
                start = 0x10000000;
                size = 1G; 
                },
                { 
                start = 0x10000000;
                size = 1G; 
                }
        )   

    }

asdf

:: code-block: text
    this is a block of text

    this is more

This is regular text.
