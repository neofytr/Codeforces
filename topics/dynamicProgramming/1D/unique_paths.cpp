#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int solve(vector<vector<int> > &dp, const int x, const int y) {
        // returns the number of ways to get to (x, y) from the origin
        if (x == y && !x) {
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
        const int ans = solve(dp, m - 1, n - 1);

        // approach with tabulation
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                if (x && y) {
                    dp[x][y] = dp[x - 1][y] + dp[x][y - 1];
                } else if (y) {
                    dp[x][y] = dp[x][y - 1];
                } else if (x) {
                    dp[x][y] = dp[x - 1][y];
                } else {
                    dp[x][y] = 1;
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};
