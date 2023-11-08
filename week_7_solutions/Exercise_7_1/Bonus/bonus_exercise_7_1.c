#include "mpi.h"
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // The cartesian coordinate topology
    /*  int MPI_Cart_create(
            MPI_Comm comm_old, // the old communicater, in this case MPI_COMM_WORLD
            int ndims, // an integer representing the number of dimensions of the grid, in the ring case
            // 1 for 1D, can also be 2D, etc.
            int *dims, // integer array of size ndims, specifies the number of process in each dimension
            // e.g. dims = [ndims], for ring it would contain the integer value 4
            // for 4 processes in the one dimension (between the processors and around to start at first again)
            int *periods,  // a logical array of size ndims specifying whether the grid is period (true -> goes around)
            // or not (false -> does not go around) in each dimension -> for each dimension, contains 1 or 0 to denote this
            // e.g. periods = [ndims]
            int reorder,  // is either 1 or 0 -> ranks get reordered (1 -> true) or not (0 -> false) (logical)

            MPI_Comm *comm_cart // the new cartesian communicator
            );*/

    // Initialize the dimensions of the grid
    int ndims = 1;
    // Initialize the processes per dimension
    int dims[1];
    // Set the number of processes per dimension,
    // if more than one dimension, define the number of processes for every
    // dimension (goes for period as well)
    // eg dims[0]=4, dims[1] = 3 for 3 dimensions
    dims[0] = 4;
    // Initialize the periodicity
    int period[1];
    // Set the periodicity to true
    period[0] = 1;
    // Initialize the reordering
    int reorder;
    // Set the reordering to true
    reorder = 1;
    // initialize a new communicator
    MPI_Comm new_comm;

    MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, period, reorder, &new_comm);

    // Get the number of processes and the rank of the process
    int size, my_rank;
    MPI_Status status[2];
    MPI_Request request[2];
    MPI_Comm_size(new_comm, &size);
    MPI_Comm_rank(new_comm, &my_rank);

    // the number of processes is the size
    int n_proc = size;

    int my_sum = my_rank; // initalize with own rank

    // Initialize the values so they can be used
    int send_rank = my_rank;  // Send buffer
    int recv_rank = my_rank - 1;        // Receive buffer


/*   It works with this, now try with MPI_Cart_shift
 *  // Compute the ranks of left/right neighbours
    int left_rank, right_rank;
    if (my_rank == 0) {
        left_rank = size - 1;
        right_rank = my_rank + 1;
    }
    else if (my_rank == size - 1) { // count starts from 0, max number is size - 1
        left_rank = my_rank - 1;
        right_rank = 0;
    }
    else {
        left_rank = my_rank - 1;
        right_rank = my_rank + 1;
    }*/

/*    int MPI_Cart_shift(
            MPI_Comm comm, // the communicator with cartesian structure
            // in this case -> new_comm -> is the communicator that was returned
            // from MPI_Cart_create
            int direction, // coordinate dimension of shift (integer) -> just one value
            // dimension along we want to communicate -> from 0 to ndims-1??
            int displ, // displacement > 0 -> upward shift -> towards the bigger/ higher rank
            // displacement < 0 -> downward shift -> towards the smaller / lower rank
            int *source, // rank of the source process (integer) -> from here we get it
            int *dest // rank of the destination process (integer) -> here we want to send to
            );*/

    int direction = 0;
    int displ = 1;
    int left_rank, right_rank;
    MPI_Cart_shift(new_comm, direction, displ, &left_rank, &right_rank);

    // Loop over the number of processes
    //     send to right, receive from left
    //     update the send buffer
    //     update the local sum
    for (int i = 0; i < n_proc - 1; i++) {
        // recv receives the value and associates it with the recv_rank?
        MPI_Irecv(&recv_rank, 1, MPI_INTEGER, left_rank, 100, MPI_COMM_WORLD, &request[1]);
        // send sends the value associated with send_rank
        MPI_Isend(&send_rank, 1, MPI_INTEGER, right_rank, 100, MPI_COMM_WORLD, &request[0]);
        //my_sum += recv_rank;
        MPI_Waitall(2, request, status);
        my_sum += recv_rank;
        send_rank = recv_rank;

    }

    printf("I am processor %d out of %d, and the sum is %d\n", my_rank, size, my_sum);

    // Finalize the MPI environment.
    MPI_Finalize();

    return 0;
}