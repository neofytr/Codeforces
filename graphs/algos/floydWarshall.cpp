#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <vector>
using namespace std;

// floyd-warshall algorithm
// finds the shortest path between all pairs of nodes in a weighted, directed graph
// supports negative edge weights
// detects negative cycles

// constructs the actual shortest path from u to v using the "next" matrix
vector<int> constructPath(int u, int v, vector<vector<int>> &next) {
    if (next[u][v] == -1)
        return {}; // no path exists

    int x = u;
    vector<int> path = {u};
    while (x != v) {
        x = next[x][v]; // move to the next node on the path
        path.push_back(x);
    }

    return path;
}

int main() {
    int n, m;
    cin >> n >> m; // n = number of nodes, m = number of edges

    // input edges: (u -> v with weight w)
    vector<tuple<int, int, int>> edges;
    int u, v, w;
    while (m--) {
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    // initialize distance and path tracking matrices
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX)); // dist[u][v] = shortest distance from u to v
    vector<vector<int>> next(n, vector<int>(n, -1));      // next[u][v] = next node to go to from u on shortest path to v

    // set distances for direct edges and initialize "next" matrix
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0; // distance to self is zero
        next[i][i] = i; // path from i to i is trivial
    }
    for (auto &[u, v, w] : edges) {
        dist[u][v] = w; // set direct edge weight
        next[u][v] = v; // to go from u to v directly, next step is v
    }

    // main floyd-warshall loop
    // try every node as an intermediate node (via)
    for (int via = 0; via < n; via++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                // only consider valid paths (avoid integer overflow)
                if (dist[u][via] != INT_MAX && dist[via][v] != INT_MAX) {
                    // if going through "via" is shorter, update distance and path
                    if (dist[u][via] + dist[via][v] < dist[u][v]) {
                        dist[u][v] = dist[u][via] + dist[via][v];
                        next[u][v] = next[u][via]; // path from u to v goes through "via", so take the first step towards "via"
                    }
                }
            }
        }
    }

    // check for negative cycles
    for (int r = 0; r < n; r++) {
        if (dist[r][r] < 0) {
            cout << "graph has a negative cycle!\n";
            return EXIT_FAILURE;
        }
    }

    // print shortest distances and paths
    cout << "Shortest distance matrix:\n";
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (dist[u][v] == INT_MAX) {
                cout << "INF ";
            } else {
                cout << dist[u][v] << " ";
            }
        }
        cout << "\n";
    }

    cout << "\nSample shortest paths:\n";
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (u == v || next[u][v] == -1)
                continue;

            vector<int> path = constructPath(u, v, next);
            cout << "Path from " << u << " to " << v << ": ";
            for (int i = 0; i < path.size(); i++) {
                cout << path[i];
                if (i + 1 < path.size())
                    cout << " -> ";
            }
            cout << " | cost = " << dist[u][v] << "\n";
        }
    }
}
