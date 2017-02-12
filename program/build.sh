#!/bin/bash

#avr-gcc -c -mmcu=atmega32c1 can_lib.c -o can_lib.o 
#avr-gcc -c -mmcu=atmega32c1 can_drv.c -o can_drv.o
#avr-gcc -c -mmcu=atmega32c1 Timer.c -o Timer.o -std=c99

#avr-ar rcs libcan_lib.a can_lib.o
#avr-ar rcs libcan_drv.a can_drv.o
#avr-ar rcs libTimer.a Timer.o

#avr-gcc -mmcu=atmega32c1 main.c -L. -lcan_lib -lcan_drv -lTimer -o main.elf

##avr-ld -o main.elf ./can_lib.o ./can_drv.o ./Timer.o ./main.o

#avr-objcopy -R .eeprom -O ihex main.elf main.hex




#g++ -ggdb `pkg-config --cflags opencv` -o `basename main.cpp .cpp` main.cpp `pkg-config --libs opencv`


#build apriltag library

#build object files
gcc -c -I. -o apriltag.o apriltag.c -std=gnu99 -Wall
gcc -c -I. -o apriltag_quad_thresh.o apriltag_quad_thresh.c -std=gnu99
gcc -c -I. -o tag36h11.o tag36h11.c -std=gnu99

###make libraries (optional) // would need to build libcommon.a to be super useful
#ar rcs libapriltag.a apriltag.o
#ar rcs libapriltag_quad_thresh.a apriltag_quad_thresh.o
#ar rcs libtag36h11.a tag36h11.o
##build libcommon.a here
###

#build final package with opencv and apriltag options

#build by telling it all the object files
g++ -ggdb `pkg-config --cflags opencv` -o `basename main.cpp .cpp` main.cpp apriltag.o apriltag_quad_thresh.o tag36h11.o ./common/*.o `pkg-config --libs opencv`


##=###========##### UNMAINTAINED BELOW  ######========###=##
#basename options, choose 1
#g++ -c -ggdb `pkg-config --cflags opencv` -o `basename main.cpp .cpp` main.cpp `pkg-config --libs opencv`
#g++ -c -ggdb `pkg-config --cflags opencv` -o main.o main.cpp `pkg-config --libs opencv`
##

#link it all together
#ld -o mainex ./apriltag.o ./apriltag_quad_thresh.o ./tag36h11.o ./main
