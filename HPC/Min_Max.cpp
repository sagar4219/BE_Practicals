#include <iostream>
#include <omp.h>

using namespace std;

// Function to find the minimum value in an array using parallel reduction
int findMin(int arr[], int n) {
    int min_val = arr[0];
    #pragma omp parallel for reduction(min:min_val)
    for (int i = 1; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    return min_val;
}

// Function to find the maximum value in an array using parallel reduction
int findMax(int arr[], int n) {
    int max_val = arr[0];
    #pragma omp parallel for reduction(max:max_val)
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

int main() {
    const int n = 10000;
    int arr[n];

    // Generate or populate the array (You can fill it according to your requirements)
    for (int i = 0; i < n; ++i) {
        arr[i] = i; // Example: Filling the array with values 0 to 9999
    }

    // Find minimum value
    int min_val = findMin(arr, n);
    cout << "Minimum value: " << min_val << endl;

    // Find maximum value
    int max_val = findMax(arr, n);
    cout << "Maximum value: " << max_val << endl;

    return 0;
}
