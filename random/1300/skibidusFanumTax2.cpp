#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1), b(m + 1);
    for (int r = 1; r <= n; r++)
        cin >> a[r];
    for (int r = 1; r <= m; r++)
        cin >> b[r];

    set<int> s;
    vector<vector<int>> dp(n + 1, vector<int>(2, -1));
    dp[1][0] = a[1], dp[1][1] = b[1] - a[1];
    s.insert(b[1]);
    for (int r = 2; r <= n; r++) {
        if (dp[r - 1][0] != -1 && a[r] >= a[r - 1])
            dp[r][0] = a[r];

        if (dp[r - 1][0] != -1 && a[r] < a[r - 1]) {
            auto itr = s.lower_bound(a[r - 1] + a[r]);
            if (itr != s.end()) {
                dp[r][1] = *itr - a[r];
            }
        }

        if (dp[r - 1][1] != -1 && a[r] >= dp[r - 1][1])
            dp[r][0] = a[r];
        if (dp[r - 1][1] != -1 && a[r] < dp[r - 1][1]) {
            auto itr = s.lower_bound(dp[r - 1][1] + a[r]);
            if (itr != s.end()) {
                if (dp[r][1] == -1)
                    dp[r][1] = *itr - dp[r - 1][1];
                else
                    dp[r][1] = min(dp[r][1], *itr - dp[r - 1][1]);
            }
        }

        if (dp[r][0] == -1 && dp[r][1] == -1) {
            cout << "NO\n";
            return;
        }

        s.insert(b[r]);
    }

    cout << "YES\n";
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}