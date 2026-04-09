#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: buildingRoads
// URL: https://cses.fi/problemset/task/1666
// Difficulty: medium
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;

    int u, v;
    vector<vector<int>> graph(n);
    while(m--) 
        cin >> u >> v, u--, v--, graph[v].push_back(u), graph[u].push_back(v);

    int cnt = 0;
    vector<bool> vis(n, false);
    queue<int> que;
    vector<pair<int, int>> res;
    int prev = -1;
    for (int node = 0; node < n; node++)
        if (!vis[node]) {
            cnt++;
            if (prev != -1)
                res.push_back({prev, node}), prev = node;
            else 
                prev = node;
            int src = node;
            vis[src] = true;
            que.push(src);
            while(!que.empty()) {
                int x = que.front();
                que.pop();

                for (int v : graph[x])
                    if (!vis[v])
                        vis[v] = true, que.push(v);
            }
        }
    cout << cnt - 1 << endl;
    for (auto &[u, v] : res)
        cout << u + 1 << " " << v + 1 << endl;
    return 0;
}
