When using ```MPI_Ssend``` and ```MPI_Recv``` are used, the executable does not print anything but gets termianted
due to time limit. This is because it produces a dead lock, where the send and receive command are waiting for each other, 
but as it does around in a circle, neither can proceed. The output produced by running this is in [slurm-2423886.out](slurm-2423886.out).

Please ignore the file [ring_non_block.c](ring_non_block.c). I kept ths file to know what not to do, it is a deadlock.

The corrected file for the non blocking implementation the file is first the file [ring_non_blocking_1.c](ring_non_block_1.c) 
for the Isend-Irecv-Waitall version, for Irecv-Isend-Waitall it is file [ring_non_blocking_2.c](ring_non_block_2.c).

These methods are better, because they do not need to wait or block till the communication happened,
it can communicate in the background. The Waitall at the end of each for loop makes sure, that the processes are done
and then the variable send_rank can be updated for the next round.
