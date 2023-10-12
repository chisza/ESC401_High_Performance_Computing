The code produces always the same sum but with different times:

O0: sum=10022429073.341873
Computed in 5.979 seconds

O1: sum=10022429073.341873
Computed in 1.158 seconds

O2: sum=10022429073.341873
Computed in 1.061 seconds

O3: sum=10022429073.341873
Computed in 1.072 seconds

For the flags -O1, -O2, -O3 the difference was relatively small, though -O0 takes around 6 times longer to compile

I don't really know other ways to get timing.

For the different flags, different optimizations were used.

To make it even faster, other flags could be used or it could be parallelized with either MPI or OpenMP, for example

To parallelize the sum_omp.c file ,I inserted the line before the for loop.
