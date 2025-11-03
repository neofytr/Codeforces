#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (998244353)
#define MAX (int)(2e5 + 1)

int32_t main() {
    int n, k;
    cin >> n >> k;

    int l, r;
    vector<pair<int, int>> segs;
    while (k--) {
        cin >> l >> r;
        segs.push_back({l, r});
    }

    // dp[r] is the number of ways to reach cell r starting from cell 1 for all 1 <= r <= n
    vector<int> dp(n + 1, 0);
    dp[1] = 1;

    vector<int> pref(n + 1, 0);
    pref[1] = dp[1];
    for (int r = 2; r <= n; r++) {
        for (auto &[left, right] : segs) {
            dp[r] = (dp[r] + pref[max(0LL, r - left)] - pref[max(0LL, r - right - 1)]) % MOD;
        }
        pref[r] = (pref[r - 1] + dp[r]) % MOD;
    }

    cout << (dp[n] + MOD) % MOD << endl;
    return 0;
}