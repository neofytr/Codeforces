#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)
#define INF (int)(1e9)

int arr[MAX + 1];
int dp[MAX + 1][2];

void solve() {
    int n;
    cin >> n;

    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    for (int r = 1; r <= n; r++)
        for (int s = 0; s <= 1; s++)
            dp[r][s] = 0;

    // dp[r][0] is the minimum number of skip points used to kill [1, r] with the last one killed by me
    // dp[r][1] is the minimum number of skip points used to kill [1, r] with the last one killed by my friend

    dp[0][0] = dp[0][1] = 0;
    dp[1][0] = INF;
    dp[1][1] = arr[1];

    dp[2][0] = arr[1];
    dp[2][1] = arr[1] + arr[2];
    for (int r = 3; r <= n; r++) {
        dp[r][0] = min(dp[r - 1][1], dp[r - 2][1]);
        if (arr[r] == 1 && arr[r - 1] == 1)
            dp[r][1] = min(1 + dp[r - 1][0], 2 + dp[r - 2][0]);
        if (arr[r] == 1 && arr[r - 1] == 0)
            dp[r][1] = min(1 + dp[r - 1][0], 1 + dp[r - 2][0]);
        if (arr[r] == 0 && arr[r - 1] == 1)
            dp[r][1] = min(dp[r - 1][0], 1 + dp[r - 2][0]);
        if (arr[r] == 0 && arr[r - 1] == 0)
            dp[r][1] = min(dp[r - 1][0], dp[r - 2][0]);
    }

    cout << min(dp[n][1], dp[n][0]) << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}