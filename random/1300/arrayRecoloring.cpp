#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX 5000

int dp[MAX + 1][MAX + 1][2];
int arr[MAX + 1];

void solve() {
    int n, k;
    cin >> n >> k;

    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    for (int r = 1; r <= n; r++)
        for (int s = 1; s <= k; s++)
            for (int j = 0; j <= 1; j++)
                dp[r][s][j] = LLONG_MIN;

    dp[0][0][0] = 0;
    dp[1][0][0] = 0;
    dp[1][1][0] = arr[1];
    dp[2][0][0] = 0;
    dp[2][1][0] = max(arr[1], arr[2]);
    dp[2][2][0] = arr[1] + arr[2];
    dp[2][1][1] = arr[1] + arr[2];

    for (int r = 3; r <= n; r++)
        for (int s = 1; s <= k; s++) {
            if (r >= s) {
                dp[r][s][0] = arr[r] + dp[r - 1][s - 1][0];
                if (r - 1 >= s)
                    dp[r][s][0] = max(dp[r][s][0], dp[r - 1][s][0]);
            }

            if (r - 1 >= s) {
                int one = max(arr[r] + arr[r - 1] + dp[r - 2][s - 1][0], dp[r - 1][s][1]);
                int two = max(arr[r] + arr[r - 1] + dp[r - 2][s - 1][0], arr[r] + arr[r - 1] + dp[r - 2][s - 2][1]);
                int three = arr[r] + dp[r - 2][s - 1][1];

                dp[r][s][1] = max(one, max(two, three));
            }
        }

    int maxi = LLONG_MIN;
    for (int r = 1; r <= n; r++)
        maxi = max(maxi, dp[r][k][1]);

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