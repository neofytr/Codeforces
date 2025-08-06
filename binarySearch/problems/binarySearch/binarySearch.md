# binarySearch

```markdown
# Binary Search Solution Documentation

This document describes the solution to the "binarySearch" problem, found at [https://codeforces.com/edu/course/2/lesson/6/1/practice/contest/283911/problem/A](https://codeforces.com/edu/course/2/lesson/6/1/practice/contest/283911/problem/A).

## 1. Problem Description (Inferred)

Given a sorted array `arr` of `n` integers and `k` queries, for each query `x`, determine whether `x` is present in the array.

## 2. Approach Explanation

The problem is solved using binary search.  For each query `x`, a binary search is performed on the sorted array `arr`. The binary search aims to find an element equal to `x`. A specifically designed binary search template that maintains invariants is used to facilitate the search for `x`.

## 3. Key Insights and Algorithmic Techniques Used

*   **Binary Search:** The core algorithm is binary search, which is efficient for searching in sorted arrays. The key is to narrow down the search space in each iteration by comparing the middle element with the target value.

*   **Invariant Maintenance:** This code uses a specific binary search template that maintains the following invariants:
    *   `arr[left] <= x`
    *   `arr[right] > x`
    *   Initially, `left = -1` and `right = n`. This ensures that the invariants hold at the start of the loop.

*   **Half-Open Interval:** The range `[left + 1, right - 1]` represents the possible indices where `x` might be found.  The loop continues as long as `right != left + 1`, meaning there are still elements to consider between `left` and `right`.

*   **Preventing Integer Overflow:** The calculation `mid = left + (right - left) / 2` is used to prevent integer overflow when calculating the middle index, especially for large arrays.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Sorting the array (if it wasn't already sorted) would take O(n log n) time.  However, this problem provides the array as sorted.
    *   The binary search for each query takes O(log n) time.
    *   Since there are `k` queries, the total time complexity is O(k log n).

*   **Space Complexity:**
    *   The space complexity is O(n) due to storing the input array `arr`. The other variables use constant space. Therefore, the overall space complexity is O(n).

## 5. Important Code Patterns or Tricks Used

*   **Binary Search Template:** The specific implementation of binary search with `left = -1` and `right = n` and the invariant maintenance is a common and robust template.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:**  This is a standard optimization technique in C++ competitive programming to speed up input/output operations by disabling synchronization between C++ streams and the C standard input/output.

## 6. Edge Cases Handled

*   **Target Value Not Found:** The code handles the case where the target value `x` is not found in the array. The conditions `left == -1` (all elements are > x) and `arr[left] != x` (the largest element less than or equal to x isn't actually equal to x) indicate that `x` is not present in the array.
*   **Target Value Smaller Than All Elements:** The case where `x` is smaller than all elements in the array is explicitly handled by the condition `left == -1`.
*   **Target Value Larger Than All Elements:** This case is implicitly handled because if `x` is larger than all elements, the binary search will converge to `left = n - 1` and `arr[left] <= x` condition is checked.


## Original Code
```cpp
#include <bits/stdc++.h>
#include <vector>
using namespace std;

// Problem: binarySearch
// URL: https://codeforces.com/edu/course/2/lesson/6/1/practice/contest/283911/problem/A
// Difficulty: easy
// Tags:
// Strategy:

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    int x;
    while (k--) {
        cin >> x;
        int left = -1; // arr[left] <= x
        int right = n; // arr[right] > x

        while (right != left + 1) {
            int mid = left + (right - left) / 2;
            if (arr[mid] <= x)
                left = mid;
            else
                right = mid;
        }

        if (left == -1) {
            // all elements in the array are > x
            cout << "NO\n";
        } else if (arr[left] != x) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }
    return 0;
}
```

---
*Documentation generated on 2025-08-06 18:41:27*
