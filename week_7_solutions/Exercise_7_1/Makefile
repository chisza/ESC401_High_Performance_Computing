ring_mpi : ring.c
	cc -O3 -o ring_mpi ring.c

ring_non_block : ring_non_block.c
	cc -O3 -o ring_non_block ring_non_block.c

ring_non_blocking_1 : ring_non_blocking_1.c
	cc -O3 -o ring_non_blocking_1 ring_non_blocking_1.c

ring_non_blocking_2 : ring_non_blocking_2.c
	cc -O3 -o ring_non_blocking_2 ring_non_blocking_2.c

all : ring_mpi ring_non_block ring_non_blocking_1 ring_non_blocking_2

clean:
	rm -f ring_mpi ring_non_block ring_non_blocking_1 ring_non_blocking_2

