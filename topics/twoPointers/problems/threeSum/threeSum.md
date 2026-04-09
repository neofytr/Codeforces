# threeSum

```markdown
## Three Sum Problem Documentation

This document provides a comprehensive analysis of the provided C++ solution for the "Three Sum" problem, available on CSES (https://cses.fi/problemset/task/1641).

### 1. Problem Description

The "Three Sum" problem on CSES asks to find three distinct indices in a given array of integers whose sum is equal to a target value `x`.  If such a triplet exists, the program should output the corresponding indices separated by spaces. If no such triplet exists, the program should output "IMPOSSIBLE".

Specifically, given an array `arr` of `n` integers and a target value `x`, the task is to find three *distinct* indices `i`, `j`, and `k` (1-indexed) such that `arr[i] + arr[j] + arr[k] == x`.

### 2. Approach Explanation

The provided solution employs a combination of sorting and the two-pointer technique to efficiently find the desired triplet.

1.  **Preprocessing:**
    *   The input array `arr` is read along with its size `n` and the target sum `x`. Crucially, along with the value of each element, the *original index* of the element is also stored in a `pair<int, int>`. This is essential for outputting the original indices if a solution is found.
    *   The array `arr` (containing the element and its original index) is then sorted based on the element value. This sorting step is crucial for the two-pointer approach.

2.  **Iteration and Two-Pointer Search:**
    *   The code iterates through the sorted array using a `for` loop (index `i`). For each element `arr[i]`, it attempts to find two other elements in the remaining part of the array that sum up to `x - arr[i].first`.
    *   A two-pointer technique is used within the `for` loop.  `left` pointer starts from `i + 1` and `right` pointer starts from `n - 1`.
    *   The `while` loop continues as long as `left < right`.  Inside the `while` loop:
        *   The sum `s` of `arr[left].first` and `arr[right].first` is calculated.
        *   If `s < sum` (where `sum` is `x - arr[i].first`), the `left` pointer is incremented to consider a larger value.
        *   If `s > sum`, the `right` pointer is decremented to consider a smaller value.
        *   If `s == sum`, a solution is found! The original indices of `arr[i]`, `arr[left]`, and `arr[right]` are outputted, and the program exits successfully.

3.  **No Solution:**
    *   If the outer `for` loop completes without finding a solution, it means no such triplet exists. In this case, the program outputs "IMPOSSIBLE".

### 3. Key Insights and Algorithmic Techniques Used

*   **Sorting:** Sorting the input array is essential to enable the efficient two-pointer technique.  The sorting is done on a vector of pairs. The first element of the pair represents the number, and the second element stores the original index.
*   **Two-Pointer Technique:** The two-pointer technique is a classic approach for finding pairs in a sorted array that satisfy a certain condition. In this case, it efficiently searches for the two numbers that sum up to the required value (`x - arr[i].first`).  The crucial point is that the array *must* be sorted for the two-pointer technique to work correctly.
*   **Index Preservation:**  The solution cleverly stores the original indices of the array elements before sorting. This is crucial for meeting the problem's requirement of outputting the original indices of the found elements.  Using a `vector<pair<int, int>>` is a good way to associate the value and the index of each element.
*   **Reduction to Two Sum:** The three-sum problem is effectively reduced to multiple instances of the two-sum problem. By iterating through each element `arr[i]` and searching for two other elements that sum to `x - arr[i]`, the problem is broken down into smaller, manageable subproblems.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Sorting the array takes O(n log n) time.
    *   The outer `for` loop iterates `n` times.
    *   The `while` loop (two-pointer technique) takes at most O(n) time in each iteration of the `for` loop.
    *   Therefore, the overall time complexity is dominated by the sorting step and the nested loops, resulting in O(n log n + n * n) = O(n<sup>2</sup>).

*   **Space Complexity:**
    *   The solution uses a `vector<pair<int, int>> arr` of size `n` to store the input array and its indices.
    *   Therefore, the space complexity is O(n).

### 5. Important Code Patterns or Tricks Used

*   **`pair<int, int>` for Index Tracking:**  Using `std::pair` is a neat trick to keep track of the original index alongside the value during sorting. This avoids the need for separate index tracking mechanisms.
*   **Early Exit:** The `return EXIT_SUCCESS` statement inside the `while` loop immediately terminates the program once a solution is found. This improves efficiency, especially when a solution is likely to be found early in the search.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**: These lines are standard optimizations in competitive programming to speed up input/output operations by disabling synchronization between C++ streams and the C standard input/output.

### 6. Any Edge Cases Handled

The solution implicitly handles the case where no solution exists by outputting "IMPOSSIBLE" if the outer `for` loop completes without finding a suitable triplet. The use of distinct indices is also inherently handled by the fact that `left` starts at `i + 1`.

However, if the prompt had required distinct *values* (not just distinct *indices*), then extra steps would have to be taken to ensure only combinations of distinct values are considered.  This particular problem only considers that `i`, `j`, and `k` must be different indices; there is no restriction that `arr[i]`, `arr[j]`, and `arr[k]` must be different values.
```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

#define int long long

// Problem: threeSum
// URL: https://cses.fi/problemset/task/1641
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    cin >> n >> x;
    vector<pair<int, int>> arr(n);
    int index = 1;
    for (auto &val : arr) {
        cin >> val.first;
        val.second = index++;
    }

    // all elements of the array are non-negative
    // we are to find three distinct indexes in arr with sum == x
    sort(arr.begin(), arr.end());
    for (int i = 0; i < n; i++) {
        int sum = x - arr[i].first;
        int left = i + 1;
        int right = n - 1;
        while (left < right) {
            int s = arr[left].first + arr[right].first;
            if (s < sum)
                left++;
            else if (s > sum)
                right--;
            else {
                cout << arr[i].second << " " << arr[left].second << " " << arr[right].second << endl;
                return EXIT_SUCCESS;
            }
        }
    }
    cout << "IMPOSSIBLE\n";
    return 0;
}
```

---
*Documentation generated on 2025-08-16 20:23:21*
