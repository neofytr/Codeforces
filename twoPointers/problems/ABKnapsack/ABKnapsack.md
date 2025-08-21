# ABKnapsack

```markdown
# ABKnapsack Problem Documentation

This document provides comprehensive documentation for the C++ solution of the "ABKnapsack" problem, accessible at [https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/H](https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/H).

## 1. Problem Description

Given:

*   `n`: Number of items of type A.
*   `m`: Number of items of type B.
*   `s`: Maximum weight capacity of the knapsack.
*   `A`: Weight of each item of type A.
*   `B`: Weight of each item of type B.
*   `costA`: Array of size `n` representing the costs of items of type A.
*   `costB`: Array of size `m` representing the costs of items of type B.

Objective:

Maximize the total cost of items placed in the knapsack, subject to the weight constraint `total_weight <= s`.  You can take any number of items of type A (up to `n`) and any number of items of type B (up to `m`).

## 2. Approach Explanation

The solution uses a greedy approach combined with prefix sums to efficiently find the optimal combination of items.

1.  **Sort Items:** Sort the items of type A and type B in descending order of their costs. This prioritizes taking the most valuable items first.

2.  **Prefix Sums:** Calculate the prefix sums of the costs of items of type A and type B. `prefA[i]` represents the sum of the costs of the `i` most expensive items of type A.  Similarly for `prefB`.

3.  **Iterate and Maximize:** Iterate through all possible numbers of items of type A that can be included in the knapsack (from 0 to `n`).  For each possible number `i` of type A items:
    *   Calculate the total weight of the `i` type A items.
    *   If the weight exceeds the knapsack capacity `s`, break the loop (since adding more type A items will only make the weight exceed the capacity further).
    *   Calculate the remaining weight capacity after including the `i` type A items.
    *   Determine the maximum number `j` of type B items that can be included within the remaining capacity. `j = min(m, rem / B)`.
    *   Calculate the total cost: `prefA[i] + prefB[j]`.
    *   Update the maximum cost found so far.

## 3. Key Insights and Algorithmic Techniques Used

*   **Greedy Approach:** Sorting items in descending order by cost allows us to prioritize the most valuable items. This is a crucial step.  Without sorting, the solution would not be correct. This works because the weight of each item of type A is the same, and the weight of each item of type B is the same.

*   **Prefix Sums:** Prefix sums enable efficient calculation of the total cost of the `i` most expensive items in `O(1)` time. This avoids repeatedly summing the costs within the inner loop.  This transforms an O(n^2) solution to an O(n) solution.

*   **Iteration and Optimization:**  The outer loop iterates through possible numbers of items of type A. Inside the loop, the number of type B items is determined by dividing the remaining space by the weight of each B item. The `min(m, rem / B)` prevents indexing beyond `costB` array.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Sorting `costA` and `costB`: `O(n log n + m log m)`.
    *   Calculating prefix sums: `O(n + m)`.
    *   Iterating through all possible numbers of items of type A: `O(n)`.  The calculation inside each iteration is `O(1)`.

    Therefore, the overall time complexity is `O(n log n + m log m + n + m + n) = O(n log n + m log m)`. If `n` and `m` are assumed to be the same order, time complexity would be O(n log n).

*   **Space Complexity:**
    *   `costA`: `O(n)`
    *   `costB`: `O(m)`
    *   `prefA`: `O(n)`
    *   `prefB`: `O(m)`

    Therefore, the overall space complexity is `O(n + m)`.

## 5. Important Code Patterns or Tricks Used

*   **`ios::sync_with_stdio(false); cin.tie(nullptr);`:**  This optimizes input/output operations by disabling synchronization between C++ streams and the C standard input/output streams.

*   **`#define int long long`:** This redefines the `int` data type as `long long` to handle potentially large integer values, preventing overflow issues.  This is very common in competitive programming.

*   **`sort(costA.rbegin(), costA.rend());`:** This efficiently sorts the vector `costA` in descending order. `rbegin()` and `rend()` return reverse iterators.

## 6. Any Edge Cases Handled

*   **`weightA > s`:** This check in the outer loop prevents unnecessary calculations and ensures that the weight constraint is always satisfied.
*   **`min(m, rem / B)`:** This check prevents exceeding the bounds of `costB` or `prefB` when calculating the number of type B items to include. It ensures the algorithm considers only available B items and the remaining capacity.  It also handles the case where `rem / B` is greater than `m`.
*   The prefix sums are created with an extra element (size n+1 and m+1) and initialized to 0. This handles the case where 0 A items are selected.

```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: ABKnapsack
// URL: https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/H
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s, A, B;
    cin >> n >> m >> s >> A >> B;

    vector<int> costA(n), costB(m);
    for (int &x : costA)
        cin >> x;
    for (int &x : costB)
        cin >> x;

    // Sort descending (take expensive items first)
    sort(costA.rbegin(), costA.rend());
    sort(costB.rbegin(), costB.rend());

    vector<int> prefA(n + 1, 0), prefB(m + 1, 0);
    for (int i = 0; i < n; i++)
        prefA[i + 1] = prefA[i] + costA[i];
    for (int i = 0; i < m; i++)
        prefB[i + 1] = prefB[i] + costB[i];

    int ans = 0;

    for (int i = 0; i <= n; i++) {
        int weightA = i * A;
        if (weightA > s)
            break; // too heavy already

        int rem = s - weightA;
        int j = min(m, rem / B);
        ans = max(ans, prefA[i] + prefB[j]);
    }

    cout << ans << "\n";
    return 0;
}

```

---
*Documentation generated on 2025-08-21 20:41:55*
