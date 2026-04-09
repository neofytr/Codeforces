#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<int> arr(n + 1), p(n + 1, 0);
    for (int r = 1; r <= n; r++)
        cin >> arr[r], p[r] += p[r - 1] + arr[r];

    set<pair<int, int>> s;
    int maxi = LLONG_MIN;
    s.insert({p[0], 0});
    for (int r = 1; r <= n; r++) {
        if (r != n)
            maxi = max(maxi, p[r] - s.begin()->first);
        else {
            auto [v, idx] = *s.begin();
            if (idx != 0)
                maxi = max(maxi, p[r] - v);
            else {
                auto [nv, nidx] = *(++s.begin());
                maxi = max(maxi, p[r] - nv);
            }
        }

        s.insert({p[r], r});
    }

    if (p[n] > maxi)
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
}