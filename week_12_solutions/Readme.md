Exercise 1

OpenMP is faster than OpenACC, there is no linear trend in the timings, N=400 and N=700 
take longer than all the others, on the GPU there seems to be an overhead from copying the data on the GPU memory

Exercise 2

Blur: The Host version is the fastest, but the naive and nocopies version show a difference in timing, nocopies is
faster, probably due to the overhead from copying the data.

Dot: Also here GPU is slower than CPU, probably due to overhead from the copying from data to the GPU