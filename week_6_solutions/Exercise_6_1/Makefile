CFLAGS=-O3 -fopenmp
LDFLAGS=-fopenmp
CC=cc

all : critical_serial
       
critical_serial : critical_serial.o

critical_serial.o : critical_serial.c

clean : 
	rm -f critical_serial critical_serial.o
