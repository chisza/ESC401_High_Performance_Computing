CPPFLAGS=-O3 -fopenmp
LDFLAGS=-fopenmp
CC=CC

all : nbody_omp

nbody_omp : nbody_omp.o gettime.o

nbody_omp.o : nbody_omp.cpp gettime.h

gettime.o : gettime.c gettime.h

clean :
		rm -f nbody_omp.o nobody_omp gettime.o

