#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<int> arr(n + 1), p(n + 1, 0);
    for (int r = 1; r <= n; r++)
        cin >> arr[r], p[r] = p[r - 1] ^ arr[r];

    vector<vector<int>> dp(n + 1);
    dp[1] = {arr[1]};
    for (int r = 2; r <= n; r++) {
        dp[r] = dp[r - 1];
    }
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}