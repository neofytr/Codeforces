#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: orac
// URL: https://codeforces.com/problemset/problem/1350/B
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> arr(n + 1);
        for (int r = 1; r <= n; r++)
            cin >> arr[r];

        // dp[r] is the maximum number of models ending at index r
        vector<int> dp(n + 1, 1);
        dp[1] = 1;
        int maxi = 1;
        for (int r = 2; r <= n; r++) {
            for (int i = 1; i * i <= r; i++)
                if (!(r % i)) {
                    int one = i;
                    int two = r / i;
                    if (one < r && arr[one] < arr[r])
                        dp[r] = max(dp[r], dp[one] + 1);
                    if (two < r && arr[two] < arr[r])
                        dp[r] = max(dp[r], dp[two] + 1);
                }
            maxi = max(maxi, dp[r]);
        }
        cout << maxi << endl;
    }
    return 0;
}