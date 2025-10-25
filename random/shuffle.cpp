#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n, x, m;
    cin >> n >> x >> m;

    int left = x, right = x;

    while (m--) {
        int l, r;
        cin >> l >> r;
        // if this interval overlaps or touches the current one
        if (r >= left && l <= right) {
            left = min(left, l);
            right = max(right, r);
        }
    }

    cout << right - left + 1 << "\n";
}

int32_t main() {
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
