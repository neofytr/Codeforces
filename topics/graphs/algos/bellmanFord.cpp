#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // 0-indexed edges
    // weighted, directed graph
    vector<tuple<int, int, int>> edges(m);
    int u, v, w;
    while (m--) {
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    int src;
    cin >> src;
    if (src >= n)
        return EXIT_FAILURE;

    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, 0);
    for (int x = 0; x < n; x++) {
        parent[x] = x;
    }
    dist[src] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (auto &[u, v, w] : edges) {
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) { // relax the edge
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    bool negativeCycleDetected = false;
    for (auto &[u, v, w] : edges) {
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            negativeCycleDetected = true;
            break;
        }
    }

    if (negativeCycleDetected)
        cout << "the graph has a negative cycle\n";
    else {
        for (int node = 0; node < n; node++) {
            stack<int> path;
            int x = node;
            while (x != parent[x]) {
                path.push(x);
                x = parent[x];
            }
            path.push(x);
            cout << src << " to " << node << " -> ";
            while (!path.empty()) {
                cout << path.top() << " ";
                path.pop();
            }
            cout << "\n";
        }
    }

    return EXIT_SUCCESS;
}
