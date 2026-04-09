#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)

int arr[MAX + 1];
int dp[MAX + 1][3];

// j * arr[f] >= x
// j >= x / arr[f]

void solve() {
    int n, x;
    cin >> n >> x;

    for (int r = 1; r <= n; r++)
        cin >> arr[r];
    for (int r = 1; r <= n; r++)
        for (int s = 0; s <= 2; s++)
            dp[r][s] = 0;

    sort(arr + 1, arr + n);
    for (int r = 1; r <= n; r++) {
        dp[r][0] = max(dp[r - 1][0], max(dp[r - 1][1], dp[r - 1][2]));
    }
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}