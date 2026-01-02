#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int cnt[MAX + 1];
void solve() {
    int n, k;
    cin >> n >> k;

    set<pair<int, int>> p;
    set<int> elts;

    int v;
    for (int r = 1; r <= n; r++)
        cin >> v, cnt[v]++;

    for (int r = 1; r <= MAX; r++)
        if (cnt[r])
            p.insert({r * cnt[r], r}), elts.insert(r);

    int res = 0;
    while (elts.size() > 1) {
        int x = *elts.begin();
        auto itr =
    }
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}