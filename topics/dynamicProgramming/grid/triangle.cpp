#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumTotal(const vector<vector<int> > &triangle) {
        const int n = static_cast<int>(triangle.size()); // number of rows in the triangular grid
        vector<vector<int> > dp(n);

        for (int row = 0; row < n; row++) {
            if (!row) {
                dp[row] = vector<int>(1);
                dp[row][0] = triangle[row][0];
                continue;
            }
            dp[row] = vector<int>(triangle[row].size());
            const int m = static_cast<int>(triangle[row].size());
            for (int col = 0; col < m; col++) {
                if (col > 0 && col < m - 1) {
                    dp[row][col] = min(dp[row - 1][col], dp[row - 1][col - 1]) + triangle[row][col];
                } else if (!col) {
                    dp[row][col] = dp[row - 1][col] + triangle[row][col];
                } else {
                    dp[row][col] = dp[row - 1][col - 1] + triangle[row][col];
                }
            }
        }

        int minimum = dp[n - 1][0];
        for (int index = 0; index < triangle[n - 1].size(); index++) {
            minimum = min(minimum, dp[n - 1][index]);
        }

        return minimum;
    }
};
