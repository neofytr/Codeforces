# maxSubarraySum

```markdown
## Documentation: Maximum Subarray Sum

This document analyzes a C++ solution for the Maximum Subarray Sum problem, often encountered in competitive programming.  The problem can be found on CSES (https://cses.fi/problemset/task/1643).

### 1. Problem Description

The problem is to find the maximum sum of any contiguous subarray within a given array of integers. The input is an array of `n` integers (positive, negative, or zero). The output should be a single integer representing the maximum possible subarray sum.

### 2. Approach Explanation

The provided code implements Kadane's Algorithm to efficiently solve the Maximum Subarray Sum problem. The algorithm processes the array once, maintaining two key variables:

*   `maxiSum`: Stores the maximum subarray sum found so far.
*   `mini`: Stores the minimum prefix sum encountered up to the current index.

The core idea is based on the following observation:

The maximum subarray sum ending at index `r` is equal to `prefix[r + 1] - min(prefix[0], ..., prefix[r])`, where `prefix[i]` represents the prefix sum up to index `i - 1` in the input array. In essence, for a subarray that spans from index `l` to `r` (inclusive), we need to find such `l` that `sum[l,r]` is maximized. So the goal is to find the smallest `prefix[l]` that `prefix[r+1] - prefix[l]` is maximized for each `r`.

The algorithm iterates through the array, updating `maxiSum` with the maximum of its current value and `prefix[r + 1] - mini`. It also updates `mini` with the minimum prefix sum encountered so far.  The use of `prefix` sum allow us to easily calculate `sum[l,r]` with `prefix[r+1] - prefix[l]`. By maintaining `mini`, it ensures we always subtract the minimum prefix sum from the current prefix sum to potentially find a larger subarray sum.

The commented-out DP solution, although correct, is less efficient due to its space complexity. Kadane's Algorithm improves on the space complexity.

### 3. Key Insights and Algorithmic Techniques Used

*   **Kadane's Algorithm:** This is the fundamental algorithm used. It efficiently calculates the maximum subarray sum in linear time.
*   **Prefix Sums:** Using prefix sums (`prefix` vector) allows for easy calculation of the sum of any subarray. `prefix[i]` stores the sum of elements from index 0 to `i-1` in the input array. The sum of the subarray from `l` to `r` can then be computed as `prefix[r + 1] - prefix[l]`.
*   **Dynamic Programming Principle (Implied):** Although the code directly implements Kadane's Algorithm in a more concise way, it implicitly leverages a dynamic programming principle. The maximum subarray sum ending at index `r` can be computed based on the maximum subarray sum ending at the previous index (`r-1`). This allows us to find the solution iteratively, building upon previously computed results.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:** O(n), where n is the size of the input array. The algorithm iterates through the array once.
*   **Space Complexity:** O(n) due to `prefix` array. However, it is possible to reduce the space complexity to O(1) by maintaining only `curr_max` and `max_so_far` without the prefix array.

### 5. Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**: This optimization disables synchronization between C++ iostreams and the C stdio library, and unties `cin` from `cout`, leading to faster input/output operations. It is essential in competitive programming environments.
*   **`#define int long long`**: This is a common trick in competitive programming to avoid integer overflow issues when dealing with large numbers. It changes the default `int` type to `long long`, effectively doubling the range of representable integer values. However, care must be taken to ensure that any required cast is done correctly.
*   **`vector<int> prefix(n + 1, 0);`**:  The `prefix` array is initialized with a size of `n+1` to simplify calculations. `prefix[0]` is always 0, representing the prefix sum of an empty subarray.  This makes the index calculations for subarray sums cleaner.
*   **`LLONG_MIN`**: Used to initialize `maxiSum` to the smallest possible `long long` value. This ensures that any valid subarray sum will be greater than the initial value, allowing the algorithm to correctly identify the maximum subarray sum.

### 6. Edge Cases Handled

*   **All Negative Numbers:** The algorithm correctly handles the case where all numbers in the input array are negative. In this case, the maximum subarray sum will be the largest (least negative) single element in the array. This is because the algorithm initializes `maxiSum` to `LLONG_MIN`.
*   **Empty Subarray is not allowed**: The solution doesn't allow empty subarray, meaning that there always will be at least one element in the subarray.

```


## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: maxSubarraySum
// URL: https://cses.fi/problemset/task/1643
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // the following is the DP solution
    /*
    // dp[r] is the maximum subarray sum among all the subarrays that end at r
    vector<int> dp(n);
    dp[0] = arr[0];
    int maxi = dp[0];
    for (int r = 1; r < n; r++) {
        dp[r] = max(dp[r - 1] + arr[r], arr[r]);
        maxi = max(maxi, dp[r]);
    }
    cout << maxi << endl;
    */

    // the following is the prefix sum solution?
    vector<int> prefix(n + 1, 0);
    for (int index = 1; index <= n; index++)
        prefix[index] = prefix[index - 1] + arr[index - 1];
    // we find the maximum subarray sum among all subarrays that end at r, for all 0<= r < n
    // for any 0 <= r < n, maximum subarray sum ending at r = max(sum[l, r] for 0 <= l < r)
    //                                                      = max(prefix[r + 1] - prefix[l] for 0 <= l <= r)
    //                                                      = prefix[r + 1] - min(prefix[l] for 0 <= l <= r)
    // so, if for each 0 <= r < n, we can have the minimum among the following {prefix[0], ..., prefix[r]}, we are done

    int mini = prefix[0];
    int maxiSum = LLONG_MIN;
    for (int r = 0; r < n; r++) {
        maxiSum = max(maxiSum, prefix[r + 1] - mini); // prefix[r + 1] - mini is the max subarray sum ending at r
        mini = min(mini, prefix[r + 1]);              // update the mini for the next round
    }
    cout << maxiSum << endl;
    return 0;
}
```

---
*Documentation generated on 2025-08-23 09:02:25*
