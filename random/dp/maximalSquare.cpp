#include <bits/stdc++.h>
using namespace std;

#define MAX (int)(3 * 1e2)

int mat[MAX + 1][MAX + 1];
int dp[MAX + 1][MAX + 1];

class Solution {
  public:
    int maximalSquare(const vector<vector<char>> &matrix) {
        const int n = (int)matrix.size(), m = (int)matrix[0].size();
        for (int r = 1; r <= n; r++)
            for (int c = 1; c <= m; c++)
                mat[r][c] = matrix[r - 1][c - 1] - '0';

        for (int r = 1; r <= n; r++)
            for (int c = 1; c <= m; c++)
                dp[r][c] = 0;

        // dp[r][c] is the side-length of the largest square consisting of just ones with its bottom right end at (i, j)
        for (int c = 1; c <= m; c++)
            if (mat[1][c])
                dp[1][c] = 1;
        for (int r = 1; r <= n; r++)
            if (mat[r][1])
                dp[r][1] = 1;

        for (int r = 2; r <= n; r++)
            for (int c = 2; c <= m; c++) {
                if (!mat[r][c])
                    continue;
                dp[r][c] = 1 + min({dp[r - 1][c], dp[r][c - 1], dp[r - 1][c - 1]});
            }

        int maxi = 0;
        for (int r = 1; r <= n; r++)
            for (int c = 1; c <= m; c++)
                maxi = max(maxi, dp[r][c]);
        return maxi * maxi;
    }
};