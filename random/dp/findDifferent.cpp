#include <bits/stdc++.h>
using namespace std;

#define int long long
#define N_MAX (int)(2 * 1e5)
#define ELTMAX (int)(1e6)

int arr[N_MAX + 1];
int dp[N_MAX + 1];

void solve() {
    int n;
    cin >> n;

    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    dp[1] = 1;
    for (int r = 2; r <= n; r++)
        if (arr[r] == arr[r - 1])
            dp[r] = dp[r - 1] + 1;
        else
            dp[r] = 1;

    int q, l, r;
    cin >> q;
    while (q--) {
        cin >> l >> r;
        if (dp[r] >= (r - l + 1))
            cout << -1 << " " << -1 << endl;
        else {
            cout << r << " " << r - dp[r] << endl;
        }
    }
    cout << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}