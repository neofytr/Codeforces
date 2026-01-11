#include <bits/stdc++.h>
using namespace std;

#define int long long
#define WMAX (int)(1e5)
#define NMAX (int)(1e2)

int dp[WMAX + 1];
int wt[NMAX + 1], val[NMAX + 1];

int32_t main() {
    int n, W;
    cin >> n >> W;

    for (int r = 1; r <= n; r++)
        cin >> wt[r] >> val[r];

    for (int w = 0; w <= W; w++)
        dp[w] = 0;

    for (int r = 1; r <= n; r++)
        for (int w = W; w >= wt[r]; w--)
            // either take dp[r - 1][w] (represented by dp[w]), or dp[r - 1][w - wt[r] + val[r] (represented by dp[w - wt[r]])
            dp[w] = max(dp[w - wt[r]] + val[r], dp[w]);
    // since we are iterating backwards, dp[w - wt[r]] still contains dp[r - 1][w - wt[r]] and dp[w] still contains dp[r - 1][w]
    // and after the updating, dp[w] (or dp[r][w] after updating) won't be used for updating any lower dps

    cout << dp[W] << endl;
    return 0;
}