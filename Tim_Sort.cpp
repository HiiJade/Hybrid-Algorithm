#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

// Insertion Sort for small partitions
void insertionSort(vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Merge function for Merge Sort
void merge(vector<int>& arr, int left, int mid, int right) {
    int len1 = mid - left + 1;
    int len2 = right - mid;
    vector<int> leftArr(len1), rightArr(len2);

    for (int i = 0; i < len1; i++) leftArr[i] = arr[left + i];
    for (int i = 0; i < len2; i++) rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < len1 && j < len2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }
    while (i < len1) arr[k++] = leftArr[i++];
    while (j < len2) arr[k++] = rightArr[j++];
}

// Recursive Merge Sort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Hybrid Merge Sort with Insertion Sort for small partitions
void timSortHelper(vector<int>& arr, int left, int right, int k) {
    if (right - left + 1 <= k) {
        insertionSort(arr, left, right);
        return;
    }
    int mid = left + (right - left) / 2;
    timSortHelper(arr, left, mid, k);
    timSortHelper(arr, mid + 1, right, k);
    merge(arr, left, mid, right);
}

// Tim Sort Entry Function
void timSort(vector<int>& arr, int k) {
    timSortHelper(arr, 0, arr.size() - 1, k);
}

// Function to generate random test cases
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100000; // Random numbers between 0 and 99999
    }
    return arr;
}

// Function to test different values of k
void findOptimalK() {
    int n = 100000; // Large array size
    vector<int> original = generateRandomArray(n);
    
    int bestK = 0;
    double bestTime = 1e9; // Initialize with a large time

    cout << "Testing different values of k...\n";
    cout << "k\tMerge Sort (ms)\tTim Sort (ms)\n";
    
    for (int k = 2; k <= 64; k *= 2) {
        // Run Merge Sort
        vector<int> arr1 = original;
        auto start1 = high_resolution_clock::now();
        mergeSort(arr1, 0, arr1.size() - 1);
        auto end1 = high_resolution_clock::now();
        double mergeTime = duration_cast<microseconds>(end1 - start1).count() / 1000.0; // Convert to ms

        // Run Tim Sort
        vector<int> arr2 = original;
        auto start2 = high_resolution_clock::now();
        timSort(arr2, k);
        auto end2 = high_resolution_clock::now();
        double timSortTime = duration_cast<microseconds>(end2 - start2).count() / 1000.0; // Convert to ms

        cout << k << "\t" << mergeTime << "\t\t" << timSortTime << endl;

        if (timSortTime < bestTime) {
            bestTime = timSortTime;
            bestK = k;
        }
    }
    cout << "\nOptimal k: " << bestK << " with time: " << bestTime << " ms\n";
}

int main() {
    findOptimalK();
    return 0;
}
