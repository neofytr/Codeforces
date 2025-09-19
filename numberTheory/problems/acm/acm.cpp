#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (1000000000 + 7)

// Problem: acm
// URL: https://codeforces.com/problemset/problem/414/B
// Difficulty: hard
// Tags:
// Strategy:

int solve(const int n, const int k) {
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));

    for (int s = 1; s <= n; s++)
        dp[1][s] = 1;

    for (int r = 2; r <= k; r++)
        for (int s = 1; s <= n; s++)
            for (int j = 1; j * j <= s; j++)
                if (!(s % j)) {
                    dp[r][s] = (dp[r][s] + dp[r - 1][j]) % MOD;
                    if (j != s / j)
                        dp[r][s] = (dp[r][s] + dp[r - 1][s / j]) % MOD;
                }

    int ans = 0;
    for (int s = 1; s <= n; s++)
        ans = (ans + dp[k][s]) % MOD;
    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    cout << solve(n, k) << endl;
    return 0;
}