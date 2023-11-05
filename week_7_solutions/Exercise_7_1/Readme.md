When using ´´´MPI_Ssend´´´ and ```MPI_Recv``` are used, the executable does not print anything but gets termianted
due to time limit. This is because it produces a dead lock, where the send and receive command are waiting for each other, but as it does around in a circle, neither can proceed. The output produced by running this is in [slurm-2423886.out](slurm-2423886.out).


