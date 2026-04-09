#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N_MAX (12)
#define V_MAX (ll)(1e4)
#define INF (ll)(1e10)

ll dp[N_MAX + 1][V_MAX + 1];
ll c[N_MAX + 1];

class Solution {
  public:
    int coinChange(const vector<int> &coins, int amount) {
        const int n = static_cast<int>(coins.size());
        for (int r = 1; r <= n; r++)
            c[r] = coins[r - 1];

        // dp[r][v] is the minimum number of coins needed to make the amt v using c[1, r]
        dp[0][0] = 0;
        for (int v = 1; v <= amount; v++)
            dp[0][v] = INF;

        for (int r = 1; r <= n; r++) {
            dp[r][0] = 0;
            for (int v = 1; v <= amount; v++) {
                dp[r][v] = dp[r - 1][v]; // not using the rth coin at all
                if (v >= c[r])
                    dp[r][v] = min(dp[r][v], dp[r][v - c[r]] + 1); // use the rth coin (we can reuse the coin again)
            }
        }

        return (dp[n][amount] >= INF ? -1 : dp[n][amount]);
    }
};