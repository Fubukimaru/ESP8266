#!/bin/bash
#Conecta el 0 al ground para flashear
PORT=/dev/ttyUSB1

#python2 esptool.py -p $PORT erase_flash 0x7e000
python2 esptool.py -p $PORT write_flash 0x00000 firmware/blank512k.bin
