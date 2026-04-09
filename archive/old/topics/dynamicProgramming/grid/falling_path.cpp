#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int minFallingPathSum(const vector<vector<int> > &matrix) {
        const int n = static_cast<int>(matrix.size());
        vector<vector<int> > dp(n, vector<int>(n, INT_MAX));

        for (int col = 0; col < n; ++col) {
            dp[0][col] = matrix[0][col];
        }

        for (int row = 1; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                int minAbove = dp[row - 1][col];
                if (col > 0)
                    minAbove = min(minAbove, dp[row - 1][col - 1]);
                if (col < n - 1)
                    minAbove = min(minAbove, dp[row - 1][col + 1]);

                dp[row][col] = minAbove + matrix[row][col];
            }
        }

        return *min_element(dp[n - 1].begin(), dp[n - 1].end());
    }
};
