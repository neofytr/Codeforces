#include <bits/stdc++.h>
using namespace std;

#define int long long
#define N (int)(1e5)

int H1[N + 1];
int H2[N + 1];
int dp[N + 1][3];

int32_t main() {
    int n;
    cin >> n;

    for (int r = 1; r <= n; r++)
        cin >> H1[r];
    for (int r = 1; r <= n; r++)
        cin >> H2[r];

    dp[1][0] = H1[1], dp[1][1] = H2[1], dp[1][2] = 0;
    for (int r = 2; r <= n; r++) {
        dp[r][0] = H1[r] + max(dp[r - 1][1], dp[r - 1][2]);
        dp[r][1] = H2[r] + max(dp[r - 1][0], dp[r - 1][2]);
        dp[r][2] = max(dp[r - 1][0], max(dp[r - 1][1], dp[r - 1][2]));
    }

    cout << max(dp[n][0], max(dp[n][1], dp[n][2])) << endl;
    return 0;
}