#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // directed, weighted graph
    // 0-indexed nodes
    int u, v, w;
    vector<tuple<int, int, int>> edges;
    while (m--) {
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    // bellman-ford algorithm finds the shortest path from source node to all the other nodes in the graph
    int src;
    cin >> src;

    vector<int> parent(n);
    for (int x = 0; x < n; x++) {
        parent[x] = x;
    }

    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    for (int i = 1; i <= n - 1; i++) {
        for (auto &[u, v, w] : edges) {
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    // shortest distance from a src node to any other node is defined only if there is not any
    // negative cycle that is reachable from the src node

    // negative cycle detection
    for (auto &[u, v, w] : edges) {
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            cout << "negative cycle detected in the graph!\n";
            return EXIT_FAILURE;
        }
    }

    // path reconstruction
    // generate one of the shortest path from src to a node

    for (int x = 0; x < n; x++) {
        if (dist[x] == INT_MAX) {
            cout << "No path from " << src << " to " << x << endl;
            continue;
        }

        int u = x;
        stack<int> pt;
        while (u != parent[u]) {
            pt.push(u);
            u = parent[u];
        }
        pt.push(src);

        cout << src << " to " << x << " -> ";
        while (!pt.empty()) {
            cout << pt.top() << " ";
            pt.pop();
        }
        cout << endl;
    }

    return EXIT_SUCCESS;
}