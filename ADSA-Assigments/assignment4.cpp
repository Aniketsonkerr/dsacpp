// #include <iostream>
// #include <vector>
// #include <cstdlib>
// #include <ctime>

// using namespace std;

// // Rearranges the array elements to maintain the max heap property
// void heapify(vector<int>& arr, int size, int root) {
//     int largest = root;
//     int leftChild = 2 * root + 1;
//     int rightChild = 2 * root + 2;

//     // Check if left child is larger than root
//     if (leftChild < size && arr[leftChild] > arr[largest]) {
//         largest = leftChild;
//     }

//     // Check if right child is larger than current largest
//     if (rightChild < size && arr[rightChild] > arr[largest]) {
//         largest = rightChild;
//     }

//     // If largest is not root, swap and continue heapifying
//     if (largest != root) {
//         swap(arr[root], arr[largest]);
//         heapify(arr, size, largest);
//     }
// }

// // Main Heap Sort function
// void heapSort(vector<int>& arr) {
//     int n = arr.size();

//     // Step 1: Build the max heap from the array
//     for (int i = n / 2 - 1; i >= 0; i--) {
//         heapify(arr, n, i);
//     }

//     // Step 2: Extract elements one by one from the heap
//     for (int i = n - 1; i > 0; i--) {
//         // Move current root (maximum element) to the end
//         swap(arr[0], arr[i]);

//         // Call heapify on the reduced heap
//         heapify(arr, i, 0);
//     }
// }

// // Helper to check if array is correctly sorted
// bool checkSorted(const vector<int>& arr) {
//     for (size_t i = 1; i < arr.size(); i++) {
//         if (arr[i - 1] > arr[i]) {
//             return false;
//         }
//     }
//     return true;
// }

// int main() {
//     int sizes[] = {100, 500, 1000, 5000, 10000};
//     int numSizes = 5;

//     cout << "--- HEAP SORT BENCHMARK ---" << endl;

//     for (int k = 0; k < numSizes; k++) {
//         int n = sizes[k];
//         vector<int> arr(n);

//         // Fill array with random values
//         for (int i = 0; i < n; i++) {
//             arr[i] = rand() % 10000;
//         }

//         // Measure execution time using clock()
//         clock_t start = clock();
//         heapSort(arr);
//         clock_t end = clock();

//         double timeTaken = double(end - start) / CLOCKS_PER_SEC * 1000.0; // in ms
//         bool passed = checkSorted(arr);

//         cout << "Input size (n): " << n 
//              << " | Time: " << timeTaken << " ms"
//              << " | Correctly Sorted: " << (passed ? "Yes" : "No") << endl;
//     }

//     return 0;
// }

// #include <iostream>
// #include <vector>
// #include <algorithm>

// using namespace std;

// void solveKnapsack(const vector<int>& weights, const vector<int>& values, int capacity) {
//     int n = weights.size();

//     // Create a DP table of size (n+1) x (capacity+1) initialized to 0
//     vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

//     // Build table in a bottom-up manner
//     for (int i = 1; i <= n; i++) {
//         for (int w = 1; w <= capacity; w++) {
//             if (weights[i - 1] <= w) {
//                 // Choice: include item i-1 or exclude it
//                 dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
//             } else {
//                 dp[i][w] = dp[i - 1][w];
//             }
//         }
//     }

//     cout << "Maximum total value: " << dp[n][capacity] << endl;

//     // Trace back to find which items were picked
//     vector<int> selectedItems;
//     int currentCap = capacity;

//     for (int i = n; i > 0; i--) {
//         // If value came from including item i-1
//         if (dp[i][currentCap] != dp[i - 1][currentCap]) {
//             selectedItems.push_back(i - 1); // Save 0-based index
//             currentCap -= weights[i - 1];
//         }
//     }

//     // Print chosen items
//     cout << "Selected items (0-indexed): ";
//     for (int i = selectedItems.size() - 1; i >= 0; i--) {
//         cout << selectedItems[i] << " ";
//     }
//     cout << endl << endl;

//     // Print the DP Table
//     cout << "DP Matrix:" << endl;
//     for (int i = 0; i <= n; i++) {
//         for (int w = 0; w <= capacity; w++) {
//             cout << dp[i][w] << "\t";
//         }
//         cout << endl;
//     }
// }

// int main() {
//     vector<int> weights = {2, 3, 4, 5};
//     vector<int> values = {3, 4, 5, 6};
//     int capacity = 5;

//     cout << "--- 0/1 KNAPSACK DEMO ---" << endl;
//     solveKnapsack(weights, values, capacity);

//     return 0;
// }

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Runs Knapsack algorithm to measure runtime performance
int knapsack(const vector<int>& weights, const vector<int>& values, int capacity) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][capacity];
}

int main() {
    // Array of inputs: {number of items, capacity}
    int itemCounts[] = {10, 50, 100, 200, 500};
    int capacities[] = {50, 200, 500, 1000, 2000};
    int numTests = 5;

    cout << "--- KNAPSACK EXECUTION TIMING ---" << endl;

    for (int k = 0; k < numTests; k++) {
        int n = itemCounts[k];
        int W = capacities[k];

        vector<int> weights(n);
        vector<int> values(n);

        // Generate sample item data
        for (int i = 0; i < n; i++) {
            weights[i] = (rand() % 30) + 1;
            values[i] = (rand() % 100) + 10;
        }

        clock_t start = clock();
        knapsack(weights, values, W);
        clock_t end = clock();

        double duration = double(end - start) / CLOCKS_PER_SEC * 1000.0; // in ms

        cout << "Items (n): " << n 
             << " | Capacity (W): " << W 
             << " | Execution Time: " << duration << " ms" << endl;
    }

    return 0;
}