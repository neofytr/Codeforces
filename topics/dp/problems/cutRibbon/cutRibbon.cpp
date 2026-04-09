#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: cutRibbon
// URL: https://codeforces.com/problemset/problem/189/A
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, a, b, c;
    cin >> n >> a >> b >> c;

    unordered_set<int> pieces;
    pieces.insert(a);
    pieces.insert(b);
    pieces.insert(c);

    // dp[r] denotes the maximum number of ribbon pieces for cutting ribbons of length r for n >= r >= 0
    vector<int> dp(n + 1, -1); // -1 is for we cannot make it
    dp[0] = 0;
    for (int r = 1; r <= n; r++) {
        for (const int p : pieces)
            if (r >= p && dp[r - p] != -1)
                dp[r] = max(dp[r], dp[r - p] + 1);
    }

    cout << dp[n] << endl;
    return 0;
}