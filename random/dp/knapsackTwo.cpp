#include <bits/stdc++.h>
using namespace std;

#define int long long
#define N_MAX (int)(1e2)
#define V_MAX (int)(1e6)
#define INF (int)(1e14)

int val[N_MAX + 1], wt[N_MAX + 1];
int dp[N_MAX + 1][V_MAX + 1];

int32_t main() {
    int n, w;
    cin >> n >> w;

    for (int r = 1; r <= n; r++)
        cin >> wt[r] >> val[r];

    // dp[r][v] is the minimum sum of weights in [1, r] required to produce the value v
    dp[0][0] = 0;
    for (int v = 1; v <= V_MAX; v++)
        dp[0][v] = INF;
    for (int r = 1; r <= n; r++) {
        dp[r][0] = 0;
        for (int v = 1; v <= V_MAX; v++) {
            dp[r][v] = dp[r - 1][v]; // not take the current item
            if (v >= val[r])
                dp[r][v] = min(dp[r][v], dp[r - 1][v - val[r]] + wt[r]); // take the current item
        }
    }

    for (int v = V_MAX; v >= 0; v--)
        if (dp[n][v] <= w) {
            cout << v << endl;
            break;
        }
    return 0;
}