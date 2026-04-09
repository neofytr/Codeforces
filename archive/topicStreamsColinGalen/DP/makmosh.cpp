#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (int)(1e9 + 7)

int32_t main() {
    int n, k;
    cin >> n >> k;

    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

    for (int r = 1; r <= n; r++) dp[r][1] = 1;
    for (int l = 1; l < k; l++)
        for (int r = 1; r <= n; r++)
            for (int d = r; d <= n; d += r) {
                dp[d][l + 1] += dp[r][l];
                if (dp[d][l + 1] >= MOD) dp[d][l + 1] -= MOD;
            }

    int res = 0;
    for (int r = 1; r <= n; r++) {
        res += dp[r][k];
        if (res >= MOD) res -= MOD;
    }

    cout << res << endl;
    return 0;
}