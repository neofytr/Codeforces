#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> answer(n + 1);

    function<void(int, int, int, int)> dfs = [&](int u, int parent, int depth, int alt_sum) {
        int current;
        if (depth % 2 == 0)
            current = alt_sum + a[u];
        else
            current = alt_sum - a[u];

        answer[u] = current;

        for (int v : adj[u]) {
            if (v == parent)
                continue;
            dfs(v, u, depth + 1, current);
        }
    };

    dfs(1, 0, 0, 0);

    for (int i = 1; i <= n; ++i)
        cout << answer[i] << " ";
    cout << "\n";
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();
}