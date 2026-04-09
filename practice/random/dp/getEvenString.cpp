#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int str[MAX + 1];
int prv[MAX + 1][26];
int dp[MAX + 1];

void solve() {
    string s;
    cin >> s;

    int n = (int)s.length();
    for (int r = 1; r <= n; r++)
        str[r] = s[r - 1] - 'a';
    for (int c = 0; c < 26; c++)
        prv[1][c] = -1;

    for (int r = 2; r <= n; r++)
        for (int c = 0; c < 26; c++)
            if (str[r - 1] == c)
                prv[r][c] = r - 1;
            else
                prv[r][c] = prv[r - 1][c];

    // dp[r] is the maximum number of characters we can preserve in str[1, r]
    dp[1] = 0;
    dp[0] = 0;
    for (int r = 2; r <= n; r++)
        if (prv[r][str[r]] == -1)
            dp[r] = dp[r - 1];
        else {
            const int p = prv[r][str[r]];
            dp[r] = max(dp[r - 1], dp[p - 1] + r - p + 1 - (r - 1 - (p + 1) + 1));
        }

    cout << n - dp[n] << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}