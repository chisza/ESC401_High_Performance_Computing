#include "mpi.h"
#include <stdio.h>
#include "init.h"

int start_MPI(int* my_rank, int* size){
	printf("Setting MPI environment\n");
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD,size);
	MPI_Comm_rank(MPI_COMM_WORLD,my_rank);

	return 0;
}

int close_MPI(){
	MPI_Finalize();
	return 0;
}

int mpi_get_domain(int nx, int ny, int my_rank, int size, int* min_x, int* max_x, int* min_y, int* max_y){
	/*
	define corners or local domains
	*/
    // get the local nx for each rank
    // divide the number of dots in x direction by the number of processes
    // get only integers
    int nx_local = nx / size;
    // get the remainder of the division
    int remainder = nx % size;

    // *min_x is a pointer to the value for min_x -> calculate this with the rank and the calculated "distance"
    *min_x = my_rank * nx_local;
    // *max_x is a pointer to the value for max_x -> calculate this starting from the value min_x pointed at by
    // *min_x and add the "distance" nx_local to it
    *max_x = *min_x + nx_local;

    // check, if the current rank is the last one
    // if yes, then add the remainder to make sure, that all dots are part of one process
    // the maximum number of processes is size - 1, because it starts at 0
    if (my_rank == size - 1) {
        *max_x += remainder;
    }

    // with this first method, no splitting along the y-axis is done, therefore the given values are used
    // and min_y is initialized with 0
    *min_y = 0;
    *max_y = ny;

    printf("in mpi_get_domain() in mpi_module.cpp,  define corners of the local domains\n");

	printf("I am rank %d and my domain is: xmin, xmax, ymin, ymax: %d %d %d %d\n",my_rank,*min_x,*max_x,*min_y,*max_y);
	return 0;
}

int halo_comm(params p, int my_rank, int size, double** u, double* fromLeft, double* fromRight){


    // initialize the ranks
    int left_rank, right_rank;

    if (my_rank == 0) {
        right_rank = my_rank + 1;
        // give a dummy value for ranks that are not needed -> do not go around
        left_rank = - 1;
    }
    else if (my_rank == size-1) {
        right_rank = -1;
        left_rank = my_rank - 1;
    }
    else {
        right_rank = my_rank + 1;
        left_rank = my_rank - 1;
    }
    printf("my rank : %d right rank : %d left rank : %d\n", my_rank, right_rank, left_rank);

	
	/*this function, vectors fromLeft and fromRight should be received from the neighbours of my_rank process*/
	/*if you want to implement also cartesian topology, you need fromTop and fromBottom in addition to fromLeft a
	nd fromRight*/

	for (int j=0;j<(p.ymax - p.ymin);j++) {
        // vectors that should be received
        // initialized to value for each element
        // gets overwritten by receive?
        fromLeft[j] = 0;
        fromRight[j] = 0;
    } //initialize fromLeft and fromRight

    // initialize what should be sent
    // define the columns
    double* column_to_right = new double [p.ymax - p.ymin];
    for (int j=0;j<(p.ymax - p.ymin);j++) column_to_right[j] = u[p.xmax - p.xmin - 1][j];
    double* column_to_left = new double [p.ymax - p.ymin];
    for (int j=0;j<(p.ymax - p.ymin);j++) column_to_left[j] = u[0][j];
    printf("&column_to_left : %g", *column_to_left);

    MPI_Request request[4];
    for (int i=0;i<4;i++) {request[i] = MPI_REQUEST_NULL;}
    if (left_rank != -1) {
        // send to the left and right
        // column_to_left -> is the address of the first element -> go left of all the elements that we want
        // and send them -> is not a value
        MPI_Isend(column_to_left, p.ymax - p.ymin, MPI_DOUBLE, left_rank, 0, MPI_COMM_WORLD, &request[0]);
        printf("I am rank %d and I am sending to rank: %d \n", my_rank, left_rank);
        MPI_Irecv(fromLeft, p.ymax - p.ymin, MPI_DOUBLE, left_rank, 0, MPI_COMM_WORLD, &request[2]);
        printf("I am rank %d and I am receiving from rank: %d \n", my_rank, left_rank);
    }
    if (right_rank != -1){
        MPI_Isend(column_to_right, p.ymax - p.ymin, MPI_DOUBLE,  right_rank, 1, MPI_COMM_WORLD, &request[1]);
        printf("I am rank %d and I am sending to rank: %d\n", my_rank, right_rank);
        // what is stored in u (is the subslice that this rank can see)

        MPI_Irecv(fromRight, p.ymax - p.ymin, MPI_DOUBLE, right_rank, 1, MPI_COMM_WORLD, &request[3]);
        printf("I am rank %d and I am receiving from rank: %d \n", my_rank, right_rank);
    }

    MPI_Waitall(4, request, MPI_STATUSES_IGNORE);


	printf("mpi_module.cpp, define halo comm:  \n");
	return 0;
}


int ALLREDUCE(double* loc_diff, double* loc_sumdiff){
    // use this with the correct varibles to get the stuff
	MPI_Allreduce(loc_diff, loc_sumdiff, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	return 0;

	}

