The terminal output can be found in [slurm-244133.out](slurm-2441333.out)  
Instead of a "result" or printed output from the C++ script run, a text report with 
performance statistics are shown. This is the same output as in 
[RUNTIME.rpt](nbody+25928-8639969s/rpt-files/RUNTIME.rpt)

Besides this, running the executable also produces a folder ([nbody+25928-8639969s](nbody+25928-8639969s).
In this folder, several subdirectories exist:

* [rpt-files](rpt-files) with a copy of the text report
* [ap2-files](ap2-files) with the processed data files, in a special format that is
required for the analysis
* [xf-files](xf-files) with the raw data files
* there can be, if the code is run with MPI, one or more MPICH_RANK_ORDER_FILE files, that
contain suggestions for optimizing MPI rank placement

The most CPU time is spent in the function `forces`, which is the function doing the most
work in the main body of the program. Within the `forces` function, most time is spent in 
line 23, coming to 63.4% corresponding to `plist[i].ax += dx * ir3;`. Though most of the
time is probably rather spent in line 22 with `auto ir3 = 1 / (r*r*r);`, line 23 is
shown in the text report due to how sampling is performed, maybe also due to the optimization,
which is allowed to do weird thing with the code, including swapping lines. 
This line 22 would require more time, as division and the square root calculation require more time than + - *.

From Table 1, we can see which function, if we have several, in the main body of the 
program requires most of the time. In Table 2, we get a more detailed listing with the
line numbers of the places where the most time is spent during the execution of the function.
From "Observation: MPI utilization", I think that when more than one rank is used for the
execution, suggestions are made on how to improve the MPI implementation.
This could help us improve our code further.

