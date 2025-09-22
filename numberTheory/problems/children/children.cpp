#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: children
// URL: https://codeforces.com/problemset/problem/1850/F
// Difficulty: medium
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

        int val;
        unordered_map<int, int> mp;
        for (int r = 1; r <= n; r++)
            cin >> val, mp[val]++;

        int maxi = -1;
        for (int r = 1; r <= n; r++) {
            int cnt = 0;
            for (int d = 1; d * d <= r; d++)
                if (!(r % d)) {
                    cnt += mp[d];
                    if (d != r / d)
                        cnt += mp[r / d];
                }
            maxi = max(maxi, cnt);
        }
        cout << maxi << endl;
    }
    return 0;
}