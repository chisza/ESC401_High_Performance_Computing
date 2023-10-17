#include <stdio.h>
#include <stdlib.h>

// initialize a structure that has two vectors, one for the real part and one for the imaginary part
// for one number, eg. 1 + i it needs complex_vector real for the real part and complex_vector imagine
// for the imagine part
struct complex_vector{
    float *real;
    float *imagine;
};

// start function up, what is the function name, which arguments does it take
struct complex_vector linear_combination(struct complex_vector x_vector,
                                         struct complex_vector y_vector,
                                         struct complex_vector z_vector,
                                         int multiplier);

// define the function, what it does
struct complex_vector linear_combination(struct complex_vector x_vector,
                                         struct complex_vector y_vector,
                                         struct complex_vector z_vector,
                                         int multiplier) {

    // start the real and imaginary part of the z vector, set to 0, so other values
    // can be added to
    z_vector.real[0] = 0;
    z_vector.imagine[0] = 0;

    // for loop to sum the vectors and add the sum to the total sum
    // for both the real and imaginary part
    for (int i = 0; i < 1000; i++) {
        z_vector.real[0] += x_vector.real[i] + (float)multiplier * y_vector.real[i];
        z_vector.imagine[0] += x_vector.imagine[i] + (float)multiplier * y_vector.imagine[i];
    }
    return z_vector;
}

int main(int argc, char const *argv[]){

    // initialize three complex vectors, with a chosen length
    // initialize the real and the complex part for the three vectors
    struct complex_vector x, y, z;

    // assign part of the memory to the real and imaginary part of x and y
    // memory allocated has to be the "number" of the calculations
    x.real = malloc(1000 * sizeof(float)); //array with floats
    x.imagine = malloc(1000* sizeof(float));
    y.real = malloc(1000 * sizeof(float));
    y.imagine = malloc(1000 * sizeof(float));

    // z is the array for the result, needs only space for one
    // float for both .real and .imagine
    z.real = malloc(1 * sizeof(float));
    z.imagine = malloc(1 * sizeof(float));

    // allocate actual values to both x and y -> need a for loop
    // at place i for each real and imagine for each vector -> assign a value
    // make it a bit more interesting and multiply each with a factor
    for (int i = 0; i < 1000; i++){
        x.real[i] = (float)i + 1;
        x.imagine[i] = (float)i + 2;
        y.real[i] = (float)i + 3;
        y.imagine[i] = (float)i + 4;
    }

    // call the function linear_combination that was defined outside the main
    // give it the necessary arguments
    // type of the arguments does not have to be defined, as in the function definition
    // the types are defined
    linear_combination(x, y, z, 4);

    // Print the result
    printf("Linear combination gives the following result:\n%.1f + %.1fi", z.real[0], z.imagine[0]);

    // Free the memory so that there is no memory leak
    free(x.real);
    free(x.imagine);
    free(y.real);
    free(y.imagine);
    free(z.real);
    free(z.imagine);

    return 0;
}


