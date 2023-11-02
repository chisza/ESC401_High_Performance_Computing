When running the programming on 1, 2, 3, 4 threads -> time needed goes down a bit over 10 s in total

When running on more threads, going all the way up to 128 -> time goes up again (probably because the work that is given for execution does not really suffice to generate a real speedup compared to the work/time needed for setting up the forking over all possible threads?)
