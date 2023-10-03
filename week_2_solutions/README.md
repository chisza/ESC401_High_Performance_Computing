Exercise Session 2

Exercise 2: 

Current programming environment: according to user guide, no modules are loaded at login by default. Therefore, first load the module cray. When this module is loaded -> the compiler is Cray clang 14.0.0 

Module can be swaped with module swap PrgEnv-cray PrgEnv-gnu 

Compilation of the code with make all, as the Makefile has two dependencies in all 

module list: gives a list of all currently loaded modules 

module avail: modules that are available to load on the machine (with current compiler) 

module spider: all modules that are possible, even if not with the current compiler (the list shows the module name, different versions, and a description) 

Exercise 3: 

To get different output/error files -> --error=filenamepattern, --output=filenamepattern

To get the modified squeue: squeue -o "%A %u %p %a %j %D %t %r %S %L %p"

Exercise 4:

When changing the OMP NUM THREADS to 1 and then to 10 -> time needed for calculation changes -> when only 1 thread -> 4.436 seconds, when 10 threads -> 0.4491 seconds -> with 10 threads it is around 10x faster compared to using only 1 thread

When changing -O3 to -O0 -> the time needed for the calculation is higher, the error of the calculation is bigger -> value calculated for pi is different (changes from the third decimal point onwards) 
