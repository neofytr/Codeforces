#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int solve(vector<vector<int> > &dp, const vector<vector<int> > &grid, const int x, const int y) {
        if (grid[y][x] == 1) return 0; // obstacle
        if (x == 0 && y == 0) return 1; // base case

        if (dp[y][x] != -1) return dp[y][x];

        int ways = 0;
        if (x > 0 && !grid[y][x - 1])
            ways += solve(dp, grid, x - 1, y);
        if (y > 0 && !grid[y - 1][x])
            ways += solve(dp, grid, x, y - 1);

        return dp[y][x] = ways;
    }

    static int uniquePathsWithObstacles(const vector<vector<int> > &obstacleGrid) {
        const int m = static_cast<int>(obstacleGrid.size());
        const int n = static_cast<int>(obstacleGrid[0].size());
        if (obstacleGrid[0][0] == 1) return 0;

        vector<vector<int> > dp(m, vector<int>(n, -1));
        return solve(dp, obstacleGrid, n - 1, m - 1);
    }
};
