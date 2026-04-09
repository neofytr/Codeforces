#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e7)
#define MOD (int)(1e9 + 7)

int dp[MAX + 1];

int32_t main() {
    int n;
    cin >> n;

    // dp[r] is the number of paths of length r from vertex e, where e is in {A, B, C}, to D
    dp[1] = 1;
    dp[0] = 0;
    for (int r = 2; r <= n; r++)
        dp[r] = (2 * dp[r - 1] + 3 * dp[r - 2]) % MOD;

    cout << (3 * dp[n - 1]) % MOD << endl;
    return 0;
}