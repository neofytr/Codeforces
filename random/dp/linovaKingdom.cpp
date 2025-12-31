#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<int>> adj;
vector<int> depth;
vector<int> sz;

void dfs(int u, int p, int d) {
    depth[u] = d;
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, d + 1);
            sz[u] += sz[v];
        }
    }
}

int32_t main() {
    int n, k;
    cin >> n >> k;

    adj.resize(n + 1);
    depth.resize(n + 1);
    sz.resize(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0, 0);

    vector<int> values;
    for (int i = 1; i <= n; i++) {
        values.push_back(depth[i] - (sz[i] - 1));
    }

    sort(values.rbegin(), values.rend());

    int ans = 0;
    for (int i = 0; i < k; i++) {
        ans += values[i];
    }

    cout << ans << endl;
    return 0;
}