#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: removingDigits
// URL: https://cses.fi/problemset/task/1637
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    // we are given an integer n
    // on each step, we may subtract one of the digits from the number
    // what is the minimum number of steps needed to make the number equal to 0?

    // dp[r] is the minimum number of steps needed to make the number equal to 0
    vector<int> dp(n + 1);
    dp[0] = 0;
    for (int r = 1; r <= n; r++) {
        // how many unique digits does r have?
        dp[r] = LLONG_MAX;
        unordered_set<int> un;
        int x = r;
        while (x) {
            un.insert(x % 10);
            x /= 10;
        }

        for (const int d : un)
            if (dp[r - d] != LLONG_MAX)
                dp[r] = min(dp[r], dp[r - d] + 1);
    }

    cout << dp[n] << endl;
    return 0;
}