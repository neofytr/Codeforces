#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m; // n = number of vertices, m = number of edges

    vector<tuple<int, int, int>> edges;

    // reading all edges
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w; // edge from u to v with weight w
        edges.push_back({u, v, w});
    }

    int source;
    cin >> source; // source node for shortest paths

    vector<int> dist(n, INT_MAX); // stores shortest distance from source to each node
    vector<int> parent(n, -1);    // stores parent of each node for path reconstruction

    dist[source] = 0; // distance to source is 0

    // relax all edges n - 1 times
    // because the shortest path can have at most n - 1 edges
    for (int i = 1; i <= n - 1; i++) {
        for (auto [u, v, w] : edges) {
            // if u is reachable and going from u to v gives a shorter path
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w; // update distance
                parent[v] = u;         // update parent
            }
        }
    }

    // one more iteration to check for negative-weight cycles
    bool hasNegativeCycle = false;
    for (auto [u, v, w] : edges) {
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            hasNegativeCycle = true;
            break;
        }
    }

    if (hasNegativeCycle) {
        cout << "negative weight cycle detected" << endl;
    } else {
        // print shortest distances and paths
        for (int i = 0; i < n; i++) {
            cout << "distance to node " << i << " = ";
            if (dist[i] == INT_MAX) {
                cout << "INF" << endl;
            } else {
                cout << dist[i] << ", path = ";

                // reconstruct path from source to i
                vector<int> path;
                for (int cur = i; cur != -1; cur = parent[cur]) {
                    path.push_back(cur);
                }
                reverse(path.begin(), path.end());
                for (int x : path) {
                    cout << x << " ";
                }
                cout << endl;
            }
        }
    }

    return 0;
}
