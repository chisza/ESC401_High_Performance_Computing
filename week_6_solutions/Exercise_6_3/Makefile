CPPFLAGS=-O3
CC=CC

all : nbody_serial

nbody_serial : nbody_serial.o gettime.o

nbody_serial.o : nbody_serial.cpp gettime.h

gettime.o : gettime.c gettime.h

clean :
		rm -f nbody_serial.o nbody_serial gettime.o
