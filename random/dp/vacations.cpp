#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (100)

int arr[MAX + 1];
int dp[MAX + 1][3];

int32_t main() {
    int n;
    cin >> n;

    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    for (int r = 1; r <= n; r++) {
        if (!arr[r]) {
            dp[r][0] = dp[r][1] = dp[r][2] = min(dp[r - 1][0], min(dp[r - 1][1], dp[r - 1][2])) + 1;
        }

        if (arr[r] == 1) {
            dp[r][0] = min(dp[r - 1][0], min(dp[r - 1][1], dp[r - 1][2])) + 1;
            dp[r][1] = min(dp[r - 1][0], dp[r - 1][2]);
            dp[r][2] = min(dp[r - 1][0], min(dp[r - 1][1], dp[r - 1][2])) + 1;
        }

        if (arr[r] == 2) {
            dp[r][0] = min(dp[r - 1][1], dp[r - 1][2]);
            dp[r][1] = min(dp[r - 1][0], min(dp[r - 1][1], dp[r - 1][2])) + 1;
            dp[r][2] = min(dp[r - 1][0], min(dp[r - 1][1], dp[r - 1][2])) + 1;
        }

        if (arr[r] == 3) {
            dp[r][0] = min(dp[r - 1][1], dp[r - 1][2]);
            dp[r][1] = min(dp[r - 1][0], dp[r - 1][2]);
            dp[r][2] = min(dp[r - 1][0], min(dp[r - 1][1], dp[r - 1][2])) + 1;
        }
    }

    cout << min(dp[n][0], min(dp[n][1], dp[n][2])) << endl;
    return 0;
}