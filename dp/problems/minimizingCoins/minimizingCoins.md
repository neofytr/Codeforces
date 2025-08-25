# minimizingCoins

```markdown
## Minimizing Coins - Documentation

This document provides a detailed analysis of the provided C++ code solution for the "Minimizing Coins" problem found on CSES (https://cses.fi/problemset/task/1634).

### 1. Problem Description

The "Minimizing Coins" problem on CSES asks us to find the minimum number of coins required to form a given sum `x` using a given set of `n` coin denominations.  We are given `n` coin values and a target sum `x`.  Each coin denomination can be used an unlimited number of times. If it's not possible to form the sum `x` using the given coins, we should output -1.

### 2. Approach Explanation

The solution uses dynamic programming (DP) to solve the problem.  The core idea is to build a table `dp` where `dp[i]` stores the minimum number of coins needed to form the sum `i`. The table is built iteratively from 0 to `x`.

1.  **Initialization:**  `dp[i]` is initialized to `LLONG_MAX` for all `i` from 0 to `x`. This effectively represents infinity, meaning that initially, we assume it's impossible to form any sum. For each coin `c` in `coins`, if `c <= x`, we initialize `dp[c] = 1` since we can make the sum `c` using exactly one coin.
2.  **Iteration:**  We iterate through the sums from 1 to `x`. For each sum `r`, we consider all the coin denominations `c`.  If `r >= c`, it means we can potentially use coin `c` to contribute to the sum `r`.  If `dp[r - c]` is not `LLONG_MAX` (meaning we can form the sum `r - c`), we can update `dp[r]` using the following recurrence relation:

    `dp[r] = min(dp[r], dp[r - c] + 1)`

    This means the minimum number of coins to form `r` is the minimum of its current value and the number of coins to form `r - c` plus one (for the coin `c` we just used).

3.  **Result:**  After iterating through all the sums, `dp[x]` will contain the minimum number of coins required to form the sum `x`. If `dp[x]` is still `LLONG_MAX`, it means it's impossible to form the sum `x`, and we output -1. Otherwise, we output `dp[x]`.

### 3. Key Insights and Algorithmic Techniques Used

*   **Dynamic Programming:** This problem exhibits optimal substructure and overlapping subproblems, making dynamic programming a suitable approach. The principle of optimality holds: the optimal solution for the sum `x` can be constructed from the optimal solutions for smaller sums.
*   **Bottom-Up Approach:** The solution uses a bottom-up dynamic programming approach, building the `dp` table from smaller subproblems (smaller sums) to larger ones. This avoids recursion and potential stack overflow issues.
*   **`LLONG_MAX` for Infinity:** Using `LLONG_MAX` as an initial value for `dp` entries effectively represents infinity, allowing us to track whether a given sum can be formed or not.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:** The solution has a time complexity of O(n\*x), where `n` is the number of coin denominations and `x` is the target sum. The nested loops iterate through all coins for each sum from 1 to `x`.
*   **Space Complexity:** The solution has a space complexity of O(x), primarily due to the `dp` vector, which stores the minimum number of coins needed for each sum from 0 to `x`.

### 5. Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This optimization disables synchronization between C and C++ standard input/output streams and unties `cin` from `cout`, significantly improving input/output performance, which is crucial for competitive programming.
*   **`#define int long long`:** This line changes the default `int` type to `long long`. This is a common practice in competitive programming to avoid integer overflow issues, especially when dealing with large numbers.  It trades some memory for a wider range of representable values.
*   **Range-based for loop:** The use of `for (int &val : coins)` is a convenient way to iterate through a vector and modify its elements in place.  In this context, it's used for reading the input values into the `coins` vector. When just reading and not modifying `for (const int c : coins)` should be preferred.
*   **`min()` function:** The `min()` function is used to find the minimum of two values, allowing us to efficiently update the `dp` table based on the recurrence relation.
*   **Clarity:** Use of `dp[r]` representing minimum coins needed to form sum `r` is a good practice to use variables with meaning that corresponds to the problem.

### 6. Any Edge Cases Handled

*   **Unreachable Sum:** The code correctly handles the case where it is impossible to form the target sum `x` using the given coin denominations.  If `dp[x]` remains `LLONG_MAX` after the DP iterations, it means the sum `x` is unreachable, and the code outputs -1.
*   **Coin values greater than target sum:** Coin values larger than the target are correctly skipped by the `if (r >= c)` condition. If coin `c` is larger than target `r`, then we can't use that coin to make the target `r`.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: minimizingCoins
// URL: https://cses.fi/problemset/task/1634
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // consider a money system consisting of n coins
    // each coin has a positive integer value
    // our task is to produce a sum of money x using the available coins in such a way that the
    // number of coins used is minimal

    int n, x;
    cin >> n >> x;
    vector<int> coins(n);
    for (int &val : coins)
        cin >> val;

    // dp[r] is the minimum number of coins used to produce the sum r
    vector<int> dp(x + 1, LLONG_MAX);
    // all the coin denominations can be made using exactly one coin
    for (const int c : coins)
        if (c <= x)
            dp[c] = 1;

    for (int r = 1; r <= x; r++) {
        // dp[r] = min (over all c in coins such that r >= c and dp[r - c] != LLONG_MAX) (dp[r - c] + 1)
        for (const int c : coins)
            if (r >= c && dp[r - c] != LLONG_MAX)
                dp[r] = min(dp[r], dp[r - c] + 1);
    }
    if (dp[x] == LLONG_MAX)
        cout << -1 << endl;
    else
        cout << dp[x] << endl;
    return 0;
}
```

---
*Documentation generated on 2025-08-25 19:21:00*
