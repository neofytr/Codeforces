#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;

// undirected graph
// weighted edges with non-negative weights
// 0-indexed nodes

// graph[r] = {(u, w) where u is the node r - u and w is the edge weight}

// this algorithm finds the minimum-cost path from start to all other nodes in the graph
// only works with non-negative weights

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n);
    int a, b, w;
    while (m--) {
        cin >> a >> b >> w;
        graph[a].push_back({b, w});
        graph[b].push_back({a, w});
    }

    int start;
    cin >> start;

    vector<bool> selected(n, false);
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap; // sorted by pair.first (distance)

    dist[start] = 0;
    minHeap.push({dist[start], start});

    while (!minHeap.empty()) {
        int node = minHeap.top().second;
        minHeap.pop();
        if (!selected[node]) {
            selected[node] = true;
            for (auto elt : graph[node]) {
                int v = elt.first;
                int w = elt.second;

                if (dist[node] + w < dist[v]) {
                    dist[v] = dist[node] + w;
                    minHeap.push({dist[v], v});
                }
            }
        }
    }

    for (int node = 0; node < n; node++) {
        cout << "min distance from node " << start << " to node " << node << " is -> " << dist[node] << "\n";
    }

    return EXIT_SUCCESS;
}