#include <bits/stdc++.h>
using namespace std;

#define int long long
#define NMAX (int)(1e3)
#define XMAX (int)(1e5)

int cost[NMAX + 1];
int pages[NMAX + 1];
int dp[XMAX + 1];
int32_t main() {
    int n, x;
    cin >> n >> x;

    for (int r = 1; r <= n; r++)
        cin >> cost[r];
    for (int r = 1; r <= n; r++)
        cin >> pages[r];

    // dp[r][p] is the maximum number of pages we can buy in [1, r] such that the total price is <= p
    for (int p = 0; p <= x; p++)
        dp[p] = 0;
    for (int r = 1; r <= n; r++) 
        for (int p = x; p >= cost[r]; p--) 
                dp[p] = max(dp[p], dp[p - cost[r]] + pages[r]);
    cout << dp[x] << endl;
    return 0;   
}
