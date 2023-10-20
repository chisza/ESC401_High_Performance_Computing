#include "jacobi.h"
#include <math.h>

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
    // initialize the value containing the norm
    double norm;
    double sum = 0;

    for (int i = 0; i < p.nx; i++) {
        for (int j = 0; j < p.ny; j++) {
            sum += ((mat1[i][j] - mat2[i][j]) * (mat1[i][j] - mat2[i][j]));
        }
    }

    norm = sqrt(sum /(p.nx * p.ny));

    //printf("Function norm_diff (jacobi.cpp l.12): not implemented.\n");
    return norm; // replace 0 with the norm
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
void jacobi_step(params p, double** u_new, double** u_old, double** f){
    double dx = 1.0/(double(p.nx - 1));
    double dy = 1.0/(double(p.ny - 1));

    for (int i=0; i<p.nx; i++){
        for (int j=0; j<p.ny; j++){
            u_old[i][j] = u_new[i][j];

            // stay away from the boundaries
            if (i == 0 || j == 0 || i == p.nx - 1 || j == p.ny - 1) {
                continue;
            }
            // if (1 <= i <= (p.nx -2) || 1 <= j <= (p.ny -2))
            else {
                u_new[i][j] = (1.0 / 4.0) * (u_old[i - 1][j] + u_old[i + 1][j] + u_old[i][j - 1] + u_old[i][j + 1] -
                                           (dx * dy) * f[i][j]);
            }
        }
    }
    //printf("Function jacobi_step (jacobi.cpp l.26): not implemented.\n");
}
