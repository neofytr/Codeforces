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

    // dp[k][r] is the number of distinct ways we can produce a money sum r using the coins in the index range [0, k]
    vector<vector<int>> dp(n, vector<int>(x + 1, 0));

    // so, to construct the money sum r using coins [0, k]
    // we can either pick the coin k and construct the sum r - k (if r >= k) from the coins [0, k]
    // or we don't pick the coin and construct the sum from the coins [0, k - 1]
    // dp[k][r] = dp[k][r - k] + dp[k - 1][r]

    // base cases ->
    // we need dp[0][...] and dp[...][0]

    for (int k = 0; k < n; k++)
        dp[k][0] = 1; // there is exactly one way to make the sum 0
    for (int r = 0; r <= x; r++)
        dp[0][r] = (!(r % coins[0]) ? 1 : 0); // if we can make r using some number of coins[0], we put it to one

    for (int r = 1; r <= x; r++)
        for (int k = 1; k < n; k++)
            dp[k][r] = (r >= coins[k] ? dp[k][r - coins[k]] : 0) + dp[k - 1][r];

    cout << dp[n - 1][x] << endl;
    return 0;
}