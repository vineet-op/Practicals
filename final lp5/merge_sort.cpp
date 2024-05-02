#include <iostream>
#include <stdlib.h>
#include <omp.h>

using namespace std;

// Function to merge two halves of an array
void merge(int a[], int i1, int j1, int i2, int j2) {
    int temp[1000]; // Temporary array to store merged result
    int i, j, k;
    i = i1;
    j = i2;
    k = 0;

    // Merge two halves into temp array in sorted order
    while (i <= j1 && j <= j2) {
        if (a[i] < a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }

    // Copy remaining elements of first half, if any
    while (i <= j1) {
        temp[k++] = a[i++];
    }

    // Copy remaining elements of second half, if any
    while (j <= j2) {
        temp[k++] = a[j++];
    }

    // Copy sorted elements back to original array a
    for (i = i1, j = 0; i <= j2; i++, j++) {
        a[i] = temp[j];
    }
}

// Recursive function to perform mergesort
void mergesort(int a[], int i, int j) {
    int mid;

    if (i < j) {
        mid = (i + j) / 2;

        // Parallelize the two recursive calls using OpenMP sections
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergesort(a, i, mid); // Sort first half
            }

            #pragma omp section
            {
                mergesort(a, mid + 1, j); // Sort second half
            }
        }

        // Merge the sorted halves
        merge(a, i, mid, mid + 1, j);
    }
}

int main() {
    int *a, n, i;

    cout << "Enter total number of elements: ";
    cin >> n;

    a = new int[n];

    cout << "Enter elements: ";
    for (i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Perform mergesort on the array
    mergesort(a, 0, n - 1);

    // Output the sorted array
    cout << "\nSorted array is: \n";
    for (i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    delete[] a; // Free dynamically allocated memory

    return 0;
}
