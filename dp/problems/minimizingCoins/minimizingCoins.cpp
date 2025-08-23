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

    // consider a money system consisting of n coins
    // each coin has a positive integer value
    // our task is to produce a sum of money x using the available coins in such a way that the
    // number of coins used is minimal

    int n, x;
    cin >> n >> x;
    vector<int> coins(n);
    for (int &val : coins)
        cin >> val;

    // dp[r] is the minimum number of coins used to produce the sum r
    vector<int> dp(x + 1, LLONG_MAX);
    // all the coin denominations can be made using exactly one coin
    for (const int c : coins)
        if (c <= x)
            dp[c] = 1;

    for (int r = 1; r <= x; r++) {
        // dp[r] = min (over all c in coins such that r >= c and dp[r - c] != LLONG_MAX) (dp[r - c] + 1)
        for (const int c : coins)
            if (r >= c && dp[r - c] != LLONG_MAX)
                dp[r] = min(dp[r], dp[r - c] + 1);
    }
    if (dp[x] == LLONG_MAX)
        cout << -1 << endl;
    else
        cout << dp[x] << endl;
    return 0;
}