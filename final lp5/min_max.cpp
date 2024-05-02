#include <iostream>
#include <omp.h>
#include <climits>
using namespace std;

// Function to find the minimum value in the array using OpenMP reduction
void min_reduction(int arr[], int n) {
    int min_value = INT_MAX;
    #pragma omp parallel for reduction(min : min_value)
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
    }
    cout << "Minimum value: " << min_value << endl;
}

// Function to find the maximum value in the array using OpenMP reduction
void max_reduction(int arr[], int n) {
    int max_value = INT_MIN;
    #pragma omp parallel for reduction(max : max_value)
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }
    cout << "Maximum value: " << max_value << endl;
}

// Function to calculate the sum of elements in the array using OpenMP reduction
void sum_reduction(int arr[], int n) {
    int sum = 0;
    #pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    cout << "Sum: " << sum << endl;
}

// Function to calculate the average of elements in the array using OpenMP reduction
void average_reduction(int arr[], int n) {
    int sum = 0;
    #pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    // Calculate the average (excluding the number of threads)
    cout << "Average: " << (double)sum / (n - 1) << endl;
}

int main() {
    int *arr, n;

    // Input the total number of elements
    cout << "Enter total number of elements: ";
    cin >> n;

    // Dynamically allocate memory for the array
    arr = new int[n];

    // Input array elements
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Call reduction functions to find minimum, maximum, sum, and average of array elements
    min_reduction(arr, n);
    max_reduction(arr, n);
    sum_reduction(arr, n);
    average_reduction(arr, n);

    // Free dynamically allocated memory
    delete[] arr;

    return 0;
}
