#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int solve(const string &str, vector<vector<int> > &dp, const int left, const int right) {
        if (left > right) {
            return 0;
        }

        if (dp[left][right] != -1) {
            return dp[left][right];
        }

        if (str[left] == str[right]) {
            if (left == right) {
                return dp[left][right] = 1 + solve(str, dp, left + 1, right - 1);
            } else {
                return dp[left][right] = 2 + solve(str, dp, left + 1, right - 1);
            }
        }

        const int first = solve(str, dp, left + 1, right);
        const int second = solve(str, dp, left, right - 1);

        return dp[left][right] = max(first, second);
    }

    static int longestPalindromeSubseq(const string &s) {
        const int n = static_cast<int>(s.length());
        vector<vector<int> > dp(n, vector<int>(n, -1));
        return solve(s, dp, 0, n - 1);
    }
};
