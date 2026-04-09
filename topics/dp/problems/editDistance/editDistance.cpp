#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: editDistance
// URL: https://cses.fi/problemset/task/1639
// Difficulty: hard
// Tags:
// Strategy:

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.size(), m = s2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    // base cases
    for (int i = 0; i <= n; i++)
        dp[i][0] = i;
    for (int j = 0; j <= m; j++)
        dp[0][j] = j;

    // transitions
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1]; // no cost
            else
                dp[i][j] = 1 + min({
                                   dp[i - 1][j],    // remove
                                   dp[i][j - 1],    // insert
                                   dp[i - 1][j - 1] // replace
                               });
        }
    }

    cout << dp[n][m] << endl;
}
