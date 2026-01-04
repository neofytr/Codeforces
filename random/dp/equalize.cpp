#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e6)

int dp[MAX + 1][2];
int near[MAX + 1][2];
int A[MAX + 1], B[MAX + 1];

int32_t main() {
    int n;
    cin >> n;

    string a, b;
    cin >> a >> b;

    for (int r = 1; r <= n; r++)
        A[r] = a[r - 1] - '0', B[r] = b[r - 1] - '0';

    for (int r = 1; r <= n; r++)
        for (int s = 0; s <= 1; s++)
            near[r][s] = LLONG_MAX;

    near[1][0] = near[1][1] = LLONG_MAX;
    for (int r = 2; r <= n; r++) {
        if (!A[r - 1] && B[r - 1])
            near[r][0] = r - 1;
        else
            near[r][0] = near[r - 1][0];

        if (A[r - 1] && !B[r - 1])
            near[r][1] = r - 1;
        else
            near[r][1] = near[r - 1][1];
    }

    dp[0][0] = dp[0][1] = 0;
    for (int r = 1; r <= n; r++) {
        if (A[r] == B[r]) {
            dp[r][0] = dp[r - 1][0];
            dp[r][1] = dp[r - 1][1];
            continue;
        }

        if (!A[r] && B[r]) {
            int idx = near[r][1];
            if (idx != LLONG_MAX)
                dp[r][0] = min(dp[idx - 1][0], dp[idx - 1][1]) + abs(r - idx);

            dp[r][1] = min(dp[r - 1][0], dp[r - 1][1]) + 1;
        }

        if (A[r] && !B[r]) {
            int idx = near[r][0];
            if (idx != LLONG_MAX)
                dp[r][0] = min(dp[idx - 1][0], dp[idx - 1][1]) + abs(r - idx);

            dp[r][1] = min(dp[r - 1][0], dp[r - 1][1]) + 1;
        }
    }

    cout << min(dp[n][0], dp[n][1]) << endl;
    return 0;
}