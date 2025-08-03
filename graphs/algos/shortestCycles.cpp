#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;

int main() {
    // undirected, unweighted graph
    int n, m;
    cin >> n >> m;

    int u, v;
    vector<vector<int>> graph(n, vector<int>());
    while (m--) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int minCycle = INT_MAX;
    for (int src = 0; src < n; src++) {
        vector<bool> vis(n, false);
        queue<pair<int, int>> que;
        vector<int> dist(n, INT_MAX);

        vis[src] = true;
        que.push({src, -1});
        dist[src] = 0;
        bool found = false;
        while (!que.empty() && !found) {
            auto elt = que.front();
            que.pop();

            int x = elt.first;
            int parent = elt.second;
            for (int v : graph[x]) {
                if (!vis[v]) {
                    vis[v] = true;
                    dist[v] = dist[x] + 1;
                    que.push({v, x});
                } else if (v != parent) {
                    // cycle detected
                    minCycle = min(minCycle, dist[v] + dist[x] + 1);
                    found = true;
                }
            }
        }
    }

    if (minCycle == INT_MAX)
        cout << 0 << endl;
    else
        cout << minCycle << endl;
    return EXIT_SUCCESS;
}