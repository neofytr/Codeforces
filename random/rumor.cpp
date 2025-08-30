#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);
    vector<int> gold(n);
    for (int &val : gold)
        cin >> val;

    int u, v;
    while (m--) {
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<bool> vis(n, false);
    int cost = 0;
    for (int node = 0; node < n; node++) {
        if (!vis[node]) {
            int src = node;
            int mini = gold[src];

            queue<int> que;
            que.push(src);
            vis[src] = true;
            while (!que.empty()) {
                int x = que.front();
                que.pop();
                mini = min(mini, gold[x]);
                for (int v : graph[x]) {
                    if (!vis[v]) {
                        que.push(v);
                        vis[v] = true;
                    }
                }
            }

            cost += mini;
        }
    }

    cout << cost << endl;
    return EXIT_SUCCESS;
}