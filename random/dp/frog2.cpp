#include <bits/stdc++.h>
using namespace std;

#define int long long
#define NMAX (int)(1e5)
#define VMAX (int)(1e4)

int h[NMAX + 1];
int dp[NMAX + 1];

int32_t main() {
    int n, k;
    cin >> n >> k;

    for (int r = 1; r <= n; r++)
        cin >> h[r];

    // dp[r] is the minimum cost to reach stone r
    for (int r = 1; r <= n; r++)
        dp[r] = LLONG_MAX;

    dp[1] = dp[0] = 0;
    for (int r = 1; r <= n; r++)
        for (int s = 1; s <= k; s++)
            dp[r + s] = min(dp[r + s], dp[r] + abs(h[r] - h[r + s]));

    cout << dp[n] << endl;
}