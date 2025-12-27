#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF 1e10

int32_t main() {
    int n;
    cin >> n;

    vector<int> d(n + 1), c(n + 1);
    for (int r = 1; r <= n; r++) cin >> d[r];
    for (int r = 1; r <= n; r++) cin >> c[r];

    // dp[r][len] is the minimum cost of making a subsequence of length len in [1, r]
    // with the last element of the sequence being r
    vector<vector<int>> dp(n + 1, vector<int>(3 + 1, INF));

    for (int r = 1; r <= n; r++) {
        dp[r][1] = c[r];
        for (int i = 1; i < r; i++)
            if (d[i] < d[r])
                dp[r][2] = min(dp[r][2], dp[i][1] + c[r]);

        for (int i = 1; i < r; i++)
            if (d[i] < d[r])
                dp[r][3] = min(dp[r][3], dp[i][2] + c[r]);
    }

    int mini = INF;
    for (int r = 3; r <= n; r++)
        mini = min(mini, dp[r][3]);

    cout << (mini >= INF ? -1 : mini) << endl;
}