# numPairs

```markdown
## Documentation for Competitive Programming Solution

This document provides a comprehensive analysis of the provided C++ code snippet, which solves the "numPairs" problem on Codeforces (problemset/problem/1538/C).

### 1. Problem Description

Given an array `arr` of `n` integers and two integers `l` and `r`, the problem asks to find the number of pairs `(i, j)` such that `0 <= i < j < n` and `l <= arr[i] + arr[j] <= r`.

URL: [https://codeforces.com/problemset/problem/1538/C](https://codeforces.com/problemset/problem/1538/C)

### 2. Approach Explanation

The solution employs the following strategy:

1.  **Sort the Array:** The input array `arr` is sorted in ascending order. Sorting enables efficient searching using binary search (upper\_bound).
2.  **Count Pairs with Sum <= r:** The `count` function determines the number of pairs whose sum is less than or equal to `r`.
3.  **Count Pairs with Sum < l:**  Similarly, the `count` function is used to find the number of pairs whose sum is less than `l`.
4.  **Subtract to Find the Difference:**  The final answer is calculated by subtracting the count of pairs with sum less than `l` from the count of pairs with sum less than or equal to `r`.  This provides the number of pairs with sum in the range `[l, r]`.

The `count` function iterates through each element `arr[left]` in the sorted array.  For each `arr[left]`, it calculates the `target` value as `bound - arr[left]`. It then uses `upper_bound` to find the index of the first element in the subarray `arr[left+1, n)` that is *greater* than `target`.  The number of elements from `arr[left+1]` up to (but not including) that index represents the number of elements `arr[j]` such that `arr[left] + arr[j] <= bound` and `left < j`.

### 3. Key Insights and Algorithmic Techniques Used

*   **Sorting:** Sorting the array is crucial for applying binary search.
*   **Binary Search (upper\_bound):** The `upper_bound` function efficiently finds the number of elements greater than a specific value in a sorted range. This technique significantly reduces the time complexity compared to a linear search.
*   **Inclusion-Exclusion Principle:** The problem utilizes the inclusion-exclusion principle. By calculating the number of pairs satisfying `arr[i] + arr[j] <= r` and subtracting the number of pairs satisfying `arr[i] + arr[j] < l`, we accurately determine the number of pairs falling within the range `[l, r]`.  This avoids directly counting pairs in the desired range, which could be more complex.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Sorting the array takes O(n log n) time.
    *   The `count` function iterates through the array `n` times, and within each iteration, `upper_bound` takes O(log n) time. Thus, `count` function is O(n log n).
    *   The `solve` function calls `count` twice and is thus O(n log n).
    *   Since `solve` is called `t` times, the overall time complexity is O(t * n log n).

*   **Space Complexity:**
    *   The `arr` vector takes O(n) space.
    *   The sorting algorithm might use some auxiliary space, but often it's O(log n) or O(n) depending on the implementation.
    *   Overall, the space complexity is O(n).

### 5. Important Code Patterns or Tricks Used

*   **`#define int long long`:** This is a common practice in competitive programming to avoid integer overflow issues, especially when dealing with large numbers or products. It redefines `int` as `long long`, which has a larger range.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This optimization technique disables synchronization between C and C++ standard streams and unties `cin` from `cout`, which can significantly improve input/output performance.
*   **Using `upper_bound`:** This is a standard binary search algorithm that efficiently finds the upper bound of a value in a sorted range. It simplifies the logic for counting the number of pairs within a specified range.  Using `itr - arr.begin()` to calculate the index returned by `upper_bound` is a common idiom.

### 6. Any Edge Cases Handled

The code implicitly handles the following edge cases:

*   **Empty Array:** If the input array is empty (`n = 0`), the `count` function will correctly return 0 because the outer loop won't execute.
*   **`l > r`:** If `l` is greater than `r`, the result will be `count(arr, r) - count(arr, l - 1)`. This ensures correct handling, potentially returning a negative value if `count(arr, l - 1) > count(arr, r)`, although this isn't necessarily an *error* but rather a mathematical outcome based on the given parameters.  The prompt doesn't exclude the possibility of `l > r`.
*   **Duplicate Values:** The `upper_bound` correctly handles duplicate values in the array because it searches for the first element *greater* than the target.
*   **Values of l and r outside a reasonable range:** Although not handled specifically, since `int` is redefined as `long long`, the calculations are much less likely to overflow unless `l` or `r` are *extremely* large.  However, this is still a consideration that would depend on the specific problem constraints. The use of `long long` gives a much wider latitude than simply using a 32-bit integer.

**Learning Points:**

*   This problem is a great example of how sorting and binary search can be combined to efficiently solve counting problems.
*   The inclusion-exclusion principle can simplify complex counting problems by breaking them down into smaller, more manageable subproblems.
*   The use of `#define int long long` and disabling stream synchronization are valuable optimizations for competitive programming.
*   Understanding the behavior of standard library functions like `upper_bound` is crucial for writing efficient and correct code.
```

## Original Code
```cpp
#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

// Problem: numPairs
// URL: https://codeforces.com/problemset/problem/1538/C
// Difficulty: medium
// Tags:
// Strategy:

int count(vector<int> &arr, int bound) {
    // we want to count the number of pairs (i, j) where 0 <= i < j < n such that arr[i] + arr[j] <= bound
    int cnt = 0;
    int n = arr.size();

    for (int left = 0; left < n; left++) {
        int target = bound - arr[left];
        // search only in the range [left+1, end)
        auto itr = upper_bound(arr.begin() + left + 1, arr.end(), target);
        int index = itr - arr.begin();
        cnt += (index - (left + 1));
    }

    return cnt;
}

void solve() {
    int n, l, r;
    cin >> n >> l >> r;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    sort(arr.begin(), arr.end());
    // we are to find the number of pairs (i, j) such that 0 <= i < j < n where l <= arr[i] + arr[j] <= r
    // we count the number of pairs with sum <= r and then subtract the pairs with sum < l

    cout << count(arr, r) - count(arr, l - 1) << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
```

---
*Documentation generated on 2025-08-11 17:50:43*
