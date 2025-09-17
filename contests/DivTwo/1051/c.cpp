#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    vector<int> in_degree(n + 1, 0);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        int x, y;
        cin >> u >> v >> x >> y;
        if (x > y) {
            adj[u].push_back(v);
            in_degree[v]++;
        } else {
            adj[v].push_back(u);
            in_degree[u]++;
        }
    }
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (!in_degree[i]) {
            q.push(i);
        }
    }
    vector<int> topo_order;
    topo_order.reserve(n);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo_order.push_back(u);
        for (int v : adj[u])
            if (!(--in_degree[v]))
                q.push(v);
    }

    vector<int> p(n + 1);
    int current_val = n;
    for (const int node : topo_order) {
        p[node] = current_val;
        current_val--;
    }
    for (int i = 1; i <= n; ++i) {
        cout << p[i] << (i == n ? "" : " ");
    }
    cout << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}