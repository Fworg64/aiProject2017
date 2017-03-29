#!/bin/bash

#build object files
gcc -c -I. -o apriltag.o apriltag.c -std=gnu99 -Wall
gcc -c -I. -o apriltag_quad_thresh.o apriltag_quad_thresh.c -std=gnu99
gcc -c -I. -o tag36h11.o tag36h11.c -std=gnu99

g++ -c -I. -o theplayer.o theplayer.cpp -Wall -std=c++11

###make libraries (optional) // would need to build libcommon.a to be super useful
#ar rcs libapriltag.a apriltag.o
#ar rcs libapriltag_quad_thresh.a apriltag_quad_thresh.o
#ar rcs libtag36h11.a tag36h11.o
##build libcommon.a here
###

#build final package with opencv and apriltag options

#build by telling it all the object files
g++ -ggdb `pkg-config --cflags opencv` -o `basename main.cpp .cpp` main.cpp apriltag.o apriltag_quad_thresh.o tag36h11.o theplayer.o ./common/*.o -I. -lm -lpthread `pkg-config --libs opencv`


##=###========##### UNMAINTAINED BELOW  ######========###=##
#basename options, choose 1
#g++ -c -ggdb `pkg-config --cflags opencv` -o `basename main.cpp .cpp` main.cpp `pkg-config --libs opencv`
#g++ -c -ggdb `pkg-config --cflags opencv` -o main.o main.cpp `pkg-config --libs opencv`
##

#link it all together
#ld -o mainex ./apriltag.o ./apriltag_quad_thresh.o ./tag36h11.o ./main
