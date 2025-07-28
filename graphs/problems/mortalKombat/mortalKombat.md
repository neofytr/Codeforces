# mortalKombat

```markdown
## Competitive Programming Solution Analysis: Mortal Kombat (Codeforces 1418C)

This document analyzes a C++ solution for the "Mortal Kombat" problem on Codeforces (problem 1418C, URL: https://codeforces.com/problemset/problem/1418/C).  The goal is to provide a comprehensive understanding of the solution, including the problem, approach, algorithms, complexities, and potential improvements.

### 1. Problem Description

The "Mortal Kombat" problem involves a sequence of `n` bosses.  Each boss has a difficulty rating represented by an integer (0 or 1).  Two players, a friend and the opponent, alternate turns.  The friend goes first.  On each turn, a player can choose to defeat either one or two consecutive bosses.

-   **Friend's Turn:** The friend *must* skip (use a "skip point") for each boss with a difficulty rating of 1 that they defeat.
-   **Opponent's Turn:** The opponent doesn't need to skip any bosses, regardless of their difficulty.

The problem asks to find the minimum number of "skip points" the friend needs to use to defeat all the bosses.

### 2. Approach Explanation

The solution uses a top-down dynamic programming approach (with memoization) to explore the possible moves and minimize the skip points. The core idea is to recursively compute the minimum skip points needed to clear the remaining bosses, considering whether it's the friend's or the opponent's turn.

The `dfs(index, player, arr, dp)` function calculates the minimum skip points needed to defeat bosses from `index` to the end of the `arr` (boss difficulty array), given that it is `player`'s turn (`player` is 0 for the friend and 1 for the opponent).

The function explores two possibilities for each turn:

1.  Defeat the current boss (or the current two bosses) and recursively calculate the minimum skip points for the remaining bosses.
2.  Defeat the next two bosses if possible and recursively calculate the minimum skip points for the remaining bosses.

The function then returns the minimum of these two possibilities, storing the result in the `dp` table to avoid redundant calculations.

### 3. Key Insights and Algorithmic Techniques Used

*   **Dynamic Programming (Memoization):**  The problem exhibits overlapping subproblems, making dynamic programming an ideal choice. Memoization, specifically, stores the results of already computed states in the `dp` table to avoid recomputation.
*   **Top-Down (Recursive) Approach:** The problem is solved by breaking it down into smaller subproblems and recursively solving them. This makes the logic easier to understand.
*   **Turn-Based Game Optimization:** The `player` parameter in the `dfs` function efficiently tracks whose turn it is, allowing the code to apply the correct skipping rules (friend skips on difficulty 1, opponent skips none).
*   **State Representation:** The `dp` table, `dp[player][index]`, cleverly stores the minimum skip points needed from index `index` to the end when it's player `player`'s turn.  This accurately represents the state of the problem.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:** O(2\*n), where `n` is the number of bosses. The `dfs` function explores each state (player, index) at most once due to memoization.  Each state has two possible transitions, leading to a time complexity that is essentially `O(n)`.  The outer loop iterating `t` test cases multiplies this by a factor of t.
*   **Space Complexity:** O(2\*n) = O(n). The `dp` table stores the minimum skip points for each possible state (player, index), resulting in space proportional to `2*n`.

### 5. Important Code Patterns or Tricks Used

*   **Memoization Implementation:** The use of `dp[player][index] != -1` to check if a state has already been computed is a standard memoization technique.
*   **Turn-Based Logic:** The `player` parameter toggling between 0 and 1 to represent the friend and the opponent is a clean way to manage the turns.
*   **Early Exit Condition:** The `if (index >= n)` condition in the `dfs` function serves as a base case for the recursion, terminating the search when all bosses have been defeated.
*   **`INT_MAX` for Initialization:**  Using `INT_MAX` to initialize the `justCurrent` and `both` variables ensures that the `min` function correctly identifies the smaller valid value when either `justCurrent` or `both` hasn't been updated.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**: Optimizes input/output stream for faster execution.

### 6. Edge Cases Handled

*   **End of Array:** The `if (index >= n)` condition gracefully handles the case where all bosses have been defeated.
*   **Defeating Two Bosses at the End:** The `if (index + 1 < n)` condition prevents accessing array elements out of bounds when considering the "defeat two bosses" option near the end of the boss array.
*   **Zero Bosses:** The code will work correctly even when there are zero bosses (input `n = 0`) since the base case `index >= n` will immediately return 0 skip points.  There are no runtime errors.

### Additional Notes and potential improvements
- The problem is a good example of a relatively straightforward DP implementation that can benefit significantly from memoization.
- While the current code is clean and efficient for the constraints of the problem, a bottom-up (iterative) DP approach is possible, which might offer slightly better performance in some cases by avoiding the overhead of recursive calls. However, the recursive approach is often easier to understand and implement.


## Original Code
```cpp
#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

// Problem: mortalKombat
// URL: https://codeforces.com/problemset/problem/1418/C
// Difficulty: hard
// Tags:
// Strategy:

int dfs(int index, int player, vector<int> &arr, vector<vector<int>> &dp) {
    int n = (int)arr.size();
    if (index >= n)
        return 0;
    if (dp[player][index] != -1) {
        return dp[player][index];
    }

    int justCurrent = INT_MAX;
    int both = INT_MAX;
    // we can either kill the next two, or the next one
    if (!player) {
        // friend
        // can't kill hard without using skips
        // can kill the current or the next two
        justCurrent = (arr[index] ? 1 : 0) + dfs(index + 1, !player, arr, dp);
        if (index + 1 < n) {
            both = (arr[index] ? 1 : 0) + (arr[index + 1] ? 1 : 0) + dfs(index + 2, !player, arr, dp);
        }
    } else {
        justCurrent = dfs(index + 1, !player, arr, dp);
        if (index + 1 < n) {
            both = dfs(index + 2, !player, arr, dp);
        }
    }

    return dp[player][index] = min(justCurrent, both);
}

void solve() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    vector<vector<int>> dp(2, vector<int>(n, -1));
    // dp[p][r] gives the min number of skip points required to kill all the bosses from [r, n - 1] with
    // the first turn being of player p

    cout << dfs(0, 0, arr, dp) << endl;
    return;
}

int main() {
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
*Documentation generated on 2025-07-28 21:33:11*
