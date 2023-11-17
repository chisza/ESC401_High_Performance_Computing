In the folder [poisson_MPI_original_files](poisson_MPI_original_files) are the original unmodified 
files for the exercise.

In the folder [Version_I](Version_I) are the modified files, with the decomposition in one direction and the 
remnant added to the last process, halocommunication with a non-blocking MPI communication. I tried to modify
the files so that they also run in serial, but it didn't work out, so I left it at a working parallel version.

In the folder [Version_III](Version_III) I tried to make it work with the cartisian coordinates.