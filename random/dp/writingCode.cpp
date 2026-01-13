#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX 500

int dp[2][MAX + 1][MAX + 1];
int arr[MAX + 1];

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, b, mod;
    cin >> n >> m >> b >> mod;

    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    // dp[i][j][k] is the number of non-negative integral sequences v1, v2, .., vi 
    // of length i such that v1 + v2 ... + vi = j and v1 * a1 + ... vi * ai = k
    dp[0][0][0] = 1;

    for (int i = 1; i <= n; i++) {
        int cur = i & 1;
        int pre = cur ^ 1;

        // clear current layer
        for (int j = 0; j <= m; j++)
            for (int k = 0; k <= b; k++)
                dp[cur][j][k] = dp[pre][j][k];

        // prefix-sum transition (vi >= 1)
        for (int j = 1; j <= m; j++) {
            for (int k = arr[i]; k <= b; k++) {
                dp[cur][j][k] = (dp[cur][j][k] + dp[cur][j - 1][k - arr[i]]) % mod;
            }
        }
    }

    int cnt = 0;
    int last = n & 1;
    for (int k = 0; k <= b; k++)
        cnt = (cnt + dp[last][m][k]) % mod;

    cout << cnt << endl;
    return 0;
}
