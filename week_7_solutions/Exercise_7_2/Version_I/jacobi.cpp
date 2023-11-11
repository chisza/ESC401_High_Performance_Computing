#include "jacobi.h"
#include <math.h>
#include "mpi_module.h"

/**
 * @brief      Computes norm of the difference between two matrices
 *
 * @param[in]  p     Parameters
 * @param      mat1  The matrix 1
 * @param      mat2  The matrix 2
 *
 * @return     Returns \sqrt{\sum(mat1_{ij} - mat2_{ij})^2/(nx*ny)}
 */
double norm_diff(params p, double** mat1, double** mat2){

    printf("Here, in norm_diff() function, change the serial implementation to MPI setup\n");
    double ret=0., diff=0.;
    // have to ajust the number of loops as we do not have the full grid  -> update them
    // but we need to combine the 4 or however many results
    // get the difference from the matrices of one rank
    int x_range = p.xmax - p.xmin;
    int y_range = p.ymax - p.ymin;

    for (int i=0; i<x_range; i++){
        for (int j=0; j<y_range; j++){
            diff = mat1[i][j] - mat2[i][j];
            ret += diff*diff;
        }
    }
    // to calculate the overall norm_diff -> need the total sum
    double tot_sum;
    ALLREDUCE(&ret, &tot_sum);
    double tot_diff;
    tot_diff = sqrt(tot_sum/(p.nx*p.ny));
    // call some routine to get the variable from all domains
    return tot_diff;
}

/**
 * @brief      Compute a Jacobi iteration to solve Poisson equation. This function updates
 *             u_new and u_old in-place.
 *
 * @param[in]  p      Parameters
 * @param      u_new  The new solution
 * @param      u_old  The old solution
 * @param      f      The source term
 */
void jacobi_step(params p, double** u_new, double** u_old, double** f, int my_rank, int size) {
    // define the step size
    double dx = 1.0 / ((double) p.nx - 1);
    double dy = 1.0 / ((double) p.ny - 1);

    // initialize the vectors that should be received with the length
    double *fromLeft = new double[p.ymax - p.ymin];
    double *fromRight = new double[p.ymax - p.ymin];

    // change the iteration steps
    // when looking at the whole grid -> need only steps: 0-40, 41-80, 81-120, 121-161 for example
    // should already allocate the matrix according to size due to the way the matrices are done

//    for (int i=p.xmin; i<p.xmax; i++){
//        for (int j=p.ymin; j<p.ymax; j++){
//            u_old[i - p.xmin][j - p.ymin] = u_new[i - p.xmin][j - p.ymin];
//        }
//    }

    int x_range = p.xmax - p.xmin;
    int y_range = p.ymax - p.ymin;

    // sets the new values at the correct position in u_new
    for (int i = 0; i < x_range; i++) {
        for (int j = 0; j < y_range; j++) {
            u_old[i][j] = u_new[i][j];
        }
    }

    // get the edges for the columns at the left and right side
    halo_comm(p, my_rank, size, u_new, fromLeft, fromRight);

    printf("Function jacobi_step in jacobi.cpp : adapt the update of u_new.\n");

    // at the outer ranks, the x and y values have to be considered
    // at the inner ranks, only the x values have to be considered for the boundary

    // go over the whole grid to check for the boundaries
    for (int i = p.xmin; i < p.xmax; i++) {
        // stay away from the boundaries
        if (i == 0 || i == p.nx - 1) {
            continue;
        }
        for (int j = p.ymin; j < p.ymax; j++) {
            // stay away from the boundaries
            if (j == 0 || j == p.ny - 1) {
                continue;
            }
            // get the index where the jacobi step should take place
            // make sure, that the fromLeft and fromRight are included

            // are the indeces, normed to the place in the matrix of every rank
            // have to make sure that the index is fromLeft and fromRight for the outer ranks
            int idx = i - p.xmin;
            int idy = j - p.ymin;

            // To get the right most column -> not necessary at right most rank
            if (i == p.xmax - 1 && my_rank != size - 1) {
                u_new[idx][idy] = 0.25 *
                                  (u_old[idx - 1][idy] + fromRight[idy] + u_old[idx][idy - 1] + u_old[idx][idy + 1] -
                                   dx * dy * f[idx][idy]);
            }
            // To get the left most column -> not necessary at left most rank
            else if (i == p.xmin && my_rank != 0) {
                u_new[idx][idy] = 0.25 *
                                  (fromLeft[idy] + u_old[idx + 1][idy] + u_old[idx][idy - 1] + u_old[idx][idy + 1] -
                                   dx * dy * f[idx][idy]);
            }
                // What happens everywhere else
            else {
                u_new[idx][idy] = 0.25 * (u_old[idx - 1][idy] + u_old[idx + 1][idy] + u_old[idx][idy - 1] +
                                          u_old[idx][idy + 1] - dx * dy * f[idx][idy]);
            }

//            // are the indeces, normed to the place in the matrix of every rank
//            // have to make sure that the index is fromLeft and fromRight for the outer ranks
//            int idx = i-p.xmin;
//            int idy = j-p.ymin;
//            // need to implement fromLeft and fromRight somehow -> could also be done in the halo_comm
//            u_new[idx][idy] = 0.25*(u_old[idx-1][idy] + u_old[idx+1][idy] + u_old[idx][idy-1] + u_old[idx][idy+1] - dx*dy*f[idx][idy]);
//        }
        }
        if (p.nx != p.ny) printf("In function jacobi_step (jacobi.cpp l.26): nx != ny, check jacobi updates\n");
    }
    printf("\njacobi step iterations done, my rank %d\n", my_rank);
}