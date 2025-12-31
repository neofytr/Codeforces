#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int arr[MAX + 1];
int dp[MAX + 1];

void solve() {
    int n, k;
    cin >> n >> k;

    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    // dp[r] is the length of the longest subarray starting at r such that each two times an element is greater than its previous, except for the rth element
    dp[n] = 1;
    for (int r = n - 1; r >= 1; r--)
        if (2 * arr[r + 1] > arr[r])
            dp[r] = dp[r + 1] + 1;
        else
            dp[r] = 1;

    int cnt = 0;
    for (int r = 1; r <= n; r++)
        if (dp[r] >= (k + 1))
            cnt++;

    cout << cnt << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}