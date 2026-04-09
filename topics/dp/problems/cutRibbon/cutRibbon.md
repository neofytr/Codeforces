# cutRibbon

```markdown
# Codeforces Problem 189A - Cut Ribbon: Solution Analysis and Documentation

This document provides a detailed analysis of the provided C++ solution for Codeforces Problem 189A, "Cut Ribbon" (https://codeforces.com/problemset/problem/189/A).

## 1. Problem Description

Given a ribbon of length `n`, and three possible cut lengths `a`, `b`, and `c`, determine the maximum number of pieces you can cut the ribbon into using only the specified cut lengths.

## 2. Approach Explanation

The problem can be solved using dynamic programming.  The core idea is to build a table `dp` where `dp[i]` represents the maximum number of pieces that can be obtained from a ribbon of length `i`.  The base case is `dp[0] = 0` (a ribbon of length 0 requires 0 cuts).  The recurrence relation is as follows:

`dp[i] = max(dp[i], dp[i - a] + 1)` if `i >= a` and `dp[i - a] != -1`
`dp[i] = max(dp[i], dp[i - b] + 1)` if `i >= b` and `dp[i - b] != -1`
`dp[i] = max(dp[i], dp[i - c] + 1)` if `i >= c` and `dp[i - c] != -1`

If a particular length `i` cannot be achieved using the cuts `a`, `b`, and `c`, then `dp[i]` remains -1.

Finally, `dp[n]` will hold the maximum number of pieces for a ribbon of length `n`.

## 3. Key Insights and Algorithmic Techniques Used

*   **Dynamic Programming:** The core of the solution is dynamic programming. The problem exhibits optimal substructure because the optimal solution for a ribbon of length `n` can be constructed from the optimal solutions for ribbons of smaller lengths (`n - a`, `n - b`, and `n - c`). The problem also has overlapping subproblems as the same smaller lengths are reused multiple times.
*   **Bottom-Up Approach:** The DP solution is built from the bottom up, starting with the base case `dp[0]` and iteratively calculating `dp[i]` for increasing values of `i` up to `n`.
*   **Unordered Set for Cut Lengths:** Using an `unordered_set` to store the possible cut lengths `a`, `b`, and `c` provides efficient (O(1) on average) lookups when iterating through the possible cuts. This improves code readability and simplifies the main loop.
*   **Initialization with -1:** Initializing the `dp` array with -1 allows us to easily determine if a certain ribbon length `i` cannot be achieved by the cuts `a`, `b`, and `c`. This is essential for the `max` function to work correctly, as a non-achievable state will not contribute to a larger number of pieces.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:** The outer loop iterates from `1` to `n`, which takes O(n) time. The inner loop iterates over the possible cut lengths `a`, `b`, and `c`, which takes O(1) time because the set has a constant size of 3.  Therefore, the overall time complexity is O(n).
*   **Space Complexity:** The `dp` array stores the maximum number of pieces for each length from `0` to `n`. Therefore, the space complexity is O(n). The `unordered_set pieces` uses O(1) space.

## 5. Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This optimization disables synchronization between C++ streams and the C standard input/output streams. This dramatically speeds up input/output operations, which is especially important in competitive programming where time limits are strict.
*   **`#define int long long`:** This macro redefines `int` as `long long`, which prevents integer overflow issues when handling larger values of `n`, `a`, `b`, and `c`, or potentially large number of ribbon pieces.
*   **Using `-1` to represent unreachable states:** Initializing the `dp` table with `-1` is a common practice to represent states that cannot be reached by the possible cuts. This allows us to easily check the validity of transitions in the DP recurrence.

## 6. Edge Cases Handled

*   **Ribbon of Length 0:** The base case `dp[0] = 0` handles the case where the ribbon has length 0, which requires 0 cuts.
*   **Unreachable States:** The `dp` array is initialized with `-1`, and the algorithm only considers transitions from reachable states (i.e., `dp[r - p] != -1`). This ensures that unreachable states do not affect the final result. For example, if the cuts are 2,3,4, and n=1 then dp[1] remains -1 after the loop, which never happens since we start loop from 1.
*   **Integer Overflow:** Using `long long` as the underlying type for `int` mitigates the risk of integer overflows.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: cutRibbon
// URL: https://codeforces.com/problemset/problem/189/A
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, a, b, c;
    cin >> n >> a >> b >> c;

    unordered_set<int> pieces;
    pieces.insert(a);
    pieces.insert(b);
    pieces.insert(c);

    // dp[r] denotes the maximum number of ribbon pieces for cutting ribbons of length r for n >= r >= 0
    vector<int> dp(n + 1, -1); // -1 is for we cannot make it
    dp[0] = 0;
    for (int r = 1; r <= n; r++) {
        for (const int p : pieces)
            if (r >= p && dp[r - p] != -1)
                dp[r] = max(dp[r], dp[r - p] + 1);
    }

    cout << dp[n] << endl;
    return 0;
}
```

---
*Documentation generated on 2025-08-26 16:22:54*
