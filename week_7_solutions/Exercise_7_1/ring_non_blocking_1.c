//
// Created by chiar on 07.11.2023.
//

#include "mpi.h"
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes and rank of the process
    int size, my_rank, tag = 100;
    MPI_Status status[2];
    // starts a request for the send and receive respectively,
    // is needed to keep track of the status of the communication
    // is needed in MPI_Waitall, so that it knows when to continue / when the communication is done
    // MPI_Waitall is needed with 2 requests, because we have both a send and a receive command
    // that both need to be tracked till they're finished
    MPI_Request request[2];
    MPI_Comm_size(MPI_COMM_WORLD, &size); // gets the number of MPI processes in the communicator in which the calling MPI process belongs
    // returns a number for size, basically it the function goes into the communicater and gets the number of processes and assigns it to the
    // variable size -> is the number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // function goes into the communicator and gets the rank of the process as a number
    // and assigns it to the variable my_rank -> it goes into the communicator and says, LOL this is my rank

    // the number of processes is the size
    int n_proc = size;

    int my_sum = my_rank; // initalize with own rank

    // Initialize the values so they can be used
    int send_rank = my_rank;  // Send buffer
    int recv_rank = 0;        // Receive buffer, will be overwritten anyway, can start out with any value


    // Compute the ranks of left/right neighbours
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
    }

    // Loop over the number of processes
    //     send to right, receive from left
    //     update the send buffer
    //     update the local sum
    for (int i = 0; i < n_proc - 1; i++) {
        // send sends the value associated with send_rank
        MPI_Isend(&send_rank, 1, MPI_INTEGER, right_rank, 100, MPI_COMM_WORLD, &request[0]);
        // recv receives the value and associates it with the recv_rank?
        MPI_Irecv(&recv_rank, 1, MPI_INTEGER, left_rank, 100, MPI_COMM_WORLD, &request[1]);
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