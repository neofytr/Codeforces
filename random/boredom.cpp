// https://codeforces.com/problemset/problem/455/A
#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    int n;
    cin >> n;

    int val;
    unordered_map<int, int> mp;
    for (int r = 1; r <= n; r++)
        cin >> val, mp[val]++;

    // dp[r] is the maximum number of points we can get if we consider numbers from [0, r]
    vector<int> dp(100001);
    dp[0] = 0;
    dp[1] = mp[1];

    for (int r = 2; r <= 100001; r++)
        // we can either take the current number, or not
        dp[r] = max(dp[r - 2] + r * mp[r], dp[r - 1]);

    cout << dp[100001] << endl;
    return 0;
}
