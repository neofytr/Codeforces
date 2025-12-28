#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> arr(n + 1);
    for (int r = 1; r <= n; r++) cin >> arr[r];

    vector<vector<int>> p(n + 1, vector<int>(k + 1, LLONG_MIN));
    vector<vector<int>> m(n + 1, vector<int>(k + 1, LLONG_MIN));

    // dp[r][s][0] is the maximum cost of coloring s elements blue in [1, r] with r being the last colored
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(k + 1, vector<int>(2, LLONG_MIN)));

    for (int r = 1; r <= n; r++)
        for (int s = 1; s <= k; s++) {

        }

    int maxi = LLONG_MIN;
    for (int r = 1; r <= n; r++)
        maxi = max(dp[r][k][1], maxi);
    cout << maxi << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}