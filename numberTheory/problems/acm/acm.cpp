#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (1000000000 + 7)

// Problem: acm
// URL: https://codeforces.com/problemset/problem/414/B
// Difficulty: hard
// Tags:
// Strategy:

int solve(int n, int k) {
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));

    for (int s = 1; s <= n; s++)
        dp[1][s] = 1; // base case

    for (int r = 1; r < k; r++) {
        for (int s = 1; s <= n; s++) {
            int val = dp[r][s];
            if (!val)
                continue;
            for (int m = s; m <= n; m += s) {
                dp[r + 1][m] += val;
                if (dp[r + 1][m] >= MOD)
                    dp[r + 1][m] -= MOD;
            }
        }
    }

    int ans = 0;
    for (int s = 1; s <= n; s++) {
        ans += dp[k][s];
        if (ans >= MOD)
            ans -= MOD;
    }
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