When using ```MPI_Ssend``` and ```MPI_Recv``` are used, the executable does not print anything but gets termianted
due to time limit. This is because it produces a dead lock, where the send and receive command are waiting for each other, 
but as it does around in a circle, neither can proceed. The output produced by running the
blocking version ([ring.c](ring.c)) is in [slurm-2423886.out](slurm-2423886.out).

The version for ```MPI_Ssend``` and ```MPI_Recv``` where a deadlock is avoided is in [ring_non_blocking_0.c](ring_non_blocking_0.c)
It avoids the problem of a deadlock, because no rank is waiting for a signal that never comes because all the other ranks 
are waiting too. Instead, e.g. rank 2: it is even, so it send in the even-block. It receives the recv_rank from rank 1, which
is currently doing nothing, and send its rank to rank 3, which is also not doing anything. It is not optimal, because
not all ranks work in parallel.

_Please ignore the file [ring_non_block.c](ring_non_block.c). I kept ths file to know what not to do and because it helps
me to understand some aspects of the procedure; it is a deadlock._

The corrected file for the non blocking implementation the file is first the file [ring_non_blocking_1.c](ring_non_blocking_1.c) 
for the ```MPI_Isend```-```MPI_Irecv```-```MPI_Waitall``` version, 
for ```MPI_Irecv```-```MPI_Isend```-```MPI_Waitall``` it is file [ring_non_blocking_2.c](ring_non_blocking_2.c).

These methods are better, because they do not need to wait or block till the communication happened,
it can communicate in the background. The ```MPI_Waitall``` at the end of each for loop makes sure, that the processes are done
and then the variable send_rank can be updated for the next round. Further they are way less verbose, requiring less
code and no repetition of ```send_rank = recv_rank;``` and ```my_sum += recv_rank;```. Besides that, it takes more time 
to execute with the ```MPI_Ssend``` and ```MPI_Recv``` routine, as not all ranks can do work in parallel.
