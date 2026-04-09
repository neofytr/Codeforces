#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (int)(1e9 + 7)
#define MAX (100)

int dp[MAX + 1];
int mp[MAX + 1];

int32_t main() {
    int n, k, d;
    cin >> n >> k >> d;

    // dp[r] is the number of paths with sum r from the root of the tree with no edges of length d
    // mp[r] is the number of paths with sum r from the root of the tree

    dp[0] = 1;
    if (d != 1)
        dp[1] = 1;
    for (int r = 2; r <= n; r++)
        for (int s = 1; s < d; s++)
            if (r >= s)
                dp[r] = (dp[r] + dp[r - s]) % MOD;

    mp[0] = mp[1] = 1;
    for (int r = 2; r <= n; r++)
        for (int s = 1; s <= k; s++)
            if (r >= s)
                mp[r] = (mp[r] + mp[r - s]) % MOD;

    cout << (mp[n] - dp[n] + MOD) % MOD << endl;
    return 0;
}