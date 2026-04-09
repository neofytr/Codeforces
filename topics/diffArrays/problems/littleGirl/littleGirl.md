# littleGirl

```markdown
## Code Documentation: Little Girl and Maximum Sum

This document provides a comprehensive analysis of the provided C++ code, which solves the "Little Girl and Maximum Sum" problem on Codeforces (problem C from contest 276, URL: [https://codeforces.com/contest/276/problem/C](https://codeforces.com/contest/276/problem/C)).

### 1. Problem Description (Inferred)

The problem asks us to maximize the sum obtained by multiplying elements of an array `arr` of size `n` with their corresponding frequencies.  The frequencies are determined by a set of `q` queries. Each query consists of a range `[l, r]`. For each query, we increment the frequency of all elements in `arr` from index `l` to `r` (inclusive).  The goal is to find the maximum possible sum that can be obtained by multiplying each element of `arr` with its corresponding frequency after processing all `q` queries. Crucially, the order of multiplication matters and can be arranged for maximization.

### 2. Approach Explanation

The core idea is to use the following steps:

1. **Frequency Calculation:** Use a difference array (`freq`) to efficiently calculate the frequency of each index in the original array `arr` after processing all queries. Increment `freq[l]` and decrement `freq[r+1]` for each query `[l, r]`.
2. **Prefix Sum for Frequency:** Calculate the actual frequency of each index by computing the prefix sum of the `freq` array.
3. **Sorting:** Sort the `arr` in descending order and the `freq` array (excluding the extra element at the end) in descending order. This ensures that the largest elements of `arr` are multiplied by the largest frequencies.
4. **Maximum Sum Calculation:** Calculate the maximum possible sum by iterating through both sorted arrays and multiplying corresponding elements.

### 3. Key Insights and Algorithmic Techniques Used

*   **Difference Array:** The use of the `freq` array as a difference array is a crucial optimization. Instead of iterating through the range `[l, r]` for each query and incrementing the frequency of each element, we only increment `freq[l]` and decrement `freq[r+1]`.  The prefix sum calculation then efficiently derives the actual frequencies. This reduces the complexity from O(q\*n) to O(q + n).
*   **Greedy Approach:** Sorting both arrays in descending order and multiplying corresponding elements is a greedy approach. The intuition behind this is that the largest numbers should be multiplied with the largest counts to maximize the overall sum. This stems from the Rearrangement Inequality, which states that for two sequences of numbers, sorted in the same order (or both reversed), their dot product is maximized compared to other possible arrangements.
*   **Prefix Sum:** The prefix sum technique transforms the difference array into the array containing the actual element frequencies.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Input reading: O(n + q)
    *   Difference array updates: O(q)
    *   Prefix sum calculation: O(n)
    *   Sorting `arr`: O(n log n)
    *   Sorting `freq`: O(n log n)
    *   Sum calculation: O(n)
    *   Overall: O(n + q + n log n) = **O(n log n + q)**, assuming `n` is significantly larger than a constant factor.
*   **Space Complexity:**
    *   `arr`: O(n)
    *   `freq`: O(n + 1) (effectively O(n))
    *   Other variables: O(1)
    *   Overall: **O(n)**

### 5. Important Code Patterns or Tricks Used

*   **`#define int long long`**: Using this macro replaces the default `int` type with `long long`. This is essential when dealing with larger numbers, especially when calculating sums of products, preventing potential integer overflow issues.  It's a common practice in competitive programming to use `long long` as the default integer type.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**: These lines disable synchronization between the C and C++ standard input/output streams and untie `cin` from `cout`. This significantly speeds up input/output operations, which is crucial for time-sensitive competitive programming problems.
*   **`greater<int>()`**: Used as a comparator for the `sort` function to sort in descending order.
*   **Range-based for loop**: Using `for (int &val : arr)` provides a clean and concise way to iterate over a vector and modify its elements.

### 6. Edge Cases Handled

*   The code explicitly handles the case where the input numbers and frequencies could be large, by using `long long` for the relevant variables.
*   The difference array correctly handles the edge case where `r` can be `n-1` because `freq[r+1]` is only accessed when `r+1` is less than or equal to `n`, which is ensured by the size of vector `freq`.

```


## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: littleGirl
// URL: https://codeforces.com/contest/276/problem/C
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    vector<int> freq(n + 1);
    int l, r;
    while (q--) {
        cin >> l >> r;
        l--, r--;
        freq[l] += 1;
        freq[r + 1] -= 1;
    }
    for (int r = 1; r <= n; r++)
        freq[r] += freq[r - 1];

    sort(freq.begin(), freq.end(), greater<int>());
    sort(arr.begin(), arr.end(), greater<int>());

    int sum = 0;
    for (int r = 0; r < n; r++)
        sum += freq[r] * arr[r];
    cout << sum << endl;
    return 0;
}
```

---
*Documentation generated on 2025-09-08 13:11:00*
