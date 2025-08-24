# removingDigits

```markdown
# Problem: Removing Digits

This document describes a solution to the "[Removing Digits](https://cses.fi/problemset/task/1637)" problem on the CSES problem set.

## 1. Problem Description

Given a positive integer `n`, the goal is to find the minimum number of steps required to reduce `n` to 0. In each step, you can subtract one of the digits of the current number from the number itself.

For example, if `n = 16`, you can subtract 1 or 6. If you subtract 6, the number becomes 10.

## 2. Approach Explanation

The solution uses dynamic programming (DP) to find the minimum number of steps.

Specifically, `dp[r]` stores the minimum number of steps needed to reduce the number `r` to 0.  We initialize `dp[0] = 0` because it takes zero steps to reduce 0 to 0.

Then, we iterate from `r = 1` to `n`, calculating `dp[r]` for each `r`. For each `r`, we consider all its unique digits. For each digit `d`, if `r - d >= 0`, we can update `dp[r]` by taking the minimum of its current value and `dp[r - d] + 1`.  `dp[r-d]` represents the optimal number of steps to reach `r-d`, and adding 1 represents taking one additional step (subtracting digit `d`).

The final answer is stored in `dp[n]`.

## 3. Key Insights and Algorithmic Techniques Used

*   **Dynamic Programming:** The core idea is to build the solution from smaller subproblems. `dp[i]` depends on the optimal solutions for `dp[i - d]` where `d` is a digit in `i`. This overlapping subproblem structure makes DP suitable.
*   **Bottom-up approach:** We start with `dp[0]` and iteratively compute the values for `dp[1], dp[2], ..., dp[n]`.
*   **Digit Extraction:** Extracting unique digits of a number efficiently is important. The solution uses an `unordered_set` to store the unique digits. This ensures that we don't consider the same digit multiple times (e.g., in a number like 111).
*   **Initialization with Infinity:** The `dp` array is initialized with `LLONG_MAX`. This is crucial to ensure that the `min` operation correctly identifies the optimal number of steps.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:** O(n * k), where `n` is the input number and `k` is the average number of unique digits in a number from 1 to `n`. Since `k` is at most 10, the time complexity can be considered O(n).  The nested loops are the dominant factor: the outer loop iterates `n` times and the inner loop iterates at most 10 times.

*   **Space Complexity:** O(n), due to the `dp` vector of size `n + 1`. The `unordered_set` used for digit extraction has a maximum size of 10 and can be regarded as constant.

## 5. Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**: This optimizes input/output by disabling synchronization between C++ streams and the C standard input/output stream, and by unlinking `cin` from `cout`.
*   **`#define int long long`**: Using this preprocessor directive changes the default `int` type to `long long`, which is often necessary in competitive programming to avoid integer overflow issues, especially when the constraints are large (e.g. up to `10^6`).
*   **Initialization to `LLONG_MAX`:** Setting the initial values of the `dp` array to `LLONG_MAX` allows us to use the `min` function effectively in calculating the optimal values.
*   **Using `unordered_set`**: Using `unordered_set` ensures that the inner loop iterates over *unique* digits only.

## 6. Any Edge Cases Handled

*   The algorithm handles the case where a number contains a digit of 0.  Subtracting 0 doesn't change the number, which is acceptable by problem constraints and properly captured by the DP state.
*   The base case `dp[0] = 0` handles the condition when the input is already 0. The loop starts at `r=1` avoids accessing invalid memory locations.
*   The conditional `if (dp[r - d] != LLONG_MAX)` prevents cases where subtracting `d` leads to a previous state that is unreachable, avoiding incorrect calculations of `dp[r]`.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: removingDigits
// URL: https://cses.fi/problemset/task/1637
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    // we are given an integer n
    // on each step, we may subtract one of the digits from the number
    // what is the minimum number of steps needed to make the number equal to 0?

    // dp[r] is the minimum number of steps needed to make the number equal to 0
    vector<int> dp(n + 1);
    dp[0] = 0;
    for (int r = 1; r <= n; r++) {
        // how many unique digits does r have?
        dp[r] = LLONG_MAX;
        unordered_set<int> un;
        int x = r;
        while (x) {
            un.insert(x % 10);
            x /= 10;
        }

        for (const int d : un)
            if (dp[r - d] != LLONG_MAX)
                dp[r] = min(dp[r], dp[r - d] + 1);
    }

    cout << dp[n] << endl;
    return 0;
}
```

---
*Documentation generated on 2025-08-24 12:55:52*
