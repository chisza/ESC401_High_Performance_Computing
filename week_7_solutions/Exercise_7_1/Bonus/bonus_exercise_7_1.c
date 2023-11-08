#include "mpi.h"
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Initialize the dimensions of the grid
    int ndims = 1;
    // Initialize the processes per dimension -> array with size ndims
    int dims[1];
    // Set the number of processes per dimension,
    // if more than one dimension, define the number of processes for every
    // dimension (goes for period as well)
    // eg dims[0]=4, dims[1] = 3 for 3 dimensions
    dims[0] = 4;
    // Initialize the periodicity
    int period[1];
    // Set the periodicity to true for each dimension
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

    int direction = 0; // go row-wise and stay in the row
    int displ = 1; // affect the immediately left and right rank
    // initalize the left and right rank -> source and dest
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