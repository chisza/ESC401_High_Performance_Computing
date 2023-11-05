ring_mpi : ring.c
	cc -O3 -o ring_mpi ring.c

ring_non_block : ring_non_block.c
	cc -O3 -o ring_non_blocking ring_non_block.c

all : ring_mpi ring_non_block

clean:
	rm -f ring_mpi ring_non_block

