#include <bits/stdc++.h>
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <vector>
using namespace std;

#define int long long

int32_t main() {
    int n, m;
    cin >> n >> m;

    int u, v, x;
    vector<tuple<int, int, int>> edges;
    vector<vector<int>> graph(n + 1);
    while (m--) {
        cin >> u >> v >> x;
        edges.push_back({u, v, -x}); // we invert the weights so that we can work in terms of minimas and not maximas
        graph[u].push_back(v);
    }

    // its guaranteed that we can always get from 1 to n
    int src = 1;
    int dst = n;
    vector<int> dist(n + 1, LLONG_MAX);
    dist[src] = 0;
    for (int index = 1; index <= n - 1; index++) {
        for (auto &[u, v, w] : edges) {
            if (dist[u] != LLONG_MAX && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // if we have a negative cycle reachable from 1 we can get an arbitratily low score
    // though, there may not be a path through this cycle to the node n
    // if there is a path through this cycle to node n, we can arbitrarily lower the score
    queue<int> que;
    vector<bool> vis(n + 1, false);
    for (auto &[u, v, w] : edges) {
        if (dist[u] != LLONG_MAX && dist[v] > dist[u] + w) {
            if (!vis[u]) {
                vis[u] = true;
                que.push(u);
            }
        }
    }

    while (!que.empty()) {
        int x = que.front();
        que.pop();

        for (int v : graph[x]) {
            if (!vis[v]) {
                vis[v] = true;
                que.push(v);
            }
        }
    }

    if (!vis[dst]) {
        cout << -dist[dst] << endl;
    } else {
        cout << -1 << endl;
    }
    return EXIT_SUCCESS;
}