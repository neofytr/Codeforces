#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (1e9 + 7)

int n, m, k, x;

int32_t main() {
    cin >> n >> m;

    int u, v;
    vector<vector<int>> tree(n + 1);
    for (int r = 1; r <= n - 1; r++) {
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    cin >> k >> x;


    return 0;
}