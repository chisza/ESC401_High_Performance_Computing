CFLAGS=-O3 -fopenmp
LDFLAGS=-fopenmp
CC=cc

all : serial
       
critical_serial : serial.o

critical_serial.o : serial.c

clean : 
	rm -f serial serial.o
