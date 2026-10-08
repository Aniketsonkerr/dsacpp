#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <numeric>

long long merge_sort_ops = 0;
long long binary_search_ops = 0;

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        merge_sort_ops++; // Element comparison
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) { arr[k++] = L[i++]; }
    while (j < n2) { arr[k++] = R[j++]; }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        binary_search_ops++; // Loop condition & comparison count
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    std::cout << std::left << std::setw(10) << "Power" 
              << std::setw(12) << "Size (n)" 
              << std::setw(18) << "MS Measured" 
              << std::setw(18) << "MS Predicted" 
              << std::setw(15) << "MS Ratio" 
              << std::setw(18) << "BS Measured" 
              << std::setw(18) << "BS Predicted" 
              << std::setw(15) << "BS Ratio" << "\n";
    std::cout << std::string(125, '-') << "\n";

    for (int k = 4; k <= 16; ++k) {
        int n = 1 << k;
        std::vector<int> arr(n);
        std::iota(arr.begin(), arr.end(), 1); // Sorted array 1..n

        // Merge Sort Verification
        merge_sort_ops = 0;
        std::vector<int> ms_arr = arr;
        mergeSort(ms_arr, 0, n - 1);
        double ms_predicted = n * std::log2(n);
        double ms_ratio = merge_sort_ops / ms_predicted;

        // Binary Search Verification
        binary_search_ops = 0;
        binarySearch(arr, -1); // Worst-case scenario search
        double bs_predicted = std::log2(n);
        double bs_ratio = binary_search_ops / bs_predicted;

        std::cout << std::left << std::setw(10) << ("2^" + std::to_string(k))
                  << std::setw(12) << n 
                  << std::setw(18) << merge_sort_ops 
                  << std::setw(18) << std::fixed << std::setprecision(1) << ms_predicted 
                  << std::setw(15) << std::setprecision(4) << ms_ratio 
                  << std::setw(18) << binary_search_ops 
                  << std::setw(18) << std::setprecision(1) << bs_predicted 
                  << std::setw(15) << std::setprecision(4) << bs_ratio << "\n";
    }
    return 0;
}