#include <bits/stdc++.h>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;

int main() {
    // connected, undirected and weighted graph with 0-indexed nodes
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n);
    int u, v, w;
    while (m--) {
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    vector<pair<int, int>> mst;
    vector<bool> vis(n, false);
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq; // weight, node, parent
    int sum = 0;

    pq.push({0, 0, -1});
    while (!pq.empty()) {
        auto [weight, node, parent] = pq.top();
        pq.pop();

        if (vis[node])
            continue;

        sum += weight;
        mst.push_back({node, parent});
        for (auto &[v, w] : graph[node]) {
            if (!vis[v]) {
                pq.push({w, v, node});
            }
        }
    }

    if (mst.size() != n - 1) {
        cout << "The graph is not connected! No MST possible!\n";
        return EXIT_FAILURE;
    }

    cout << "MST total weight -> " << sum << endl;
    cout << "MST Edges -> \n";
    for (auto &[u, v] : mst) {
        cout << u << " " << v << endl;
    }

    return EXIT_SUCCESS;
}