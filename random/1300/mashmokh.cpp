#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (int)(1e9 + 7)

int32_t main() {
    int n, k;
    cin >> n >> k;

    // dp[l][r] is the number of sequences of length l ending at r
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));

    for (int r = 1; r <= n; r++) dp[1][r] = 1;
    for (int l = 1; l < k; l++)
        for (int r = 1; r <= n; r++)
            for (int d = r; d <= n; d += r) {
                dp[l + 1][d] += dp[l][r];
                if (dp[l + 1][d] >= MOD)
                    dp[l + 1][d] -= MOD;
            }

    int res = 0;
    for (int r = 1; r <= n; r++) {
        res += dp[k][r];
        if (res >= MOD) res -= MOD;
    }

    cout << res << endl;
    return 0;
}