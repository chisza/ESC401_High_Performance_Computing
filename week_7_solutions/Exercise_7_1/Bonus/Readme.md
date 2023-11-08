What I'm doing here, so I know it later:

What I get in the end with the ```MPI_Cart_create``` and ```MPI_Cart_shift``` is a rather simple way to get the neighboring
ranks.

With ```MPI_Cart_create``` the old communicator is taken and "converted" in a new communicator that 
gives each rank coordinates in a coordinate system (1D, 2D, etc.) based on the dimensions specified.

The command has the following form:

```C
int MPI_Cart_create(
        MPI_Comm comm_old,
        int ndims,
        int *dims,
        int *periods,
        int reorder
        MPI_Comm *comm_cart
        );
```

`MPI_Comm` is the old communicator, in this case `MPI_COMM_WORLD`  
`int ndims` is an integer representing the number of dimensions of the grid; for 1D it is 1, for 2D it is 2  
`int *dims` is an integer array of size `ndims`, specifies the number of processes in each dimension; for 1D it is `dims[1]` 
or `dims[ndims]`  
`int *periods` is a logical array of size `ndims` specifying whether the grid is periodic (true &rarr; goes around) 
or not (false &rarr; does not go around) in each dimension &rarr; for each dimension, contains 1 or 0 to denote this  
`int reorder` is either 1 or 0 &rarr; ranks get reordered (1 &rarr; true) or not (0 &rarr; false) (logical)  
`MPI_Comm *comm_cart` is the new cartesian communicater &rarr; can be named as pleased

To now get the neighboring ranks, `MPI_Cart_shift` can be used:

```C
int MPI_Cart_shift(
        MPI_Comm comm,
        int direction,
        int displ,
        int *source,
        int *dest
        );
```
`MPI_Comm comm` is the communicator with a cartesian topology / structure  
`int direction` is the coordinate dimension of shift (integer) &rarr; is the index
of the dimension the shift should take place &rarr; basically row-wise or column-wise; goes from 0 to ndims-1  
`int displ` displacement > 0 &rarr; towards the bigger / higher 
rank; displacement < 0 &rarr; downward shift &rarr; towards the smaller / lower rank -> when biger than 1 &rarr; 
do not take the immediately next coordinate to affect  
`int *source` is the rank of the source process (integer) &rarr; from here we get it (`right_rank`)  
`int *dest` is the rank of the destination process (integer) &rarr; we want to send there (`left_rank`)

