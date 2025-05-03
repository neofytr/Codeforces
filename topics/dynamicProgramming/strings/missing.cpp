#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int solve(const string &str, const int left, const int right, vector<vector<int> > &dp) {
        if (left >= right) {
            return 0;
        }

        if (dp[left][right] != -1) {
            return dp[left][right];
        }

        if (str[left] == str[right]) {
            return dp[left][right] = solve(str, left + 1, right - 1, dp);
        }

        return dp[left][right] = 1 + min(solve(str, left, right - 1, dp), solve(str, left + 1, right, dp));
    }

    int minInsertions(const string &s) {
        const int n = static_cast<int>(s.size());
        vector<vector<int> > dp(n, vector<int>(n, -1));
        return solve(s, 0, n - 1, dp);
    }
};
