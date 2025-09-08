#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: substringSwap
// URL: https://atcoder.jp/contests/abc419/tasks/abc419_d
// Difficulty: easy
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    string s, t;
    cin >> s >> t;

    int l, r;
    vector<int> diff(n + 1);
    while (m--) {
        cin >> l >> r;
        l--, r--;
        diff[l] += 1;
        diff[r + 1] -= 1;
    }
    for (int r = 1; r <= n; r++)
        diff[r] += diff[r - 1];

    for (int r = 0; r < n; r++)
        if (diff[r] & 1)
            swap(s[r], t[r]);
    cout << s << endl;
    return 0;
}