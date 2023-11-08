ring : ring.c
	cc -O3 -ffast-math -o ring ring.c

ring_non_blocking_0 : ring_non_blocking_0.c
	cc -O3 -ffast-math -o ring_non_blocking_0 ring_non_blocking_0.c

ring_non_block : ring_non_block.c
	cc -O3 -ffast-math -o ring_non_block ring_non_block.c

ring_non_blocking_1 : ring_non_blocking_1.c
	cc -O3 -ffast-math -o ring_non_blocking_1 ring_non_blocking_1.c

ring_non_blocking_2 : ring_non_blocking_2.c
	cc -O3 -ffast-math -o ring_non_blocking_2 ring_non_blocking_2.c

all : ring ring_non_block ring_non_blocking_1 ring_non_blocking_2 ring_non_blocking_0

clean:
	rm -f ring ring_non_block ring_non_blocking_1 ring_non_blocking_2 ring_non_blocking_0

