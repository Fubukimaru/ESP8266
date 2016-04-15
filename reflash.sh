#!/bin/bash
#Conecta el 0 al ground para flashear
PORT=/dev/ttyUSB0
#IMAGE=firmware/nodemcu-master-9-modules-2016-02-12-21-11-57-float.bin
IMAGE=firmware/nodemcu-master-12-modules-2016-03-05-16-44-03-float.bin
#IMAGE=firmware/ESP-Default.bin

python2 esptool.py -p $PORT write_flash 0x00000 $IMAGE #0x7E000 firmware/blank.bin

