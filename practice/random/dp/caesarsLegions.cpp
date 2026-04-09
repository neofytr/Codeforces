#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (int)(1e8)

int dp[100 + 1][100 + 1][10 + 1][10 + 1];
// For dp[i][j][r][s] ->
// 1. i footmen
// 2. j horsemen
// 3. r footmen at the end
// 4. s horsemen at the end

// There are only two possible cases:
// 1. r > 0 and s = 0
// 2. r = 0 and s > 0

int32_t main() {
    int n1, n2, k1, k2;
    cin >> n1 >> n2 >> k1 >> k2;

    dp[0][0][0][0] = 1;
    for (int i = 0; i <= n1; i++)
        for (int j = 0; j <= n2; j++)
            for (int r = 0; r <= k1; r++)
                for (int s = 0; s <= k2; s++) {
                    if (r && s)
                        continue; // invalid state

                    const int cnt = dp[i][j][r][s];
                    // place horseman
                    if (j < n2 && s < k2)
                        dp[i][j + 1][0][s + 1] = (dp[i][j + 1][0][s + 1] + cnt) % MOD;

                    // place footman
                    if (i < n1 && r < k1)
                        dp[i + 1][j][r + 1][0] = (dp[i + 1][j][r + 1][0] + cnt) % MOD;
                }

    int res = 0;
    for (int r = 0; r <= k1; r++)
        res = (res + dp[n1][n2][r][0]) % MOD;

    for (int s = 1; s <= k2; s++)
        res = (res + dp[n1][n2][0][s]) % MOD;
    cout << res << endl;
    return 0;
}