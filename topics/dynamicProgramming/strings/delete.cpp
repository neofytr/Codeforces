#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int solve(const string &str_one, const string &str_two, const int left, const int right,
                     vector<vector<int> > &dp) {
        if (left >= str_one.length() || right >= str_two.length()) {
            return static_cast<int>(max(str_one.length() - left, str_two.length() - right));
            // remove the extra characters left in either of the strings
        }

        if (dp[left][right] != -1) return dp[left][right];

        if (str_one[left] == str_two[right]) {
            return dp[left][right] = solve(str_one, str_two, left + 1, right + 1, dp);
        }

        const int delete_from_one = 1 + solve(str_one, str_two, left + 1, right, dp);
        const int delete_from_two = 1 + solve(str_one, str_two, left, right + 1, dp);

        return dp[left][right] = min(delete_from_one, delete_from_two);
    }

    static int minDistance(const string &word1, const string &word2) {
        int n = static_cast<int>(word1.size()), m = static_cast<int>(word2.size());
        vector<vector<int> > dp(n, vector<int>(m, -1));
        // return solve(word1, word2, 0, 0, dp);

        // to make word1 and word2 equal by deleting in both of them
        // is equivalent to making smaller into larger by insertions and deletions in smaller since
        // deleting in larger is the same as inserting the same thing into smaller

        // iterative solution
        const string larger = (word1.size() > word2.size()) ? word1 : word2;
        const string smaller = (word1.size() > word2.size()) ? word2 : word1;

        n = static_cast<int>(larger.length());
        m = static_cast<int>(smaller.length());

        // To convert 'smaller' into 'larger',
        // we find the longest common subsequence (LCS) between them.
        // We delete elements in 'smaller' not in LCS, and insert elements from 'larger' not in LCS (equivalent to deletions in 'larger').
        // The minimum number of steps = deletions plus insertions = (len(smaller) - LCS) + (len(larger) - LCS)

        vector<vector<int> > iter(n + 1, vector<int>(m + 1, 0));

        // we now find the length of the longest common subsequence of smaller and larger
        // be careful of the order while doing iterative dp
        for (int left = 1; left <= n; left++) {
            for (int right = 1; right <= m; right++) {
                if (smaller[right - 1] == larger[left - 1]) {
                    iter[left][right] = 1 + iter[left - 1][right - 1];
                } else {
                    iter[left][right] = max(iter[left - 1][right], iter[left][right - 1]);
                }
            }
        }

        return (n + m - 2 * iter[n][m]);
    }
};
