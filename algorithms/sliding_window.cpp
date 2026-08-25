#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int maxSubarraySum(const std::vector<int>& arr, int k) {
    int n = arr.size();
    if (n < k) return -1; // Invalid case

    // 1. Compute the sum of the first window
    int current_window_sum = 0;
    for (int i = 0; i < k; ++i) {
        current_window_sum += arr[i];
    }

    int max_sum = current_window_sum;

    // 2. Slide the window across the rest of the array
    for (int i = k; i < n; ++i) {
        // Add the next element, subtract the oldest element
        current_window_sum += arr[i] - arr[i - k];
        max_sum = std::max(max_sum, current_window_sum);
    }

    return max_sum;
}

int main() {
    std::vector<int> arr = {2, 1, 5, 1, 3, 2};
    int k = 3;
    std::cout << "Max sum of " << k << " elements: " << maxSubarraySum(arr, k) << "\n";
    // Output: 9 (from substring {5, 1, 3})
    return 0;
}