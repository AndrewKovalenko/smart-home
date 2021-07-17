#!/bin/bash
esptool.py --port /dev/tty.usbserial-0001 --baud 460800 write_flash --flash_size=detect 0 ~/Downloads/esp8266-1m-20210618-v1.16.bin