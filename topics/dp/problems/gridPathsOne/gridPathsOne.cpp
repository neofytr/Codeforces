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
    // we do space optimization since we'll only ever need to current and the previous row to do the
    // transitions and to calculate the final answer too

    vector<int> dpCurr(n, 0), dpPrev(n, 0);

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (grid[row][col] == '*') {
                dpCurr[col] = 0; // blocked
                continue;
            }
            if (!row && !col) {
                dpCurr[col] = 1; // start
            } else {
                int ways = 0;
                // we can come to this cell from (row, col - 1) or (row - 1, col)
                // there are no other possibilities
                if (col > 0)
                    ways = (ways + dpCurr[col - 1]) % MOD;
                if (row > 0)
                    ways = (ways + dpPrev[col]) % MOD;
                dpCurr[col] = ways;
            }
        }
        dpPrev = dpCurr;
    }

    cout << dpCurr[n - 1] << "\n";
    return 0;
}