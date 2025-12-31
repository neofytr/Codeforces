#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<int> arr(n + 1), p(n + 1, 0);
    for (int r = 1; r <= n; r++)
        cin >> arr[r], p[r] = p[r - 1] ^ arr[r];

    if (!p[n]) {
        cout << "YES\n";
        return;
    }

    int l = 1, r = 1, cnt = 0;
    while (l <= n) {
        r = l;
        while (r <= n && ((p[r] ^ p[l - 1]) != p[n]))
            r++;
        if (r <= n && p[r] ^ p[l - 1] == p[n])
            cnt++;
        l = r + 1;
    }

    if (cnt >= 3)
        cout << "YES\n";
    else
        cout << "NO\n";
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}