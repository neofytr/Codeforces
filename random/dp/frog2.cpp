#include <bits/stdc++.h>
using namespace std;

#define int long long
#define N_MAX (int)(1e5)
#define V_MAX (int)(1e4)

int h[N_MAX + 1];
int dp[N_MAX + 1];

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