CPPFLAGS=-O3 -fopenmp
LDFLAGS=-fopenmp
CC=CC

all : nbody gettime.o

nbody : nbody.o

nbody.o : nbody.cpp

gettime.o : gettime.c gettime.h

clean :
		rm -f nbody.o nbody gettime.o