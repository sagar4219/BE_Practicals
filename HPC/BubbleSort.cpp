#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

// Function to perform bubble sort sequentially
void bubbleSortSequential(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Function to perform bubble sort in parallel using OpenMP
void bubbleSortParallel(vector<int>& arr) {
    int n = arr.size();
    int i, j;
    #pragma omp parallel for private(i, j)
    for (i = 0; i < n - 1; ++i) {
        for (j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Function to generate random integers
void generateRandomNumbers(vector<int>& arr, int n) {
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        arr.push_back(rand());
    }
}

int main() {
    int n = 10000; // Size of the array
    vector<int> arrSequential, arrParallel;

    // Generate random numbers for the arrays
    generateRandomNumbers(arrSequential, n);
    arrParallel = arrSequential; // Copying for parallel sorting

    // Sequential Bubble Sort
    auto startSequential = high_resolution_clock::now();
    bubbleSortSequential(arrSequential);
    auto stopSequential = high_resolution_clock::now();
    auto durationSequential = duration_cast<microseconds>(stopSequential - startSequential);
    cout << "Sequential Bubble Sort Time: " << durationSequential.count() << " microseconds" << endl;

    // Parallel Bubble Sort
    auto startParallel = high_resolution_clock::now();
    bubbleSortParallel(arrParallel);
    auto stopParallel = high_resolution_clock::now();
    auto durationParallel = duration_cast<microseconds>(stopParallel - startParallel);
    cout << "Parallel Bubble Sort Time: " << durationParallel.count() << " microseconds" << endl;

    // Verify if both arrays are sorted correctly
    bool sorted = true;
    for (int i = 0; i < n - 1; ++i) {
        if (arrSequential[i] > arrSequential[i + 1]) {
            sorted = false;
            break;
        }
    }

    if (sorted) {
        cout << "Sequential Bubble Sort: Array is sorted correctly" << endl;
    } else {
        cout << "Sequential Bubble Sort: Array is NOT sorted correctly" << endl;
    }

    sorted = true;
    for (int i = 0; i < n - 1; ++i) {
        if (arrParallel[i] > arrParallel[i + 1]) {
            sorted = false;
            break;
        }
    }

    if (sorted) {
        cout << "Parallel Bubble Sort: Array is sorted correctly" << endl;
    } else {
        cout << "Parallel Bubble Sort: Array is NOT sorted correctly" << endl;
    }

    return 0;
}
