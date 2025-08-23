#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"
#define MOD (int)(1e9 + 7)
// Problem: diceCombinations
// URL: https://cses.fi/problemset/task/1633
// Difficulty: easy
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    // dp[r] is the number of ways to construct the sum r by throwing a dice one of more times
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 1 + 1;
    dp[3] = 1 + 1 + 2;
    dp[4] = 4 + 2 + 1 + 1;
    dp[5] = dp[4] + dp[3] + dp[2] + dp[1] + 1;
    for (int r = 6; r <= n; r++) {
        dp[r] = (dp[r - 1] + dp[r - 2] + dp[r - 3] + dp[r - 4] + dp[r - 5] + dp[r - 6]) % MOD;
    }
    cout << dp[n] << endl;
    return 0;
}