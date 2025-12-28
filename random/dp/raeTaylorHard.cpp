#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<int> p(n + 1), idx(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> p[r], idx[p[r]] = r;

    set<int> done;
    done.insert(1);
    for (int r = idx[1] + 1; r <= n; r++)
        done.insert(p[r]);

    for (int r = 2; r <= n; r++)
        if (done.lower_bound(r) == done.end()) {
            cout << "NO\n";
            return;
        }

    cout << "YES\n";
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}