CPPFLAGS=-O3 -ffast-math -mavx2 -fopenmp
LDFLAGS=-fopenmp
CC=CC

all: init.o io.o jacobi.o main gettime.o
init.o: init.cpp init.h
io.o: io.cpp io.h
jacobi.o: jacobi.cpp jacobi.h
main: init.o io.o jacobi.o gettime.o
gettime.o : gettime.c gettime.h
clean: 
	rm -f main init.o io.o jacobi.o gettime.o
