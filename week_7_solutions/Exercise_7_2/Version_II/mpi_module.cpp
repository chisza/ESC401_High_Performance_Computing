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
        *max_x += 1;
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
	
	/*this function, vectors fromLeft and fromRight should be received from the neighbours of my_rank process*/
	/*if you want to implement also cartesian topology, you need fromTop and fromBottom in addition to fromLeft a
	nd fromRight*/

	for (int j=0;j<(p.ymax - p.ymin);j++) {fromLeft[j] = 0; fromRight[j] = 0;} //initialize fromLeft and fromRight

    /* define columns to be sent to right neighbour and to the left neighbour, 
    also receive one both form left and right neighbour*/

    /* choose either to define MPIcolumn_type (lines 43-45) or define 
    the columns to be sent manually (lines 53-56)*/

    MPI_Datatype column_type;
    MPI_Type_vector(p.ymax - p.ymin, 1, p.xmax - p.xmin, MPI_DOUBLE, &column_type);
    MPI_Type_commit(&column_type);

    for (int i = 0; i < size-1; i++) {
        // to avoid a deadlock, split the ranks into two groups, that send and receive alternatively
        if (my_rank % 2 == 0) {
            // Even-ranked processes send first
            // Exchange with neighbour to the left
            MPI_Ssend(u[], 1, column_type, fromLeft, 0, MPI_COMM_WORLD);
            MPI_Recv(, 1, column_type, fromLeft, 0, MPI_COMM_WORLD, &status);

            // Exchange with neighbour to the right

        } else {
            // Odd-ranked processes receive first
            MPI_Recv(&recv_rank, 1, column_type, left_rank, tag, MPI_COMM_WORLD, &status);
            MPI_Ssend(&send_rank, 1, column_type, right_rank, tag, MPI_COMM_WORLD);
            send_rank = recv_rank;
            my_sum += recv_rank;
        }
    }



    // ...some code goes here and then do not forget to free the column_type

    MPI_Type_free(&column_type);

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

