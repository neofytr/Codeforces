# gridPathsOne

```markdown
## Problem: Grid Paths (CSES Task 1638)

**Problem Description:**

The problem, [Grid Paths](https://cses.fi/problemset/task/1638), asks us to find the number of paths from the top-left corner (0, 0) to the bottom-right corner (n-1, n-1) of an *n* x *n* grid.  Each cell in the grid is either empty (represented by '.') or blocked (represented by '*').  We can only move right or down, and we cannot move to a blocked cell. We need to calculate the number of valid paths modulo 10<sup>9</sup> + 7.

## Approach Explanation

The solution utilizes dynamic programming to solve this problem efficiently. A 2D array `dp` of size *n* x *n* is used to store the number of paths to reach each cell. `dp[r][c]` represents the number of paths from (0, 0) to cell (r, c).

The base case is `dp[0][0] = 1` if the starting cell is not blocked. If the starting cell is blocked, `dp[0][0]` is 0, indicating no possible paths.

The solution iterates through the grid, and for each cell (r, c), it checks if it's a valid cell (not blocked). If the cell is valid, the number of paths to reach it is the sum of the number of paths from the cell above (r-1, c) and the cell to the left (r, c-1), taken modulo 10<sup>9</sup> + 7.

The final result, the number of paths from (0, 0) to (n-1, n-1), is stored in `dp[n-1][n-1]`.

## Key Insights and Algorithmic Techniques

*   **Dynamic Programming:** The core of the solution is dynamic programming. It breaks down the problem into smaller, overlapping subproblems.  The number of paths to a cell is computed based on the number of paths to its neighboring cells.
*   **Modulus Operator:** The problem asks for the answer modulo 10<sup>9</sup> + 7. This is done to prevent integer overflow, as the number of paths can be very large.  The modulus operator (%) is used during each addition step to keep the values within the desired range.
*   **Base Case:** Defining the correct base case `dp[0][0] = 1` (if the start is valid) is crucial for the algorithm to work correctly.
*   **State Transition:** The recurrence relation for calculating `dp[r][c]` is the key:
    ```
    dp[r][c] = (dp[r-1][c] + dp[r][c-1]) % MOD, if grid[r][c] == '.'
    dp[r][c] = 0, if grid[r][c] == '*'
    ```
    This means the number of ways to reach a current cell is the sum of ways to reach it from top and from left (if the paths are not blocked).

## Time and Space Complexity Analysis

*   **Time Complexity:** The solution iterates through the grid once using nested loops, so the time complexity is O(n<sup>2</sup>).
*   **Space Complexity:** The solution uses a 2D `dp` array of size *n* x *n* to store the intermediate results. Therefore, the space complexity is O(n<sup>2</sup>).

## Important Code Patterns or Tricks Used

*   **`#define int long long`:** This macro is used to change the default integer type to `long long`, which helps prevent integer overflow issues, especially when dealing with large grids and potentially large path counts.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This is a common optimization technique used in competitive programming to speed up input/output operations by disabling synchronization between the C++ standard streams (iostream) and the C standard streams (stdio). It also unties `cin` from `cout`, preventing them from waiting on each other.
*   **Modulus Arithmetic:**  The `% MOD` operation is applied *after each addition* to prevent intermediate results from exceeding the maximum value of an integer and causing incorrect results when taking the modulus.

## Edge Cases Handled

*   **Blocked Start Cell:** The code explicitly checks if `grid[0][0]` is blocked (`'*'`). If it is, `dp[0][0]` is set to 0, meaning there are no paths from the start.
*   **Blocked Cells:** The code ensures that we don't move to blocked cells by checking `if (grid[row][col] == '.')` before calculating the number of paths to that cell.
*   **Cells on the edges:** The condition `col >= 1 && grid[row][col - 1] == '.'` and `row >= 1 && grid[row - 1][col] == '.'` check that the algorithm is not trying to access index out of bounds.


## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (int)(1e9 + 7)

// Problem: gridPathsOne
// URL: https://cses.fi/problemset/task/1638
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<vector<char>> grid(n, vector<char>(n));
    for (int row = 0; row < n; row++)
        for (int col = 0; col < n; col++)
            cin >> grid[row][col];

    // we have a nxn grid of squares that may have traps
    // it's not allowed to move to a square with a trap
    // we want to calculate the number of paths from (0, 0) to (n - 1, n - 1) subjected to the
    // constraint that we can only move right or down

    // dp[r][c] is the number of ways to get from (0, 0) to (r, c) subjected to the constraint
    vector<vector<int>> dp(n, vector<int>(n, 0));

    if (grid[0][0] == '.')
        dp[0][0] = 1;
    for (int row = 0; row < n; row++)
        for (int col = 0; col < n; col++) {
            if (grid[row][col] == '.') {
                // there are only two possible ways to get to (row, col) ->
                // from (row - 1, col), or
                // from (row, col - 1)
                if (col >= 1 && grid[row][col - 1] == '.')
                    dp[row][col] = (dp[row][col] + dp[row][col - 1]) % MOD;
                if (row >= 1 && grid[row - 1][col] == '.')
                    dp[row][col] = (dp[row][col] + dp[row - 1][col]) % MOD;
            }
        }
    cout << dp[n - 1][n - 1] << endl;
    return 0;
}
```

---
*Documentation generated on 2025-08-24 13:29:45*
