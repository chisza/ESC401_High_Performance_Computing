CFLAGS=-O3
CC=cc

all : cpi cpi_mpi

cpi : cpi.o gettime.o

cpi_mpi : cpi_mpi.o gettime.o

cpi.o : cpi.c gettime.h

cpi_mpi.o : cpi_mpi.c gettime.h

gettime.o : gettime.c gettime.h

clean:
	rm -f cpi cpi.o gettime.o cpi_mpi cpi_mpi.o
