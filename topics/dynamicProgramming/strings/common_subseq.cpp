#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int solve(const string &text1, const string &text2, const int left_index,
                     const int right_index, vector<vector<int> > &dp) {
        if (left_index >= text1.size() || right_index >= text2.size()) {
            return 0;
        }

        if (dp[left_index][right_index] != -1) {
            return dp[left_index][right_index];
        }

        if (text1[left_index] == text2[right_index]) {
            return dp[left_index][right_index] = 1 + solve(text1, text2, left_index + 1, right_index + 1, dp);
        }

        return dp[left_index][right_index] = max(
                   solve(text1, text2, left_index + 1, right_index, dp),
                   solve(text1, text2, left_index, right_index + 1, dp)
               );
    }

    int longestCommonSubsequence(const string &text1, const string &text2) {
        const int n = static_cast<int>(text1.size());
        const int m = static_cast<int>(text2.size());
        vector<vector<int> > dp(n, vector<int>(m, -1));
        return solve(text1, text2, 0, 0, dp);
    }
};
