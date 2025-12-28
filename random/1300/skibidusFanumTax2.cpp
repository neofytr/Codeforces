#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve(int t) {
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> a[r];

    set<int> s;
    int val;
    for (int r = 1; r <= m; r++)
        cin >> val, s.insert(val);

    // dp[r] is the minimum value possible on the rth place
    // it is always optimal to set an element to its minimum possible value that will make the
    // array non-decreasing
    vector<int> dp(n + 1, LLONG_MAX);
    dp[1] = min(a[1], *s.begin() - a[1]);
    for (int r = 2; r <= n; r++) {
        const int prev = dp[r - 1];
        if (a[r] >= prev)
            dp[r] = a[r];
        if (auto itr = s.lower_bound(prev + a[r]); itr != s.end() && *itr - a[r] >= prev)
            dp[r] = min(dp[r], *itr - a[r]);

        if (dp[r] == LLONG_MAX) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
}

int32_t main() {
    int t;
    cin >> t;

    for (int r = 1; r <= t; r++) {
        solve(r);
    }
    return 0;
}