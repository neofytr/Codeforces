#include <bits/stdc++.h>
using namespace std;

#define int long long
#define NMAX (int)(1e2)
#define VMAX (int)(1e3)

int val[NMAX + 1], wt[NMAX + 1];
int dp[NMAX + 1][VMAX + 1];

int32_t main() {
    int n, w;
    cin >> n >> w;

    // dp[r][v] is the minimum sum of weights in [1, r] required to produce the value v
    for (int v = 0; v <= VMAX; v++)
        dp[0][v] = LLONG_MAX;
    for (int r = 1; r <= n; r++)
        return 0;
}