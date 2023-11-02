CPPFLAGS=-O3 -fopenmp
LDFLAGS=-fopenmp
CC=CC

all : nbody_both_loops

nbody_both_loops : nbody_both_loops.o gettime.o

nbody_both_loops.o : nbody_both_loops.cpp gettime.h

gettime.o : gettime.c gettime.h

clean :
		rm -f nbody_both_loops.o nbody_both_loops gettime.o
