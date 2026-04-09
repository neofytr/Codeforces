#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (int)(1e9 + 7)

// Problem: coinCombinationsOne
// URL: https://cses.fi/problemset/task/1635
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // consider a money system consisting of n coins
    // each coin has a positive integer value
    // our task is to calculate the number of distinct ways (permutations) we can produce a money sum x using the available coins
    // i.e, we want to calculate the number of different ordered tuples (c1, c2, ..., ci) where ck is from Coins
    // for any i >= 1 such that c1 + ... + ci = x

    int n, x;
    cin >> n >> x;

    vector<int> coins(n);
    for (int &val : coins)
        cin >> val;

    vector<int> dp(x + 1, 0);
    for (const int c : coins)
        if (c <= x)
            dp[c]++;

    for (int r = 1; r <= x; r++) {
        // to make the sum r, we decide on the last coin used
        // for any c <= r, if we decide c to use as the last coin
        // then, we will have an additional dp[r - c] ways to make r
        // so,
        // dp[r] = (summation over all coins c such that c <= r) dp[r - c]

        for (const int c : coins)
            if (c <= r)
                dp[r] = (dp[r] + dp[r - c]) % MOD;
    }

    cout << dp[x] << endl;
    return 0;
}