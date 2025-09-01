#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n, root;
    cin >> n >> root;

    int u, v;
    vector<vector<int>> graph(n);
    for (int r = 1; r <= n - 1; r++)
        cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

    vector<bool> vis(n, false);
    queue<int> que;
    bool leftToRight = true;
    que.push(root);
    vis[root] = true;
    while (!que.empty()) {
        int size = (int)que.size();
        vector<int> level(size);
        for (int r = 0; r < size; r++) {
            const auto node = que.front();
            que.pop();
            const int index = (leftToRight) ? r : size - r - 1;
            level[index] = node;
            for (const int v : graph[node])
                if (!vis[v]) {
                    vis[v] = true;
                    que.push(v);
                }
        }
        for (const int x : level)
            cout << x << " ";
        leftToRight = !leftToRight;
    }
    return EXIT_SUCCESS;
}