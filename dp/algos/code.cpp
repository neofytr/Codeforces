#include <bits/stdc++.h>
using namespace std;

/*
 * Where DP?
 * 1. overlapping subproblems
 * 2. minimize/maximize some value
 * 3. finding number of ways
 * 4. covering all cases (DP v/s Greedy)
 * 5. check for possibility
 */

#define int long long

int solveFib(const int x, vector<int> &dp) {
    if (x == 1 || x == 2)
        return dp[x] = 1;
    if (dp[x] != -1)
        return dp[x];
    return dp[x] = solveFib(x - 1, dp) + solveFib(x - 2, dp);
}

void fib() {
    int n;
    cin >> n;

    vector<int> dp(n + 1, -1);
    cout << solveFib(n, dp) << endl;
}

void grid() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n, vector<int>(m));
    for (int row = 0; row < n; row++)
        for (int col = 0; col < m; col++)
            cin >> g[row][col];

    // dp[r][c] gives the minimum sum of values path from (0, 0) to (r, c)
    vector<vector<int>> dp(n, vector<int>(m, LLONG_MAX));

    queue<tuple<int, int>> que;
    int dr[] = {0, -1, 0, +1};
    int dc[] = {-1, 0, +1, 0};
    dp[0][0] = g[0][0];
    que.push({0, 0});
    while (!que.empty()) {
        auto [row, col] = que.front();
        que.pop();

        for (int i = 0; i < 4; i++) {
            int drow = row + dr[i];
            int dcol = col + dc[i];
            if (drow >= 0 && dcol >= 0 && drow < n && dcol < m) {
                if (dp[drow][dcol] > dp[row][col] + g[drow][dcol]) {
                    dp[drow][dcol] = dp[row][col] + g[drow][dcol];
                    que.push({drow, dcol});
                }
            }
        }
    }

    cout << dp[n - 1][m - 1] << endl;
}

int32_t main() {
    grid();
    return 0;
}