#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e3)
#define MOD (int)(1e9 + 7)

int dp[MAX + 1][MAX + 1];
int grid[MAX + 1][MAX + 1];

int32_t main() {
    int h, w;
    cin >> h >> w;

    char v;
    for (int r = 1; r <= h; r++)
        for (int c = 1; c <= w; c++) {
            cin >> v;
            if (v == '.')
                grid[r][c] = 0;
            else
                grid[r][c] = 1;
        }

    // dp[y][x] is the number of ways to reach (x, y) from (1, 1)
    for (int y = 1; y <= h; y++)
        for (int x = 1; x <= w; x++)
            dp[y][x] = 0;

    dp[1][1] = 1;
    for (int y = 1; y <= h; y++) {
        for (int x = 1; x <= w; x++) {
            if (grid[y][x])
                continue;
            if (x >= 2 && !grid[y][x - 1])
                dp[y][x] = (dp[y][x] + dp[y][x - 1]) % MOD;
            if (y >= 2 && !grid[y - 1][x])
                dp[y][x] = (dp[y][x] + dp[y - 1][x]) % MOD;
        }
    }

    cout << dp[h][w] << endl;
    return 0;
}