#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int solve(vector<vector<int> > &dp, const int x, const int y) {
        if (x == y && x == 0) {
            return 1;
        }

        if (dp[x][y] != -1) {
            return dp[x][y];
        }

        if (x > 0 && y > 0) {
            return dp[x][y] = solve(dp, x - 1, y) + solve(dp, x, y - 1);
        } else if (y > 0) {
            return dp[x][y] = solve(dp, x, y - 1);
        } else if (x > 0) {
            return dp[x][y] = solve(dp, x - 1, y);
        }

        // won't ever reach here
        return 0;
    }

    static int uniquePaths(const int m, const int n) {
        // the robot is located at origin(0, 0)
        // he wants to move to the point (m - 1, n - 1)
        // he can only move to the left or up at any position
        // return the number of possible unique paths that the robot can take to reach the final point
        // from the initial point

        vector<vector<int> > dp(m, vector<int>(n, -1));
        dp[0][0] = 1;

        solve(dp, m - 1, n - 1);

        return dp[m - 1][n - 1];
    }
};
