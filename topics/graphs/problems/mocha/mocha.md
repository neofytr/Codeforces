# mocha

```markdown
## Codeforces Problem 1559C: Mocha and Math

This document provides a comprehensive analysis of a C++ solution to Codeforces Problem 1559C, "Mocha and Math" (https://codeforces.com/problemset/problem/1559/C).

### 1. Problem Description

Given an array `a` of length `n` consisting of 0s and 1s. We need to construct a permutation of integers from 1 to `n+1` such that for each pair of consecutive numbers `x` and `y` in the permutation, there is a directed edge from `x` to `y` if `x < y` and the `x`-th element of the input array `a` is 0 or `x > y` and the `x`-th element of the input array `a` is 1. Essentially, the array `a` represents the constraints on the directed edges in a graph.  The goal is to output a valid permutation or -1 if no such permutation exists.

### 2. Approach Explanation

The solution aims to find a valid permutation of integers from 1 to `n+1` that satisfies the edge constraints imposed by the array `a`. The core idea is to insert `n+1` into the existing sequence `1, 2, 3, ..., n` in a way that respects the directed edge constraints.

The solution identifies three possible cases where `n+1` can be inserted:

1.  **Insert at the beginning:** If `a[0] == 1`, it means there's an edge from `n+1` to 1 (because `n+1 > 1`). In this case, we can form the permutation `n+1, 1, 2, ..., n`.

2.  **Insert at the end:** If `a[n-1] == 0`, it means there's an edge from `n` to `n+1` (because `n < n+1`). In this case, we can form the permutation `1, 2, ..., n, n+1`.

3.  **Insert in the middle:** If there exists an index `i` such that `a[i] == 0` and `a[i+1] == 1`, it means there's an edge from `i+1` to `n+1` (because `i+1 < n+1`) and an edge from `n+1` to `i+2` (because `n+1 > i+2`). Therefore, we can insert `n+1` between `i+1` and `i+2`, resulting in the permutation `1, 2, ..., i+1, n+1, i+2, ..., n`.

If none of these three conditions are met, it implies no valid permutation exists, and the solution outputs -1.

### 3. Key Insights and Algorithmic Techniques

*   **Case Analysis:** The problem is solved by carefully analyzing different scenarios based on the values in the input array `a`.
*   **Greedy Insertion:**  The solution attempts to greedily insert `n+1` into the existing sequence. The conditions for insertion are derived directly from the problem constraints.
*   **Constraint Satisfaction:** The array `a` provides constraints that guide the placement of the number `n+1` within the permutation.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:** The algorithm iterates through the input array `a` at most twice (once to check if `a[0] == 1` or `a[n-1] == 0`, and once to find an `i` where `a[i] == 0` and `a[i+1] == 1`).  The printing of the result takes O(n) time. Thus, the overall time complexity is O(n).
*   **Space Complexity:** The algorithm uses a vector `a` of size `n` to store the input array. Thus, the space complexity is O(n).

### 5. Important Code Patterns or Tricks Used

*   **Concise conditional checks:** The `if` statements directly translate the logical constraints into code, making it easy to understand the logic.
*   **Early Exit:**  The `return` statements within the `if` blocks prevent unnecessary iterations after a valid permutation is found, improving efficiency.
*   **Range-based for loop:** The use of `for (int &x : a)` offers a concise way to read input into the vector.

### 6. Any Edge Cases Handled

*   The code implicitly handles the edge case where a valid permutation doesn't exist by outputting -1 if none of the insertion conditions are met.  This makes the logic complete as per the problem description.
```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <cstdlib>
#include <ostream>
#include <vector>
using namespace std;

// Problem: mocha
// URL: https://codeforces.com/problemset/problem/1559/C
// Difficulty: easy
// Tags:
// Strategy:

/*

We want to insert n+1 somewhere in the path 1 → 2 → 3 → ... → n such that all edges (including those involving n+1) are valid.

There are 3 valid cases:

If a[0] == 1: There’s a road from n+1 to 1. So, we can start from n+1, then go to 1 → 2 → ... → n.

If a[n-1] == 0: There’s a road from n to n+1. So, we can go 1 → 2 → ... → n → n+1.

If a[i] == 0 and a[i+1] == 1 for some i: There's a road from i+1 to n+1, and from n+1 to i+2, so we can insert n+1 between them.

*/

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;

    if (a[0] == 1) {
        cout << n + 1 << " ";
        for (int i = 1; i <= n; ++i)
            cout << i << " ";
        cout << "\n";
        return;
    }

    if (a[n - 1] == 0) {
        for (int i = 1; i <= n; ++i)
            cout << i << " ";
        cout << n + 1 << "\n";
        return;
    }

    for (int i = 0; i < n - 1; ++i) {
        if (a[i] == 0 && a[i + 1] == 1) {
            for (int j = 1; j <= i + 1; ++j)
                cout << j << " ";
            cout << n + 1 << " ";
            for (int j = i + 2; j <= n; ++j)
                cout << j << " ";
            cout << "\n";
            return;
        }
    }

    cout << -1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}

```

---
*Documentation generated on 2025-07-30 13:27:36*
