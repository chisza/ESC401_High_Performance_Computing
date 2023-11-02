CFLAGS=-O3 -fopenmp
LDFLAGS=-fopenmp
CC=cc

all : second_loop_serial
       
second_loop_serial : second_loop_serial.o

second_loop_serial.o : second_loop_serial.c

clean : 
	rm -f second_loop_serial second_loop_serial.o
