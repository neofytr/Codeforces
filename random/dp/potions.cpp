#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (2000)

int arr[MAX + 1];
int dp[MAX + 1][MAX + 1];

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n))
        return 0;

    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    for (int r = 0; r <= n; r++)
        for (int s = 0; s <= n; s++)
            dp[r][s] = -1;

    for (int r = 0; r <= n; r++)
        dp[r][0] = 0;

    for (int r = 1; r <= n; r++)
        for (int s = 1; s <= r; s++) {
            if (dp[r - 1][s] != -1)
                dp[r][s] = max(dp[r][s], dp[r - 1][s]);

            if (dp[r - 1][s - 1] != -1)
                if (dp[r - 1][s - 1] + arr[r] >= 0)
                    dp[r][s] = max(dp[r][s], dp[r - 1][s - 1] + arr[r]);
        }

    int maxi = 0;
    for (int s = 0; s <= n; s++)
        if (dp[n][s] != -1)
            maxi = s;

    cout << maxi << endl;
    return 0;
}