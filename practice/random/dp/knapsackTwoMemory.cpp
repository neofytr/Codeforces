#include <bits/stdc++.h>
using namespace std;

#define int long long
#define V_MAX (int)(1E6)
#define N_MAX (int)(1E2)
#define INF (int)(1E15)

int dp[V_MAX + 1];
int val[N_MAX + 1], wt[N_MAX + 1];

int32_t main() {
    int n, w;
    cin >> n >> w;

    for (int r = 1; r <= n; r++)
        cin >> wt[r] >> val[r];

    dp[0] = 0;
    for (int v = 1; v <= V_MAX; v++)
        dp[v] = INF;

    for (int r = 1; r <= n; r++)
        for (int v = V_MAX; v >= val[r]; v--)
            dp[v] = min(dp[v], dp[v - val[r]] + wt[r]);

    for (int v = V_MAX; v >= 0; v--)
        if (dp[v] <= w) {
            cout << v << endl;
            break;
        }

    return 0;
}