#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int arr[MAX + 1];
int dp[MAX + 1];

int cnt(const int idx, const int n) {
    if (idx > n)
        return LLONG_MAX;
    if (dp[idx] != -1)
        return dp[idx];

    return dp[idx] = min(cnt(idx + arr[idx] + 1, n), 1 + cnt(idx + 1, n));
}

void solve() {
    int n;
    cin >> n;

    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    for (int r = 1; r <= n; r++)
        dp[r] = -1;

    // dp[r] is the minimum number of deletions required in [r, n] to make it beautiful
    cout << cnt(1, n) << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}