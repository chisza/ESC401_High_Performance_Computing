Exercise Session 2

Exercise 2: 
Current programming environment: according to user guide, no modules are loaded at login by default. Therefore,
first load the module cray. When this module is loaded -> the compiler is Cray clang 14.0.0 
Module can be swaped with module swap PrgEnv-cray PrgEnv-gnu 

Compilation of the code with make all, as the Makefile has two dependencies in all 

module list: gives a list of all currently loaded modules 
module avail: modules that are available to load on the machine (with current compiler) 
module spider: all modules that are possible, even if not with the current compiler (the list shows the module
name, different versions, and a description) 

Exercise 3: 
To get different output/error files -> --error=filenamepattern, --output=filenamepattern

To get the modified squeue: squeue -o "%A %u %p %a %j %D %t %r %S %L %p" 
