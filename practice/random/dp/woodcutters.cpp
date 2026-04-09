#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)

int x[MAX + 1];
int h[MAX + 1];
int dp[MAX + 1][3];

int32_t main() {
    int n;
    cin >> n;

    for (int r = 1; r <= n; r++)
        cin >> x[r] >> h[r];
    for (int r = 1; r <= n; r++)
        for (int s = 0; s <= 2; s++)
            dp[r][s] = LLONG_MIN;

    dp[1][0] = dp[1][1] = 1;
    dp[1][2] = 0;
    for (int r = 2; r <= n; r++) {
        if (x[r - 1] + h[r - 1] < x[r] - h[r])
            dp[r][0] = max(dp[r][0], dp[r - 1][1] + 1);
        if (x[r - 1] < x[r] - h[r])
            dp[r][0] = max(dp[r][0], max(dp[r - 1][0] + 1, dp[r - 1][2] + 1));

        if (x[r - 1] + h[r - 1] < x[r])
            dp[r][1] = max(dp[r][1], dp[r - 1][1] + 1);
        if (x[r - 1] < x[r])
            dp[r][1] = max(dp[r][1], max(dp[r - 1][0] + 1, dp[r - 1][2] + 1));

        if (x[r - 1] + h[r - 1] < x[r])
            dp[r][2] = max(dp[r][2], dp[r - 1][1]);
        if (x[r - 1] < x[r])
            dp[r][2] = max(dp[r][2], max(dp[r - 1][0], dp[r - 1][2]));
    }

    cout << max(dp[n][0], max(dp[n][1], dp[n][2])) << endl;
    return 0;
}