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