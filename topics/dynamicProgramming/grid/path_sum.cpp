#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minPathSum(const vector<vector<int> > &grid) {
        const int m = static_cast<int>(grid.size()); // number of rows (y coordinate)
        const int n = static_cast<int>(grid[0].size()); // number of cols (x coordinate)

        vector<vector<int> > dp(m, vector<int>(n, -1));
        // dp[y][x] is the minimum sum along any path from origin to (x, y)

        for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
                if (x && y) {
                    dp[y][x] = min(dp[y - 1][x], dp[y][x - 1]) + grid[y][x];
                } else if (x > 0) {
                    dp[y][x] = dp[y][x - 1] + grid[y][x];
                } else if (y > 0) {
                    dp[y][x] = dp[y - 1][x] + grid[y][x];
                } else {
                    dp[y][x] = grid[y][x];
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};
