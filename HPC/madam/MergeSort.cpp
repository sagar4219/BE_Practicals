#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

// Merge function to merge two sorted subarrays
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Sequential merge sort function
void mergeSortSequential(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortSequential(arr, l, m);
        mergeSortSequential(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Parallel merge sort function using OpenMP
void mergeSortParallel(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSortParallel(arr, l, m);

            #pragma omp section
            mergeSortParallel(arr, m + 1, r);
        }
        merge(arr, l, m, r);
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

    // Sequential Merge Sort
    auto startSequential = high_resolution_clock::now();
    mergeSortSequential(arrSequential, 0, n - 1);
    auto stopSequential = high_resolution_clock::now();
    auto durationSequential = duration_cast<microseconds>(stopSequential - startSequential);
    cout << "Sequential Merge Sort Time: " << durationSequential.count() << " microseconds" << endl;

    // Parallel Merge Sort
    auto startParallel = high_resolution_clock::now();
    mergeSortParallel(arrParallel, 0, n - 1);
    auto stopParallel = high_resolution_clock::now();
    auto durationParallel = duration_cast<microseconds>(stopParallel - startParallel);
    cout << "Parallel Merge Sort Time: " << durationParallel.count() << " microseconds" << endl;

    // Verify if both arrays are sorted correctly
    bool sorted = true;
    for (int i = 0; i < n - 1; ++i) {
        if (arrSequential[i] > arrSequential[i + 1]) {
            sorted = false;
            break;
        }
    }

    if (sorted) {
        cout << "Sequential Merge Sort: Array is sorted correctly" << endl;
    } else {
        cout << "Sequential Merge Sort: Array is NOT sorted correctly" << endl;
    }

    sorted = true;
    for (int i = 0; i < n - 1; ++i) {
        if (arrParallel[i] > arrParallel[i + 1]) {
            sorted = false;
            break;
        }
    }

    if (sorted) {
        cout << "Parallel Merge Sort: Array is sorted correctly" << endl;
    } else {
        cout << "Parallel Merge Sort: Array is NOT sorted correctly" << endl;
    }

    return 0;
}
