#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: ilyaAndQueries
// URL: https://codeforces.com/problemset/problem/313/B
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string str;
    cin >> str;

    int n = (int)str.length();

    vector<int> prefix(n + 1, 0);
    for (int r = 2; r <= n; r++) {
        // [0, r - 1]
        prefix[r] += ((str[r - 1] == str[r - 2] ? 1 : 0) + prefix[r - 1]);
    }

    int m;
    cin >> m;
    while (m--) {
        int l, r;
        cin >> l >> r;
        l--, r--; // convert to 0-based
        int ans = prefix[r + 1] - prefix[l];
        if (l >= 1 && str[l] == str[l - 1])
            ans--;
        cout << ans << endl;
    }
    return 0;
}