#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: minimizingCoins
// URL: https://cses.fi/problemset/task/1634
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    cin >> n >> x;

    vector<int> coins(n);
    for (int &val : coins)
        cin >> val;

    // dp[r] is the minimum number of coins required to make the sum r
    vector<int> dp(x + 1, LLONG_MAX);
    for (const int c : coins)
        if (c <= x)
            dp[c] = 1;

    for (int r = 1; r <= x; r++) {
        for (const int c : coins)
            if (r - c >= 1 && dp[r - c] != LLONG_MAX)
                dp[r] = min(dp[r], 1 + dp[r - c]);
    }

    if (dp[x] == LLONG_MAX)
        cout << -1 << endl;
    else
        cout << dp[x] << endl;
    return 0;
}