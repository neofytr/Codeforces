#include <bits/stdc++.h>
using namespace std;

#define int long long
constexpr int MOD = 1e9 + 7;
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    dp[0][0] = 1;

    for (int i = 0; i < n; ++i) {
        int v = a[i];
        vector<vector<int>> updates(n + 1, vector<int>(n + 1, 0));

        for (int x = 0; x <= n; ++x)
            for (int y = 0; y <= n; ++y) {
                if (!dp[x][y])
                    continue;
                if (v >= x)
                    updates[v][y] = (updates[v][y] + dp[x][y]) % MOD;
                else if (v >= y)
                    updates[x][v] = (updates[x][v] + dp[x][y]) % MOD;
            }

        for (int x = 0; x <= n; ++x)
            for (int y = 0; y <= n; ++y)
                dp[x][y] = (dp[x][y] + updates[x][y]) % MOD;
    }

    int total_good_subsequences = 0;
    for (int x = 0; x <= n; ++x) {
        for (int y = 0; y <= n; ++y) {
            total_good_subsequences = (total_good_subsequences + dp[x][y]) % MOD;
        }
    }

    cout << total_good_subsequences << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}