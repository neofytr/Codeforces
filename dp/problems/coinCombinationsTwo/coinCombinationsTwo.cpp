#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: coinCombinationsTwo
// URL: https://cses.fi/problemset/task/1636
// Difficulty: hard
// Tags:
// Strategy:

#define MOD (int)(1e9 + 7)

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;

    vector<int> coins(n);
    for (int &val : coins)
        cin >> val;

    // consider a money system consisting of n coins
    // each coin has a positive integer value
    // our task if to calculate the number of distinct ways we can produce a money sum x using the available coins

    // dp[r] = number of distinct ways to form sum r using the coins we've processed so far
    vector<int> dp(x + 1, 0);
    dp[0] = 1;

    for (const int c : coins)
        for (int r = c; r <= x; r++) {
            // since we can't form anything less than c with a coin = c
            dp[r] += dp[r - c]; // we add the coin c to the distinct ways of making sum = r - c
            // this won't overcount since this is the first time we're using c to build the sum r
            // also, since we count up (from r = c to x), we can reuse the coins
            if (dp[r] >= MOD)
                dp[r] -= MOD; // fast modulo
        }

    /*
     * Go coin by coin; for each sum s, add all ways to make s - c using coins seen so far.
     * Because coins are outer, orders don’t multiply; because s goes up, you can reuse the same coin many times.
     */
    cout << dp[x] << endl;
    return 0;
}