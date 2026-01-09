#include <bits/stdc++.h>
using namespace std;

#define MAX (int)(1e3)

int dp[2 * MAX + 1][MAX + 1][MAX + 1][2];
int v1[MAX + 1], v2[MAX + 1], v3[2 * MAX + 1];

class Solution {
  public:
    bool isInterleave(const string &s1, const string &s2, const string &s3) {
        for (int r = 1; r <= s1.length(); r++)
            v1[r] = s1[r - 1] - 'a';
        for (int r = 1; r <= s2.length(); r++)
            v2[r] = s2[r - 1] - 'a';
        for (int r = 1; r <= s3.length(); r++)
            v3[r] = s3[r - 1] - 'a';

        if (v3[1] == v1[1])
            dp[1][1][0][0] = true;
        if (v3[1] == v2[1])
            dp[1][0][1][1] = true;

        for (int r = 2; r <= s3.length(); r++)
            for (int i = 0; i <= s1.length(); i++)
                for (int j = 0; j <= s2.length(); j++) {
                    if (i && v3[r] == v1[i])
                        dp[r][i][j][0] = dp[r - 1][i - 1][j][1] || dp[r - 1][i - 1][j][0];
                    if (j && v3[r] == v2[j])
                        dp[r][i][j][1] = dp[r - 1][i][j - 1][0] || dp[r - 1][i][j - 1][1];
                }
        return dp[s3.length()][s1.length()][s2.length()][0] || dp[s3.length()][s1.length()][s2.length()][1];
    }
};

int32_t main() {
    return 0;
}