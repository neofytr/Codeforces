#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <vector>
using namespace std;

vector<int> constructPath(int u, int v, vector<vector<int>> &next) {
    if (next[u][v] == -1)
        return {};

    int x = u;
    vector<int> path = {u};
    while (next[x][v] != v) {
        x = next[x][v];
        path.push_back(x);
    }

    return path;
}

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

    // floyd-warshall gives the shortest distance from any node to any other node
    // can also detect negative cycles
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    vector<vector<int>> next(n, vector<int>(n, -1));

    // initialize
    for (int x = 0; x < n; x++) {
        dist[x][x] = 0;
        next[x][x] = x;
    }

    for (auto &[u, v, w] : edges) {
        dist[u][v] = w;
        next[u][v] = v;
    }

    for (int via = 0; via < n; via++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                int uvia = dist[u][via];
                int viav = dist[via][v];
                int uv = dist[u][v];
                if (uvia != INT_MAX && viav != INT_MAX && uvia + viav < uv) {
                    dist[u][v] = uvia + viav;
                    next[u][v] = next[u][via];
                }
            }
        }
    }

    // detect negative cycles
    for (int x = 0; x < n; x++) {
        if (dist[x][x] < 0) {
            cout << "the graph has a negative cycle!\n";
            return EXIT_FAILURE;
        }
    }

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

    return EXIT_SUCCESS;
}