#include <iostream>
#include <vector>

// define a function that takes an array of two arrays and reverses them
// it will return this reversed array

int ** reverse_array(int ** two_dimensional_array) {

    int ** reversed_array = new int *[2]; // same as above, but for M2
    reversed_array[0] = new int [5];
    reversed_array[1] = new int [5];

    for (int i = 0; i < 2; i++) { // loop through the 2 arrays in M
        if (i == 0) { // check if it is the first array
            for (int j = 0; j < 5; j++) { // loop through the values of the array
                *(*(reversed_array + (i+1)) + (4-j)) = *(*(two_dimensional_array + i) + j); // assign the value at position M[i][j] to the reverse position in the second array of M2
            }
        }
            // same as above but for the second array
        else if (i == 1) {
            for (int j = 0; j < 5; j++) {
                *(*(reversed_array + (i-1)) + (4-j)) = *(*(two_dimensional_array + i) + j);
            }
        }
            // make sure it's a 2-D array
        else {
            std::cout << "What the are you doing?";
        }
    }

    return reversed_array;
}

int main() {

    int ** M = new int *[2]; // starts an array, with two pointers, that then each point to a value in an array
    M[0] = new int[5] {0, 1, 2, 3, 4}; // fill the two arrays with values
    M[1] = new int[5] {5, 6, 7, 8, 9};

    // check if arrays are stored next to each other
    if (*(M[0] + 5) == M[1][0]) {
        std::cout << "Arrays stored next to each other\n";
    }
    else {
        std::cout << "Fail\n";
    }

    int ** M2 = reverse_array(M); // reverse the arrays

    // print out the values in M
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 5; j++){
            std::cout << *(*(M + i) + j) << "\n";
        }
    }

    // print out the values in M2 -> should be reverse
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 5; j++){
            std::cout << *(*(M2 + i) + j) << "\n";
        }
    }

    // free the memory
    free(M);
    free(M2);

    return 0;
}