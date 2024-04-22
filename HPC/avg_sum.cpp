#include <iostream>
#include <omp.h>

using namespace std;

// Function to calculate the sum of values in an array using parallel reduction
int findSum(int arr[], int n) {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

// Function to calculate the average value in an array using parallel reduction
double findAverage(int arr[], int n) {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return static_cast<double>(sum) / n;
}

int main() {
    const int n = 10000;
    int arr[n];

    // Generate or populate the array (You can fill it according to your requirements)
    for (int i = 0; i < n; ++i) {
        arr[i] = i; // Example: Filling the array with values 0 to 9999
    }

    // Find sum of values
    int sum = findSum(arr, n);
    cout << "Sum of values: " << sum << endl;

    // Find average value
    double avg = findAverage(arr, n);
    cout << "Average value: " << avg << endl;

    return 0;
}
