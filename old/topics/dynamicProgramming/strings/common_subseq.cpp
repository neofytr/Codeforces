#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int solve(const string &first, const string &second, vector<vector<int> > &dp, const int left,
                     const int right) {
        // returns the count of the longest subsequence for first[left, n-1] and right[right, m - 1]
        if (left >= first.size() || right >= second.size()) {
            return 0;
        }

        if (dp[left][right] != -1) {
            return dp[left][right];
        }

        if (first[left] == second[right]) {
            return dp[left][right] = 1 + solve(first, second, dp, left + 1, right + 1);
        }

        const int firstCount = solve(first, second, dp, left + 1, right);
        const int secondCount = solve(first, second, dp, left, right + 1);
        return dp[left][right] = max(firstCount, secondCount);
    }

    static int longestCommonSubsequence(const string &text1, const string &text2) {
        const int n = static_cast<int>(text1.size());
        const int m = static_cast<int>(text2.size());
        vector<vector<int> > dp(n, vector<int>(m, -1));
        // dp[left][right] stores the count of the longest subsequence for text1[left, n-1] and text2[right, m - 1]
        // return solve(text1, text2, dp, 0, 0);

        // we now do the iterative (tabulative solution)
        vector<vector<int> > iter(n + 1, vector<int>(m + 1, 0));
        // iter[left][right] stores the length of the longest subsequence of text1[1, left] and text2[1, right]

        for (int left = 1; left <= n; left++) {
            for (int right = 1; right <= m; right++) {
                if (text1[left - 1] == text2[right - 1]) {
                    iter[left][right] = 1 + iter[left - 1][right - 1];
                } else {
                    iter[left][right] = max(iter[left - 1][right], iter[left][right - 1]);
                }
            }
        }

        return iter[n][m];
    }
};
