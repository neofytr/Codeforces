#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // a connected, undirected and weighted graph with 0-indexed nodes
    // such a graph always has an MST
    // an unconnected, undirected and weighted graph doesn't have an MST
    vector<vector<pair<int, int>>> graph(n); // adjacency list: node -> [(neighbor, weight)]
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    vector<bool> vis(n, false);
    vector<pair<int, int>> mst; // (parent, node)
    int sum = 0;

    // min-heap: (weight, node, parent)
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
    pq.push({0, 0, -1}); // start from node 0

    while (!pq.empty()) {
        auto [weight, node, parent] = pq.top();
        pq.pop();

        if (vis[node])
            continue;
        vis[node] = true;

        if (parent != -1) {
            mst.push_back({parent, node});
            sum += weight;
        }

        for (auto &[neighbor, edge_weight] : graph[node]) {
            if (!vis[neighbor]) {
                pq.push({edge_weight, neighbor, node});
            }
        }
    }

    // check if all nodes were included (graph must be connected)
    if (mst.size() != n - 1) {
        cout << "Graph is not connected. MST not possible.\n";
        return 1;
    }

    // output MST and total weight
    cout << "MST weight = " << sum << "\n";
    for (auto &[u, v] : mst)
        cout << u << " - " << v << "\n";

    return EXIT_SUCCESS;
}
