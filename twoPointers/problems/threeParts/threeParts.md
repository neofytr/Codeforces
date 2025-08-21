# threeParts

```markdown
## Documentation for Codeforces Problem 1006C: Three Parts

This document provides a comprehensive analysis of a C++ solution to Codeforces Problem 1006C, titled "Three Parts" (available at [https://codeforces.com/problemset/problem/1006/C](https://codeforces.com/problemset/problem/1006/C)).

### 1. Problem Description

Given an array `arr` of `n` integers, find the maximum possible sum `s` such that the array can be partitioned into three contiguous parts `A`, `B`, and `C` such that `sum(A) = sum(C) = s`.  In other words, find the largest `s` such that there exists indices `i` and `j` with `0 <= i < j < n` satisfying:

*   `sum(arr[0...i]) = s`
*   `sum(arr[j...n-1]) = s`

If no such sum exists, output 0.

### 2. Approach Explanation

The solution uses a two-pointer approach combined with prefix and suffix sum arrays to efficiently find the maximum sum `s`.  The main idea is to maintain two pointers, `l` and `r`, initially pointing to the start and end of the array, respectively.  The prefix sum array `prefix` stores the cumulative sum from the beginning of the array up to each index, and the suffix sum array `suffix` stores the cumulative sum from the end of the array up to each index.

The algorithm iterates while `l < r`. In each iteration, it compares `prefix[l]` and `suffix[r]`:

*   If `prefix[l] < suffix[r]`, it means the sum of the left part is smaller than the sum of the right part.  Therefore, the left pointer `l` is incremented to try to increase the left sum.
*   If `prefix[l] > suffix[r]`, it means the sum of the left part is larger than the sum of the right part. Therefore, the right pointer `r` is decremented to try to increase the right sum.
*   If `prefix[l] == suffix[r]`, it means we've found a possible common sum. The maximum sum `maxi` is updated with `prefix[l]` (or equivalently `suffix[r]`), and both `l` and `r` are moved inwards to search for potentially larger sums.

Finally, the algorithm outputs the maximum sum `maxi` found.

### 3. Key Insights and Algorithmic Techniques Used

*   **Prefix and Suffix Sums:**  Pre-calculating the prefix and suffix sums allows for efficient calculation of the sum of any contiguous subarray in O(1) time. This is crucial for quickly comparing the sums of the left and right parts.
*   **Two-Pointer Approach:** The two-pointer technique efficiently searches for the desired condition (equal sums on both sides) while minimizing the number of iterations. By moving the pointers based on the comparison of the prefix and suffix sums, the algorithm avoids unnecessary computations.
*   **Greedy Optimization:**  When `prefix[l] == suffix[r]`, it's optimal to update `maxi` with this sum and move both pointers. This is because any further partitioning with these same `l` or `r` will only result in smaller equal sums since the array elements are assumed to be non-negative (implicitly, since no conditions are stated against this, and the sums can be 0).

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Calculating prefix and suffix sums takes O(n) time.
    *   The two-pointer iteration takes O(n) time in the worst case, as both pointers can move through the entire array.
    *   Therefore, the overall time complexity is O(n).
*   **Space Complexity:**
    *   The `arr`, `prefix`, and `suffix` vectors each take O(n) space.
    *   Other variables take constant space O(1).
    *   Therefore, the overall space complexity is O(n).

### 5. Important Code Patterns or Tricks Used

*   **`#define int long long`:** This macro is used to redefine `int` as `long long`, which can prevent integer overflow issues when dealing with large sums. This is a common practice in competitive programming to avoid potential runtime errors.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** These lines are used to speed up input/output operations by disabling synchronization between the C++ standard input/output streams and the C standard input/output streams.  This can significantly improve the performance of the program, especially when dealing with large input data.
*   **Range-based for loop for input:** The code utilizes a range-based for loop for reading the input array, which is a concise and readable way to iterate through the array.

### 6. Any Edge Cases Handled

The provided code implicitly handles the following edge cases:

*   **Empty array or array with a single element:**  The loop `while (l < r)` prevents the algorithm from attempting to access elements outside the bounds of the array when n is very small.  The initial value of `maxi` is 0, which is correct for such cases.
*   **No common sum exists:**  If no common sum is found, the `maxi` variable will remain 0, which is the correct output.
*   **Array elements being zero:** Zero elements are correctly handled because the prefix and suffix sums will include them, and the comparison logic still holds.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: threeParts
// URL: https://codeforces.com/problemset/problem/1006/C
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

    vector<int> prefix(n, 0);
    vector<int> suffix(n + 1, 0);

    prefix[0] = arr[0];
    for (int index = 1; index < n; index++)
        prefix[index] = prefix[index - 1] + arr[index];
    for (int index = n - 1; index >= 0; index--)
        suffix[index] = suffix[index + 1] + arr[index];

    int l = 0, r = n - 1;
    int maxi = 0;
    while (l < r) {
        if (prefix[l] < suffix[r])
            l++;
        else if (prefix[l] > suffix[r])
            r--;
        else {
            maxi = max(maxi, prefix[l]);
            l++;
            r--;
        }
    }

    cout << maxi << endl;

    return 0;
}
```

---
*Documentation generated on 2025-08-21 21:49:33*
