#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

bool detectCycleDFS(int node, int parent, vector<bool> &visited, vector<vector<int>> &graph) {
    visited[node] = true;
    for (int v : graph[node]) {
        if (!visited[v]) {
            if (detectCycleDFS(v, node, visited, graph)) {
                return true;
            }
        } else if (v != parent) {
            // we found a node that we already visited but isnt' the current parent
            // detected a cycle
            return true;
        }
    }

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
            if (detectCycleDFS(node, -1, visited, graph)) {
                cout << "Cycle detected!" << endl;
                return EXIT_SUCCESS;
            }
        }
    }

    cout << "No cycle!" << endl;
    return EXIT_SUCCESS;
}