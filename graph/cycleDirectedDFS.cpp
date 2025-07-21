#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

bool detectCycleDFS(int node, vector<bool> &onPath, vector<bool> &visited, vector<vector<int>> &graph) {
    visited[node] = true;
    onPath[node] = true;
    for (int v : graph[node]) {
        if (!visited[v]) {
            if (detectCycleDFS(v, onPath, visited, graph)) {
                return true;
            }
        } else if (onPath[v]) {
            // we have already encountered this node during our path
            // we have a cycle
            // just using visited won't do the trick since we can't be sure of a cycle even if
            // we encounter a visited node again since it may not be possible to reach from that visited
            // node to the cycle start due to the graph being directed
            return true;
        }
    }
    onPath[node] = false;
    return false;
}

int main() {
    int n, m; // vertices, edges
    cin >> n >> m;

    // directed graph
    // 0-indexed nodes (from 0 to n - 1)
    vector<vector<int>> graph(n, vector<int>());
    int a, b; // a -> b
    while (m--) {
        cin >> a >> b;
        graph[a].push_back(b); // we can go to b from a, but not vice versa
    }

    vector<bool> visited(n, false);
    for (int node = 0; node < n; node++) {
        if (!visited[node]) {
            vector<bool> onPath(n, false);
            if (detectCycleDFS(node, onPath, visited, graph)) {
                cout << "Cycle detected!" << endl;
                return EXIT_SUCCESS;
            }
        }
    }

    cout << "No cycle!" << endl;
    return EXIT_SUCCESS;
}