# basketball

```markdown
## Competitive Programming Solution Documentation: Basketball Team Selection

This document provides a comprehensive analysis of a competitive programming solution for the "Basketball Team" problem (found at [https://codeforces.com/problemset/problem/1195/C](https://codeforces.com/problemset/problem/1195/C)).

### 1. Problem Description

There are *n* students lined up in two rows, each containing *n* students. The height of each student is given.  The goal is to select a team of students with the following constraints:

*   Students are chosen from left to right in both rows.
*   The index of each chosen player (excluding the first) must be strictly greater than the index of the previously chosen player.
*   No two consecutive students can belong to the same row.
*   The first student can be chosen from any of the 2\*n students.
*   The team can consist of any number of students.

The objective is to maximize the total height of the players in the team.

### 2. Approach Explanation

The problem can be solved using dynamic programming. The core idea is to build a DP table that stores the maximum possible height of a team ending at a particular index in a specific row.

Let `dp[r][k]` be the maximum total height possible when we choose in the index range `[0, r]` such that the last player chosen is from row *k*. Here, *k* can take the following values:

*   `k = 0`: Last player chosen is from the first row.
*   `k = 1`: Last player chosen is from the second row.
*   `k = 2`: No player chosen (or at the beginning which is not helpful)

The DP table is initialized as follows:

*   `dp[0][0] = first[0]` (The first player is chosen from the first row)
*   `dp[0][1] = second[0]` (The first player is chosen from the second row)
*   `dp[0][2] = 0` (No one chosen yet)

The DP table is filled iteratively, row by row (index by index), using the following recurrence relations:

*   `dp[r][0] = max(dp[r - 1][1], dp[r - 1][2]) + first[r]`
    *   To choose the player at index `r` in the first row, the previous player must have been chosen from the second row or not chosen at all.

*   `dp[r][1] = max(dp[r - 1][0], dp[r - 1][2]) + second[r]`
    *   To choose the player at index `r` in the second row, the previous player must have been chosen from the first row or not chosen at all.

*   `dp[r][2] = max(dp[r - 1][0], max(dp[r - 1][1], dp[r - 1][2]))`
    *   To choose not to select player at `r`, the optimal solution will be maximum between previous states of first row selected, second row selected and not selected.

Finally, the maximum possible total height is `max(dp[n - 1][0], dp[n - 1][1])`. We only consider the last element being in row 0 or 1, since choosing nothing is automatically considered during DP table update and always result less height.

### 3. Key Insights and Algorithmic Techniques Used

*   **Dynamic Programming:**  The problem exhibits optimal substructure and overlapping subproblems, making it suitable for dynamic programming.
*   **State Definition:** The state `dp[r][k]` effectively captures the current state of the team selection process, allowing for efficient computation of the optimal solution.
*   **Transition Function:**  The recurrence relations accurately describe how to transition from one state to another, considering the constraints of the problem.
*   **Optimization:** The `dp[r][2]` state keeps track of maximum team height at each index while not selecting any player in that index. This is a neat way of skipping players from either row to produce an optimal result.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:** O(n), because the DP table is filled with a single loop that iterates from `r = 1` to `n - 1`, and each iteration performs constant-time operations.
*   **Space Complexity:** O(n), because the DP table `dp` has dimensions `n x 3`. This could be further optimized to O(1) by storing only the previous row's information, as the current row only depends on the previous row.

### 5. Important Code Patterns or Tricks Used

*   **`#define int long long`:** Using this preprocessor directive is a common practice in competitive programming to avoid integer overflow issues when dealing with large numbers.  The problem constraints often require using 64-bit integers (`long long` in C++).
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This optimization disables synchronization between C++ standard streams and the C standard streams, and unties `cin` from `cout`, which can significantly improve the input/output performance of the program, particularly in problems with large input/output.
*   **Simplified States:** The DP solution uses only 3 states per row in DP table, significantly simplifying the logic and leading to a clear and concise implementation.

### 6. Edge Cases Handled

*   **n = 1:** The code correctly handles the case when there is only one student in each row, as the initialization of the DP table directly assigns the heights of the first students.
*   **Empty team:** The problem statement said there could be any number of players, which including 0. That case has been handled properly with using dp[r][2] as a case where no one chosen.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: basketball
// URL: https://codeforces.com/problemset/problem/1195/C
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> first(n), second(n);
    for (int &val : first)
        cin >> val;
    for (int &val : second)
        cin >> val;

    // 2 * n students have come
    // they are lined up into two rows of the same size (n)
    // students are numbered 0 to n-1 from left to right in each row

    // we want to choose a team to play basketball
    // we will choose players from left to right, and the index of each chosen player (excluding the first one taken)
    // will be strictly greater than the index of the previously chosen player
    // no two consecutive students should belong to the same row

    // the first student can be chosen among all 2n students and a team can consist of any number of students
    // we want to maximize the total height of the players in the team

    // dp[r][k] is the maximum total height possible when we choose in the index range [0, r]
    // with the last player chosen from row k
    // k = 3 means not chosen
    vector<vector<int>> dp(n, vector<int>(3));
    dp[0][0] = first[0];
    dp[0][1] = second[0];
    dp[0][2] = 0;

    for (int r = 1; r < n; r++) {
        dp[r][0] = max(dp[r - 1][1], dp[r - 1][2]) + first[r];
        dp[r][1] = max(dp[r - 1][0], dp[r - 1][2]) + second[r];
        dp[r][2] = max(dp[r - 1][0], max(dp[r - 1][1], dp[r - 1][2]));
    }

    cout << max(dp[n - 1][0], dp[n - 1][1]) << endl;
    return 0;
}
```

---
*Documentation generated on 2025-08-29 18:51:42*
