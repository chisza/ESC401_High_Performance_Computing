#include "mpi.h"
#include <stdio.h>
#include "init.h"
#include <math.h>

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

    // Initialize the dimensions of the grid
    int ndims = 2;
    // Initialize the processes per dimension -> array with size ndims
    int dims[ndims];
    // Set the number of processes per dimension,
    // if more than one dimension, define the number of processes for every
    // dimension (goes for period as well)
    // eg dims[0]=4, dims[1] = 3 for 3 dimensions
    dims[0] = size / 2; dims[1] = size / 2;
    // Initialize the periodicity
    int period[2];
    // Set the periodicity to true for each dimension
    period[0] = 1; period[1] = 1;
    // Initialize the reordering
    int reorder;
    // Set the reordering to true
    reorder = 1;
    // initialize a new communicator
    MPI_Comm new_comm;

    MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, period, reorder, &new_comm);

    // Get the number of processes and the rank of the process
    //int size, my_rank;
    MPI_Status status[ndims];
    MPI_Request request[ndims];
    MPI_Comm_size(new_comm, &size);
    MPI_Comm_rank(new_comm, &my_rank);



    int direction = 0; // go row-wise and stay in the row
    int displ = 1; // affect the immediately left and right rank
    // initalize the left and right rank -> source and dest
    int left_rank, right_rank, bottom_rank, top_rank;

    MPI_Cart_shift(new_comm, direction, displ, &left_rank, &right_rank);
    direction = 1; // go col-wise and stay in the row
    displ = 1; // affect the immediately left and right rank
    MPI_Cart_shift(new_comm, direction, displ, &bottom_rank, &top_rank);

    // get the local nx for each rank
    // divide the number of dots in x direction by the number of processes
    // get only integers
    int nx_local = nx / (size/2);
    // get the remainder of the division
    int remainder_x = nx % (size/2);

    // get the local ny for each rank
    // divide the number of dots in y direction by the number of processes
    // get only integers
    int ny_local = ny / (size/2);
    // get the remainder of the division
    int remainder_y = ny % (size/2);

    if (my_rank == 0) {
        // *min_x is a pointer to the value for min_x -> calculate this with the rank and the calculated "distance"
        *min_x = my_rank * nx_local;
        // *max_x is a pointer to the value for max_x -> calculate this starting from the value min_x pointed at by
        // *min_x and add the "distance" nx_local to it
        *max_x = *min_x + nx_local;
        // *min_x is a pointer to the value for min_x -> calculate this with the rank and the calculated "distance"
        *min_y = my_rank * ny_local;
        // *max_x is a pointer to the value for max_x -> calculate this starting from the value min_x pointed at by
        // *min_x and add the "distance" nx_local to it
        *max_y = *min_y + ny_local;
    }
    else if (my_rank == 1) {
        *min_x = (my_rank-1) * nx_local/2;
        *max_x = *min_x + nx_local;
        *min_y = my_rank * ny_local;
        *max_y = *min_y + ny_local;
    }

    else if (my_rank % 2 == 0) {
        *min_x = my_rank * nx_local/2;
        *max_x = *min_x + nx_local;
        *min_y = (my_rank-2) * ny_local;
        *max_y = *min_y + ny_local;
    }
    else {
        *min_x = (my_rank-1) * nx_local/2;
        *max_x = *min_x + nx_local;
        *min_y = (my_rank-2) * ny_local;
        *max_y = *min_y + ny_local;
    }

    // have to split them to x and y -> I ignore this for the moment
    // check, if the current rank is the last one
    // if yes, then add the remainder to make sure, that all dots are part of one process
    // the maximum number of processes is size - 1, because it starts at 0
    if (my_rank == size - 1) {
        *max_x += remainder_x;
        *max_y += remainder_y;
    }


    printf("in mpi_get_domain() in mpi_module.cpp,  define corners of the local domains\n");

    printf("my rank : %d right rank : %d left rank : %d top rank : %d bottom rank : %d\n", my_rank, right_rank, left_rank, top_rank, bottom_rank);

	printf("I am rank %d and my domain is: xmin, xmax, ymin, ymax: %d %d %d %d\n",my_rank,*min_x,*max_x,*min_y,*max_y);
	return 0;
}

int halo_comm(params p, int my_rank, int size, double** u, double* fromLeft, double* fromRight, double *fromBottom, double *fromTop){
	
	/*this function, vectors fromLeft and fromRight should be received from the neighbours of my_rank process*/
	/*if you want to implement also cartesian topology, you need fromTop and fromBottom in addition to fromLeft a
	nd fromRight*/

	for (int j=0;j<(p.ymax - p.ymin);j++) {fromLeft[j] = 0; fromRight[j] = 0; fromTop[j] = 0; fromBottom[j] = 0} //initialize fromLeft and fromRight

    /* define columns to be sent to right neighbour and to the left neighbour, 
    also receive one both form left and right neighbour*/

    /* choose either to define MPIcolumn_type (lines 43-45) or define 
    the columns to be sent manually (lines 53-56)*/

    // initialize the ranks
    int left_rank, right_rank, top_rank, bottom_rank;

    if (my_rank == 0) {
        // the first rank
        right_rank = my_rank + (sqrt(size) + 1);
        // give a dummy value for ranks that are not needed -> do not go around
        left_rank = - 1;
        top_rank = -1;
        bottom_rank = my_rank + 1;
    }
    else if (my_rank == sqrt(size)) {
        // the lowest rank of the first column
        right_rank = my_rank + (sqrt(size) + 1);
        left_rank = -1;
        top_rank = my_rank - 1;
        bottom_rank = - 1;
    }

    else if (1 < my_rank < sqrt(size)-1) {
        // ranks of the first column
        right_rank = my_rank + (sqrt(size) + 1);
        left_rank = - 1;
        top_rank = my_rank - 1;
        bottom_rank = my_rank + 1;
    }
    else if ((size -(sqrt(size) - 1)) < my_rank < sqrt(size)-2) {
        // ranks of the last column
        right_rank = -1 ;
        left_rank = my_rank - (sqrt(size) + 1);
        top_rank = my_rank - 1;
        bottom_rank = my_rank + 1;
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
    for (int j=0;j<(p.ymax - p.ymin);j++) {column_to_right[j] = u[p.xmax - p.xmin - 1][j];}
    double* column_to_left = new double [p.ymax - p.ymin];
    for (int j=0;j<(p.ymax - p.ymin);j++) {column_to_left[j] = u[0][j];}
    printf("&column_to_left : %g\n", *column_to_left);
    printf("column_to_left : %f\n", column_to_left[1]);

    MPI_Request request[4];
    //int count = 0;
    for (int i = 0; i < 4; i++) {
        request[i] = MPI_REQUEST_NULL;
    }

    if (left_rank != -1) {
        // exchange with left
        // column_to_left -> is the address of the first element -> go left of all the elements that we want
        // and send them -> is not a value
        MPI_Irecv(fromLeft, p.ymax - p.ymin, MPI_DOUBLE, left_rank, 0, MPI_COMM_WORLD, &request[1]);
        //count += 1;
        printf("I am rank %d and I am receiving from rank: %d \n", my_rank, left_rank);
        MPI_Isend(column_to_left, p.ymax - p.ymin, MPI_DOUBLE, left_rank, 0, MPI_COMM_WORLD, &request[0]);
        //count += 1;
        printf("I am rank %d and I am sending to rank: %d \n", my_rank, left_rank);

    }
    if (right_rank != -1){
        // exchange with right
        MPI_Irecv(fromRight, p.ymax - p.ymin, MPI_DOUBLE, right_rank, 0, MPI_COMM_WORLD, &request[3]);
        //count += 1;
        printf("I am rank %d and I am receiving from rank: %d \n", my_rank, right_rank);
        MPI_Isend(column_to_right, p.ymax - p.ymin, MPI_DOUBLE,  right_rank, 0, MPI_COMM_WORLD, &request[2]);
        //count += 1;
        printf("I am rank %d and I am sending to rank: %d\n", my_rank, right_rank);
        // what is stored in u (is the subslice that this rank can see)

    }

    //MPI_Waitall(4, request, MPI_STATUSES_IGNORE);
    MPI_Waitall(4, request, MPI_STATUSES_IGNORE);


	printf("mpi_module.cpp, define halo comm:  \n");
	return 0;
}


int ALLREDUCE(double* loc_diff, double* loc_sumdiff){

	MPI_Allreduce(loc_diff, loc_sumdiff, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	return 0;

	}

