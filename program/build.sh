#!/bin/bash

#build object files
gcc -c -I. -o apriltag.o apriltag.c -std=gnu99 -Wall
gcc -c -I. -o apriltag_quad_thresh.o apriltag_quad_thresh.c -std=gnu99
gcc -c -I. -o tag36h11.o tag36h11.c -std=gnu99

gcc -c -I. -o ./common/g2d.o ./common/g2d.c -std=gnu99 -Wall
gcc -c -I. -o ./common/getopt.o ./common/getopt.c -std=gnu99 -Wall
gcc -c -I. -o ./common/homography.o ./common/homography.c -std=gnu99 -Wall

gcc -c -I. -o ./common/image_f32.o ./common/image_f32.c -std=gnu99 -Wall
gcc -c -I. -o ./common/image_u8.o ./common/image_u8.c -std=gnu99 -Wall
gcc -c -I. -o ./common/image_u8x3.o ./common/image_u8x3.c -std=gnu99 -Wall
gcc -c -I. -o ./common/image_u8x4.o ./common/image_u8x4.c -std=gnu99 -Wall

gcc -c -I. -o ./common/matd.o ./common/matd.c -std=gnu99 -Wall
gcc -c -I. -o ./common/pam.o ./common/pam.c -std=gnu99 -Wall
gcc -c -I. -o ./common/pjpeg-idtc.o ./common/pjpeg-idct.c -std=gnu99 -Wall

gcc -c -I. -o ./common/pnm.o ./common/pnm.c -std=gnu99 -Wall
gcc -c -I. -o ./common/string_util.o ./common/string_util.c -std=gnu99 -Wall
gcc -c -I. -o ./common/svd22.o ./common/svd22.c -std=gnu99 -Wall
gcc -c -I. -o ./common/time_util.o ./common/time_util.c -std=gnu99 -Wall
gcc -c -I. -o ./common/unionfind.o ./common/unionfind.c -std=gnu99 -Wall
gcc -c -I. -o ./common/workerpool.o ./common/workerpool.c -std=gnu99 -Wall
gcc -c -I. -o ./common/zarray.o ./common/zarray.c -std=gnu99 -Wall
gcc -c -I. -o ./common/zhash.o ./common/zhash.c -std=gnu99 -Wall
gcc -c -I. -o ./common/zmaxheap.o ./common/zmaxheap.c -std=gnu99 -Wall

g++ -c -I. -o theplayer.o theplayer.cpp -Wall -std=c++11

###make libraries (optional) // would need to build libcommon.a to be super useful
#ar rcs libapriltag.a apriltag.o
#ar rcs libapriltag_quad_thresh.a apriltag_quad_thresh.o
#ar rcs libtag36h11.a tag36h11.o
##build libcommon.a here
###

#build final package with opencv and apriltag options

#build by telling it all the object files
g++ -ggdb -I. `pkg-config --cflags opencv` -o `basename main.cpp .cpp` main.cpp apriltag.o apriltag_quad_thresh.o tag36h11.o theplayer.o ./common/*.o -lm -lpthread `pkg-config --libs opencv`


##=###========##### UNMAINTAINED BELOW  ######========###=##
#basename options, choose 1
#g++ -c -ggdb `pkg-config --cflags opencv` -o `basename main.cpp .cpp` main.cpp `pkg-config --libs opencv`
#g++ -c -ggdb `pkg-config --cflags opencv` -o main.o main.cpp `pkg-config --libs opencv`
##

#link it all together
#ld -o mainex ./apriltag.o ./apriltag_quad_thresh.o ./tag36h11.o ./main
