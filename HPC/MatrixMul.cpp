#include <iostream>
#include <cstdlib>
#include <omp.h>

using namespace std;

#define MAX 100

int main() {
    int r = 3, c = 2;
    int matrix[r][c], vector[c], out[r];
    
    // Fill the matrix with ones
    for (int row = 0; row < r; row++) {
        for (int col = 0; col < c; col++) {
            matrix[row][col] = 1;
        }
    }

    cout << "Input Matrix" << endl;
    // Print the matrix
    for (int row = 0; row < r; row++) {
        for (int col = 0; col < c; col++) {
            cout << "\t" << matrix[row][col];
        }
        cout << "" << endl;
    }

    // Fill the vector with twos
    for (int col = 0; col < c; col++) {
        vector[col] = 2;
    }

    cout << "Input Col-Vector" << endl;
    // Print the vector
    for (int col = 0; col < c; col++) {
        cout << vector[col] << endl;
    }

    #pragma omp parallel for
    // Perform matrix-vector multiplication
    for (int row = 0; row < r; row++) {
        out[row] = 0;
        for (int col = 0; col < c; col++) {
            out[row] += matrix[row][col] * vector[col];
        }
    }

    cout << "Resultant Col-Vector" << endl;
    // Print the result vector
    for (int row = 0; row < r; row++) {
        cout << "\nvector[" << row << "]:" << out[row] << endl;
    }

    return 0;
}
