#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (1e9 + 7)

int cnt(int node, int parent, int strongLeft, bool parentStrong, vector<vector<int>> &tree) {
    int res = 0;
    if (!parentStrong && strongLeft >= 1) // the current node can be strong
        for (int v : tree[node])
            if (v != parent)
}

int32_t main() {
    int n, m;
    cin >> n >> m;

    int u, v;
    vector<vector<int>> tree(n + 1);
    for (int r = 1; r <= n - 1; r++) {
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    int k, x;
    cin >> k >> x;
    return 0;
}