CFLAGS=-O3 -fopenmp
LDFLAGS=-fopenmp
CC=cc

all : reduction_serial
       
reduction_serial : reduction_serial.o

reduction_serial.o : reduction_serial.c

clean : 
	rm -f reduction_serial reduction_serial.o
