#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)

int dp[MAX + 1];
int cnt[MAX + 1];

int32_t main() {
    int n;
    cin >> n;

    int v, maxi = LLONG_MIN;
    for (int r = 1; r <= n; r++)
        cin >> v, cnt[v]++, maxi = max(maxi, v);

    dp[0] = 0;
    dp[1] = 1 * cnt[1];
    for (int r = 2; r <= MAX; r++)
        dp[r] = max(r * cnt[r] + dp[r - 2], dp[r - 1]);

    cout << dp[maxi] << endl;
    return 0;
}