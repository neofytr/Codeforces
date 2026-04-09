#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int str[MAX + 1];
int dp[MAX + 1][26];

int cnt(const int l, const int r, const int c) {
    if (l == r)
        return str[l] != c;

    int mid = l + (r - l) / 2;
    int len = (r - l + 1) / 2;
    int one = dp[mid][c] - dp[l - 1][c];
    int two = dp[r][c] - dp[mid][c];

    return min(len - one + cnt(mid + 1, r, c + 1), len - two + cnt(l, mid, c + 1));
}

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    for (int r = 1; r <= n; r++)
        str[r] = s[r - 1] - 'a';

    for (int c = 0; c < 26; c++)
        dp[0][c] = 0;
    for (int r = 1; r <= n; r++)
        for (int c = 0; c < 26; c++)
            dp[r][c] = dp[r - 1][c] + (str[r] == c ? 1 : 0);

    cout << cnt(1, n, 0) << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}