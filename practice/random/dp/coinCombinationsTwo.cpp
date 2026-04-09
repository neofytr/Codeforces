#include <bits/stdc++.h>
using namespace std;

#define int long long
#define X_MAX (int)(1e6)
#define N_MAX (int)(1e2)
#define MOD (int)(1e9 + 7)

int dp[X_MAX + 1];
int c[N_MAX + 1];

int32_t main() {
    int n, x;
    cin >> n >> x;

    for (int r = 1; r <= n; r++)
        cin >> c[r];

    dp[0] = 1;
    for (int v = 1; v <= x; v++)
        dp[v] = 0;

    for (int r = 1; r <= n; r++)
        for (int v = c[r]; v <= x; v++)
            dp[v] = (dp[v] + dp[v - c[r]]) % MOD;

    cout << dp[x] << endl;
    return 0;
}