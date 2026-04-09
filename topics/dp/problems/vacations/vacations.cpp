#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: vacations
// URL: https://codeforces.com/problemset/problem/698/A
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> arr(n + 1);
    for (int index = 1; index <= n; index++) {
        cin >> arr[index];
        arr[index]++;
    }

    // dp[r][k] is the minimum number of rest days in the initial r days with the rth day having kth work
    // k = 0 for rest, 1 for sport and 2 for contest
    vector<vector<int>> dp(n + 1, vector<int>(3, LLONG_MAX));
    dp[1][0] = 1;
    if (arr[1] == 2)
        dp[1][2] = 0;
    if (arr[1] == 3)
        dp[1][1] = 0;
    if (arr[1] == 4) {
        dp[1][1] = 0;
        dp[1][2] = 0;
    }

    for (int r = 2; r <= n; r++) {
        if (arr[r] == 1) {
            // gym is closed and there is no contest
            // this is a rest day
            dp[r][0] = min(dp[r - 1][0], min(dp[r - 1][1], dp[r - 1][2])) + 1;
        } else if (arr[r] == 2) {
            // gym is closed but the contest is carried out
            dp[r][0] = min(dp[r - 1][0], min(dp[r - 1][1], dp[r - 1][2])) + 1;
            dp[r][2] = min(dp[r - 1][0], dp[r - 1][1]);
        } else if (arr[r] == 3) {
            // gym is open but contest is not carried out
            dp[r][0] = min(dp[r - 1][0], min(dp[r - 1][1], dp[r - 1][2])) + 1;
            dp[r][1] = min(dp[r - 1][0], dp[r - 1][2]);
        } else {
            // both gym and contest are open
            dp[r][0] = min(dp[r - 1][0], min(dp[r - 1][1], dp[r - 1][2])) + 1;
            dp[r][1] = min(dp[r - 1][0], dp[r - 1][2]);
            dp[r][2] = min(dp[r - 1][0], dp[r - 1][1]);
        }
    }

    cout << min(dp[n][0], min(dp[n][1], dp[n][2])) << endl;
    return 0;
}