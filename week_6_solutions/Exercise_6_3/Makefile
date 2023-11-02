CPPFLAGS=-O3 -fopenmp
LDFLAGS=-fopenmp
CC=CC

all : nbody

nbody : nbody.o gettime.o

nbody.o : nbody.cpp gettime.h

gettime.o : gettime.c gettime.h

clean :
		rm -f nbody.o nbody gettime.o
