NXP/Freescale
=============

In 2015, NXP merged with Freescale to become the largest automotive semiconductor supplier.
The combined portfolio has a large number of MCUs and SoCs, from 8-bit MCUs to muti-core ARM
processors.

Supported Chips
---------------

+---------------+----------------------------------------------------------------------------+
| Family        | Description / Notes                                                        |
+===============+============================================================================+
| i.MX          | i.MX5/6/7/8 series over UART (Serial) and USB                              |
+---------------+----------------------------------------------------------------------------+
| Vybrid        | VF3xx, VF5xx, and VF6xx series over UART (Serial) and USB                  |
+---------------+----------------------------------------------------------------------------+


iMX ARM-based (including Vybrid)
--------------------------------

Device Configuration Data (DCD)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Upon reset, the device uses the default register values for all peripherals in the system. 
However, these settings typically are not ideal for achieving optimal system performance 
and there are even some peripherals that must be configured before they can be used. The 
DCD is configuration information contained in a Program Image, external to the ROM that 
the ROM interprets to configure various peripherals on this device. Some components 
such as SDRAM require some sequence of register programming as part of configuration 
before it is ready to be used. The DCD feature can be used to program DDRMC registers 
to the optimal settings.

The ROM determines the location of the DCD table based on information located in the 
Image Vector Table (IVT). See Image Vector Table and Boot Data for more details. The 
DCD table shown below is a big endian byte array of the allowable DCD commands. The 
maximum size of the DCD limited to 3028 bytes.

Sample H5
^^^^^^^^^

Sample H6
"""""""""