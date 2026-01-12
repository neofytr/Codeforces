#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX 500

int dp[MAX + 1][MAX + 1][MAX + 1];
int arr[MAX + 1];
int p[MAX + 1][MAX + 1];

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, b, mod;
    cin >> n >> m >> b >> mod;

    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    dp[0][0][0] = 1;
    for (int i = 1; i <= n; i++) 
        for (int j = 0; j <= m; j++) 
            for (int k = 0; k <= b; k++) {
                dp[i][j][k] = 0;
                for (int v = 0; v <= j; v++) {
                    int cost = arr[i] * v;
                    if (k >= cost) 
                        dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j - v][k - cost]) % mod;
                }
            }
        
    int ans = 0;
    for (int k = 0; k <= b; k++)
        ans = (ans + dp[n][m][k]) % mod;

    cout << ans << "\n";
    return 0;
}
