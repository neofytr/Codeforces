# subarraySumsTwo

```markdown
## Subarray Sums II - Documentation

This document provides a comprehensive analysis of the C++ solution for the "Subarray Sums II" problem on CSES (https://cses.fi/problemset/task/1661).

### 1. Problem Description

Given an array of `n` integers and a target sum `x`, the problem asks us to find the number of subarrays whose sum equals `x`.

### 2. Approach Explanation

The solution utilizes a prefix sum approach combined with a hash map to efficiently count the number of subarrays with the target sum.

The core idea is:

*   **Prefix Sums:** Calculate the prefix sum for each element in the array. A subarray sum can then be represented as the difference between two prefix sums.  Specifically, the sum of the subarray from index `i` to `j` is `prefixSum[j] - prefixSum[i-1]` (assuming `prefixSum[-1] = 0`).

*   **Hash Map (Frequency Counter):** Maintain a hash map (`freq`) that stores the frequency of each prefix sum encountered so far.  `freq[sum]` represents the number of times the prefix sum `sum` has occurred up to the current index.

*   **Counting Subarrays:** For each index `i`, the algorithm calculates the current prefix sum `sum`. To find subarrays ending at index `i` with sum `x`, we need to find a previous prefix sum `prefixSum[j]` such that `sum - prefixSum[j] = x`.  This can be rearranged to `prefixSum[j] = sum - x`.  By looking up the frequency of `sum - x` in the hash map `freq`, we can determine the number of such `prefixSum[j]` values, and thus the number of subarrays ending at `i` with sum `x`.

### 3. Key Insights and Algorithmic Techniques

*   **Prefix Sum Transformation:** The problem is transformed from finding subarrays with a specific sum to finding pairs of prefix sums with a specific difference. This is a standard technique for subarray sum related problems.

*   **Hash Map for Efficient Counting:** Instead of iterating through all possible starting points for a subarray ending at the current index, the hash map allows us to efficiently count the number of relevant previous prefix sums in O(1) average time complexity.

*   **Custom Hash Function:**  The code uses a custom hash function (`custom_hash`). This is likely to mitigate potential hash collisions, especially in online judge environments where there may be adversarial test cases designed to trigger worst-case hash map performance.  The SplitMix64 algorithm and the use of `chrono::steady_clock` to seed the hash function are intended to improve distribution and randomness of the hash values.

*   **Inclusion of 0 in the Hashmap:** The hashmap is initialized with `freq[0] = 1`. This accounts for cases where the subarray starts from the beginning of the array (i.e., the prefix sum before the start is 0).  If a subarray from index 0 to `i` has sum `x`, then `prefixSum[i] = x`, which means `prefixSum[i] - x = 0`. Thus, `freq[0]` keeps track of the number of times the prefix sum of 0 has occurred, i.e., before any element is processed.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:** O(n) - The code iterates through the array once to calculate the prefix sums and update the hash map. The hash map operations (insertion and lookup) take O(1) on average due to the usage of unordered map.
*   **Space Complexity:** O(n) - In the worst case, the hash map may store all prefix sums, which could be up to `n` distinct values.

### 5. Important Code Patterns or Tricks Used

*   **Prefix Sum Calculation within the Loop:** The prefix sum is calculated iteratively inside the main loop. This avoids the need to pre-compute the entire prefix sum array, saving memory and potentially improving performance. This is possible because we only need the cumulative sum up to the current iteration.

*   **`unordered_map` with Custom Hash:**  Using `unordered_map` provides fast lookups (average O(1) time).  The custom hash function (`custom_hash`) is implemented to reduce the likelihood of hash collisions, which could degrade performance to O(n) in the worst case.  Using this custom hash function is a good practice in competitive programming.

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This is a standard optimization technique in C++ competitive programming to disable synchronization between the C and C++ standard input/output streams, potentially improving input/output performance.

### 6. Edge Cases Handled

*   **Empty Subarray (Prefix Sum of 0):** The code correctly handles cases where the subarray starts from the beginning of the array because the hash map is initialized with `freq[0] = 1`.

*   **Integer Overflow:** The problem statement and the data types used (`long long`) suggest that integer overflow is a potential concern. Using `long long` helps to mitigate this.

In summary, the solution provides an efficient and well-optimized approach to solving the "Subarray Sums II" problem. The use of prefix sums, a hash map, and a custom hash function are key elements that contribute to its performance and robustness.
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
    // for each index we count the number of subarrays (starting at zero) whose sum is target
    // each such subarray forms s good segment with the current index
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
*Documentation generated on 2025-08-22 14:09:50*
