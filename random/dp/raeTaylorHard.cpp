#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<int> p(n + 1), idx(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> p[r], idx[p[r]] = r;

    set<int> done, leftidx;
    for (int r = 1; r <= n; r++)
        leftidx.insert(r);

    vector<pair<int, int>> edges;

    for (int r = 1; r <= n; r++) {
        vector<int> tmp;
        auto itr = leftidx.find(idx[r]);
        if (itr == leftidx.end())
            continue;

        if (done.empty()) {
            for (auto it = itr; it != leftidx.end(); ++it)
                if (p[*it] >= r)
                    tmp.push_back(*it), done.insert(p[*it]);

            for (int e : tmp) {
                if (idx[e] != idx[r])
                    edges.push_back({idx[r], idx[e]});
                leftidx.erase(e);
            }
            continue;
        }

        auto it = done.lower_bound(r);
        if (it == done.end()) {
            cout << "NO\n";
            return;
        }

        for (it = itr; it != leftidx.end(); ++it) {
            if (p[*it] >= r)
                done.insert(p[*it]), tmp.push_back(*it);
        }

        for (int e : tmp) {
            if (idx[e] != idx[r])
                edges.push_back({idx[r], idx[e]});
            leftidx.erase(e);
        }
    }

    cout << "YES\n";
    for (auto &[u, v] : edges)
        cout << u << " " << v << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}