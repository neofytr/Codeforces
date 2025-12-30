#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (1e5)

int arr[MAX + 1];
int dp[MAX + 1];

void solve() {
    int n;
    cin >> n;

    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    // dp[r] is the maximum number of models that he can buy in the range [1, r] when
    // he is constrained to buy the rth model

    for (int r = 1; r <= n; r++)
        for (int j = r; j <= n; j += r)
            if (arr[j] > arr[r])
                dp[j] += dp[r];
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}