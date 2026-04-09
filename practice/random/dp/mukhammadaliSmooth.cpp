#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (8000)

int arr[MAX + 1];
int cost[MAX + 1];

void solve() {
    int n;
    cin >> n;

    int sum = 0;
    for (int r = 1; r <= n; r++)
        cin >> arr[r];
    for (int r = 1; r <= n; r++)
        cin >> cost[r], sum += cost[r];

    // dp[r] is the maximum cost non-decreasing subsequence in arr[1, r] ending at arr[r]
    vector<int> dp(n + 1, LLONG_MIN);

    dp[1] = cost[1];
    for (int r = 2; r <= n; r++) {
        dp[r] = cost[r];
        for (int l = 1; l < r; l++)
            if (arr[l] <= arr[r])
                dp[r] = max(dp[r], dp[l] + cost[r]);
    }

    int maxi = LLONG_MIN;
    for (int r = 1; r <= n; r++)
        maxi = max(maxi, dp[r]);

    cout << sum - maxi << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}