#include <bits/stdc++.h>
using namespace std;

#define int long long
#define N (int)(1e5)

int arr[N + 1];
int dp[N + 1];  
// dp[r] = 1  iff it is possible to send the segment [1, r]

void solve() {
    int n;
    cin >> n;

    memset(arr, 0, sizeof(int) * (n + 1));
    memset(dp, 0, sizeof(int) * (n + 1));

    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    dp[0] = 1; // trivially true
    for (int r = 1; r <= n; r++) {
        if (dp[r - 1] && (r + arr[r] <= n)) // updates in the forward direction
        	dp[r + arr[r]] = 1;

        // updates the current (along with previous forward updations by previous iterations)
        // so for each r, both cases are covered:
        // 1. the final segment in [1, r] is lengthed by arr[r] (updated in this iteration)
        // 2. the final segment in [1, r] includes arr[r] and is lengthed by some index < r (will be updated in the
        // forward update of that index in its iteration)
        if (r - arr[r] - 1 >= 0) // since r - arr[r] - 1 can be 0, we need to set dp[0] to something
        						 // in this question, true would be correct
        	dp[r] |= dp[r - arr[r] - 1];
    }

    cout << (dp[n] ? "YES" : "NO") << "\n";
}

int32_t main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
