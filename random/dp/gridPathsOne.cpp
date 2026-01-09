#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (int)(1e9 + 7)
#define MAX (int)(1e3)

int grid[MAX + 1][MAX + 1];
int dp[MAX + 1][MAX + 1];

int32_t main() {
    int n;
    cin >> n;

    string str;
    for (int r = 1; r <= n; r++) {
        cin >> str;
        for (int c = 1; c <= n; c++)
            grid[r][c] = (str[c - 1] == '.' ? 0 : 1);
    }

    for (int r = 1; r <= n; r++)
        for (int c = 1; c <= n; c++)
            dp[r][c] = 0;

    if (!grid[1][1])
        dp[1][1] = 1;
    for (int r = 1; r <= n; r++)
        for (int c = 1; c <= n; c++) {
            if (grid[r][c])
                continue;
            if (r >= 2)
                dp[r][c] = (dp[r][c] + dp[r - 1][c]) % MOD;
            if (c >= 2)
                dp[r][c] = (dp[r][c] + dp[r][c - 1]) % MOD;
        }

    cout << dp[n][n] << endl;
    return 0;
}