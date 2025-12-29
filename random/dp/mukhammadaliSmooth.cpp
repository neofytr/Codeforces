#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (8000)

int arr[MAX + 1];
int cost[MAX + 1];

int dp[MAX + 1][0];

void solve() {
    int n;
    cin >> n;

    set<int> s;
    for (int r = 1; r <= n; r++)
        cin >> arr[r], s.insert(arr[r]);
    for (int r = 1; r <= n; r++)
        cin >> cost[r];

    for (auto itr = s.rend(); itr != s.rbegin(); ++itr) {
        for (int r = 1; r <= n; r++)
            dp[r][0] = dp[r][1] = LLONG_MAX;
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