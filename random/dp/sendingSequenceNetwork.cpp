#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int b[MAX + 1];
bool dp[MAX + 1];

void solve() {
    int n;
    cin >> n;

    for (int r = 1; r <= n; r++)
        cin >> b[r], dp[r] = false;

    // dp[r] is true iff [1, r] is good
    dp[0] = true;
    for (int r = 1; r <= n; r++) {
        if (dp[r - 1] && r + b[r] <= n)
            dp[r + b[r]] = true;
        if (r - b[r] >= 1 && dp[r - b[r] - 1])
            dp[r] = true;
    }

    cout << (dp[n] ? "YES\n" : "NO\n");
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}