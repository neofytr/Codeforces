# subarraySumsTwo

```markdown
## Competitive Programming Solution Documentation: Subarray Sums Divisible by K

This document provides a comprehensive analysis of the provided C++ code, which solves the "Subarray Sums II" problem on CSES (https://cses.fi/problemset/task/1661). The problem asks us to count the number of subarrays of a given array whose sum equals a target value `x`.

### 1. Problem Description

Given an array `arr` of `n` integers and a target sum `x`, the problem requires us to find the number of subarrays of `arr` whose elements sum up to `x`.

### 2. Approach Explanation

The code utilizes a prefix sum based approach combined with a hash map to efficiently count the number of subarrays with the desired sum.  The core idea is as follows:

*   Let `prefixSum[i]` be the sum of elements from `arr[0]` to `arr[i]`.
*   A subarray `arr[j...i]` has a sum of `x` if and only if `prefixSum[i] - prefixSum[j-1] = x`.  (Note: `prefixSum[-1] = 0`)
*   Rearranging the equation, we get `prefixSum[j-1] = prefixSum[i] - x`.
*   Therefore, to find the number of subarrays ending at index `i` with sum `x`, we need to find the number of prefix sums `prefixSum[j-1]` (where `j <= i`) that are equal to `prefixSum[i] - x`.
*   We can efficiently count the occurrences of different prefix sums using a hash map (`freq` in the code).  For each prefix sum `prefixSum[i]`, we check how many times `prefixSum[i] - x` has appeared previously.  This gives us the number of subarrays ending at `i` with sum `x`.

The algorithm iterates through the array, maintains the current prefix sum, and uses the hash map to count the subarrays that end at the current index and have the target sum.

### 3. Key Insights and Algorithmic Techniques Used

*   **Prefix Sums:**  The fundamental concept of prefix sums allows for efficient computation of subarray sums.  Instead of iterating through all possible subarrays and calculating their sums, prefix sums provide a way to calculate a subarray sum in O(1) time.
*   **Hash Map for Frequency Counting:** The `unordered_map` (with a custom hash function to mitigate potential hash collisions) is used to store the frequency of prefix sums encountered so far. This allows us to quickly check how many times a particular prefix sum (specifically, `prefixSum[i] - x`) has occurred, which directly translates to the number of subarrays ending at index `i` with the desired sum.
*   **Equation Manipulation:** The key insight is to rearrange the prefix sum equation (`prefixSum[i] - prefixSum[j-1] = x`) to `prefixSum[j-1] = prefixSum[i] - x`.  This formulation allows us to use the hash map to efficiently count the number of suitable starting points (`j-1`) for subarrays ending at `i`.
*   **Custom Hash Function:** The code uses a custom hash function (`custom_hash`) to improve the performance of the `unordered_map`. This is especially important when dealing with large datasets where hash collisions can significantly degrade performance.  The SplitMix64 algorithm is used for hash function generation.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:** The algorithm iterates through the array once (O(n)), and for each element, it performs a constant-time operation (hash map lookup and update). Therefore, the overall time complexity is **O(n)**.
*   **Space Complexity:** The hash map `freq` stores the frequency of prefix sums. In the worst case, all prefix sums could be distinct, requiring O(n) space.  Therefore, the space complexity is **O(n)**.

### 5. Important Code Patterns or Tricks Used

*   **In-place Prefix Sum Calculation:** Instead of creating a separate prefix sum array, the code maintains the current prefix sum in the `sum` variable. This saves memory and simplifies the code.
*   **Initialization of `freq[0] = 1`:** The `freq[0] = 1` initialization is crucial. It accounts for the case where a subarray starting from index 0 has the target sum `x`.  When the prefix sum `sum` equals `x` at some index `i`, `sum - x` will be 0.  Without initializing `freq[0]` to 1, these subarrays will not be counted.  This handles the edge case of subarrays starting at index 0.
*   **Custom Hash Function:** Using a custom hash function like `custom_hash` can be a useful optimization technique when dealing with `unordered_map` in competitive programming. It helps in preventing hash collisions, which can significantly improve the performance of the code, especially on large datasets or when dealing with specific types of keys.

### 6. Edge Cases Handled

*   **Subarrays starting from index 0:** The initialization `freq[0] = 1` handles the case where a subarray starting from the beginning of the array has the desired sum.
*   **Empty subarray not applicable in this problem:** The problem seeks count of non-empty subarrays summing to x. The provided code correctly accounts for the case where the entire array sums to 0 when x=0 and avoids any false counting of empty subarrays.

In summary, the code provides an efficient and well-structured solution to the subarray sums divisible by k problem. It demonstrates the effective use of prefix sums, hash maps, and a custom hash function for optimization.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: subarraySumsTwo
// URL: https://cses.fi/problemset/task/1661
// Difficulty: medium
// Tags:
// Strategy:

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    cin >> n >> x;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // we are to count the number of subarrays with target sum x
    unordered_map<int, int, custom_hash> freq; // freq[r] denotes the number of subarrays starting from 0 until the current iteration have their sum = r
    freq[0] = 1;
    int count = 0;
    int sum = 0;
    for (int index = 0; index < n; index++) {
        // pref[a + 1] - x = pref[b]
        sum += arr[index]; // since we only need sums until the current iteration to do our job, no need to build the whole prefix array before
        int target = sum - x;
        count += freq[target];
        freq[sum]++;
    }
    cout << count << endl;
    return 0;
}
```

---
*Documentation generated on 2025-08-22 14:08:41*
