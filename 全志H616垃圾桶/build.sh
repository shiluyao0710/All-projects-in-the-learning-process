#!/bin/bash

# compile the source code
gcc $1 -o "${1%.*}" \
garbage.o \
garbageClass.o \
oledShow.o \
mjpgServiceCheck.o \
sg90.o  \
socket.o \
-lwiringPi -lwiringPiDev -lpthread -lm -lcrypt -lrt \
-I /usr/include/python3.10/ -l python3.10 \
-L./ -lUARTtool

# run the compiled program
sudo -E ./"${1%.*}"
