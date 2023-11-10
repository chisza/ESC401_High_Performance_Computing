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

    // Initialize the dimensions of the grid
    int ndims = 2;
    // Initialize the processes per dimension -> array with size ndims
    int dims[ndims];
    // Set the number of processes per dimension,
    // if more than one dimension, define the number of processes for every
    // dimension (goes for period as well)
    // eg dims[0]=4, dims[1] = 3 for 3 dimensions
    dims[0] = nx/size; dims[1] = ny/size;
    // Initialize the periodicity
    int period[ndims];
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


    printf("in mpi_get_domain() in mpi_module.cpp,  define corners of the local domains\n");

	printf("I am rank %d and my domain is: xmin, xmax, ymin, ymax: %d %d %d %d\n",my_rank,*min_x,*max_x,*min_y,*max_y);
	return 0;
}

int halo_comm(params p, int my_rank, int size, double** u, double* fromLeft, double* fromRight){
	
	/*this function, vectors fromLeft and fromRight should be received from the neighbours of my_rank process*/
	/*if you want to implement also cartesian topology, you need fromTop and fromBottom in addition to fromLeft a
	nd fromRight*/

	for (int j=0;j<(p.ymax - p.ymin);j++) {fromLeft[j] = 0; fromRight[j] = 0;} //initialize fromLeft and fromRight

    /* define columns to be sent to right neighbour and to the left neighbour, 
    also receive one both form left and right neighbour*/

    /* choose either to define MPIcolumn_type (lines 43-45) or define 
    the columns to be sent manually (lines 53-56)*/

//    MPI_Datatype column_type;
//    MPI_Type_vector(p.ymax - p.ymin, 1, p.xmax - p.xmin, MPI_DOUBLE, &column_type);
//    MPI_Type_commit(&column_type);
//
//    for (int i = 0; i < size-1; i++) {
//        // to avoid a deadlock, split the ranks into two groups, that send and receive alternatively
//        if (my_rank % 2 == 0) {
//            // Even-ranked processes send first
//            // Exchange with neighbour to the left
//            MPI_Ssend(u[], 1, column_type, fromLeft, 0, MPI_COMM_WORLD);
//            MPI_Recv(, 1, column_type, fromLeft, 0, MPI_COMM_WORLD, &status);
//
//            // Exchange with neighbour to the right
//
//        } else {
//            // Odd-ranked processes receive first
//            MPI_Recv(&recv_rank, 1, column_type, left_rank, tag, MPI_COMM_WORLD, &status);
//            MPI_Ssend(&send_rank, 1, column_type, right_rank, tag, MPI_COMM_WORLD);
//            send_rank = recv_rank;
//            my_sum += recv_rank;
//        }
//    }



    // ...some code goes here and then do not forget to free the column_type

    //MPI_Type_free(&column_type);

	//or alternative approach below

	// double* column_to_right = new double [p.ymax - p.ymin];
	// for (int j=0;j<(p.ymax - p.ymin);j++) column_to_right[j] = u[p.xmax - p.xmin - 1][j]; 
	// double* column_to_left = new double [p.ymax - p.ymin];
	// for (int j=0;j<(p.ymax - p.ymin);j++) column_to_left[j] = u[0][j]; 


	printf("mpi_module.cpp, define halo comm:  \n");
	return 0;
}


int ALLREDUCE(double* loc_diff, double* loc_sumdiff){

	MPI_Allreduce(loc_diff, loc_sumdiff, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	return 0;

	}

