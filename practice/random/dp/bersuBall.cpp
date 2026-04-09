#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (100)

// dp[i][j] is the maximum number of pairs we can get after using the first i boys and first j girls
int dp[MAX + 1][MAX + 1];

int32_t main() {
    int n;
    cin >> n;
    vector<int> b(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> b[r];

    int m;
    cin >> m;
    vector<int> g(m + 1);
    for (int r = 1; r <= m; r++)
        cin >> g[r];

    sort(b.begin() + 1, b.end());
    sort(g.begin() + 1, g.end());

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (abs(b[i] - g[j]) <= 1)
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            dp[i][j] = max(dp[i][j], max(dp[i][j - 1], dp[i - 1][j]));
        }

    cout << dp[n][m] << endl;
    return 0;
}