CFLAGS=-O3 -fopenmp
LDFLAGS=-fopenmp
CC=cc

all : sum_omp

sum_omp : sum_omp.o gettime.o

sum_omp.o : sum_omp.c gettime.h

gettime.o : gettime.c gettime.h

clean:
	rm -f sum_omp sum_omp.o gettime.o

