#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"
#define MOD (int)(1e9 + 7)
// Problem: diceCombinations
// URL: https://cses.fi/problemset/task/1633
// Difficulty: easy
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    // dp[r] is the number of ways to construct the sum r by throwing a die one of more times
    deque<int> dp;
    // queue front -> {a, b, c, d, e, f} <- queue back
    // this is a space optimized solution
    dp.push_back(1); // dp[0]
    dp.push_back(0); // dp[-1]
    dp.push_back(0); // dp[-2]
    dp.push_back(0); // dp[-3]
    dp.push_back(0); // dp[-4]
    dp.push_back(0); // dp[-5]
    for (int r = 1; r <= n; r++) {
        int dpr = 0;
        for (const int e : dp) // iterates from front to back
            dpr = (dpr + e) % MOD;
        dp.push_front(dpr);
        dp.pop_back();
    }
    cout << dp.front() << endl;
    return 0;
}