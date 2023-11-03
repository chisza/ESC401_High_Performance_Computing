Parallelizing the first loop without the privat clause led to race condtion.

When parallelizing the second for loop exactly like the first loop -> get race condition -> running on different amount of
threads gives different number of 0s, but never the correct number -> resolve by reduction directive

I inserted the atomic and critical statement right before the updating happens, so that the if-loop can be done in parallel, and only the updating of the variable is done one by one.
