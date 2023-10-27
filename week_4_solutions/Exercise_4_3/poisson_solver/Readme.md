What are the routines supposed to do?   

in ```void init_f```, the matrix is initialized, depending on whether it is a boundary or in the body of the matrix. Division of 1 by the set number to stay within the conditions of the equation (between 1 and 0 for x and y). The body of the matrix is initialized with the function, so that the values can then be calculated.  

in ```norm_diff```, the norm is calculated so that the tolerance can be compared with it and a stop condition can be implemented.  

in ```jacobi_step``` the iterations are done for the matrix, overwriting the old values with the new ones.
