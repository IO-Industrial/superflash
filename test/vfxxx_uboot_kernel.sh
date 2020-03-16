#!/bin/bash

# Load device tree at 0x81000000
sudo ./utp -d /dev/sg0 -c "pipeaddr addr=0x81000000" -f /home/g4timesys/timesys/twr_vf600/rfs/boot/twr_vf600.dtb
# Load kernel at 0x8100000
sudo ./utp -d /dev/sg0 -c "pipeaddr addr=0x82000000" -f /home/g4timesys/timesys/twr_vf600/rfs/boot/uImage-3.13-ts-armv7l
# tell u-boot to boot.
sudo ./utp -d /dev/sg0 -c "$ bootm 0x82000000 - 0x81000000"

