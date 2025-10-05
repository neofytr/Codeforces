#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int s, f, r;
    cin >> s >> f >> r;

    vector<int> dr(n + 1, LLONG_MAX);
    queue<int> que;
    dr[r] = 0;
    que.push(r);
    while (!que.empty()) {
        int x = que.front();
        que.pop();

        for (int v : graph[x])
            if (dr[v] > dr[x] + 1)
                dr[v] = dr[x] + 1, que.push(v);
    }

    vector<int> ds(n + 1, LLONG_MAX);
    queue<pair<int, int>> q; // (current node, maximum of minimum distance to r on any shortest path from s to current node)

    ds[s] = 0;
    q.push({s, dr[s]});

    while (!q.empty()) {
        unordered_map<int, int> mp;
        int sz = q.size();
        while (sz--) {
            auto [x, d] = q.front();
            q.pop();

            if (x == f) {
                cout << d << endl;
                break;
            }

            for (int v : graph[x])
                if (ds[v] >= ds[x] + 1)
                    ds[v] = ds[x] + 1, mp[v] = max(mp[v], d);
        }

        for (auto &[v, d] : mp)
            q.push({v, min(d, dr[v])});
    }

    return 0;
}
