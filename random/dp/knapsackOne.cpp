#include <bits/stdc++.h>
using namespace std;

#define int long long
#define WMAX (int)(1e5)
#define NMAX (int)(1e2)

int dp[NMAX + 1][WMAX + 1];
int wt[NMAX + 1], val[NMAX + 1];

int32_t main() {
    int n, W;
    cin >> n >> W;

    for (int r = 1; r <= n; r++)
        cin >> wt[r] >> val[r];

    // dp[r][w] is the maximum possible value that can be taken with a selection whose total weight is at-most w, and the
    // selection being taken from [1, r]
    for (int r = 1; r <= n; r++)
        for (int w = 1; w <= W; w++) {
            dp[r][w] = dp[r - 1][w];
            if (wt[r] <= w)
                dp[r][w] = max(dp[r][w], val[r] + dp[r - 1][w - wt[r]]);
        }

    // the answer is dp[n][W]
    // suppose, we also wanted to reconstruct the selection
    vector<int> e;
    for (int r = n; r >= 1; r--)
        if (dp[r][W] != dp[r - 1][W])
            e.push_back(r), W -= wt[r];

    for (const int idx : e)
        cout << idx << " ";
    cout << endl;
    return 0;
}