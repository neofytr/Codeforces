#include <bits/stdc++.h>
#include <vector>
using namespace std;

bool detectCycleFromNode(int node, int parent, vector<bool> &visited, vector<vector<int>> &adjList) {
    int n = (int)visited.size();
    visited[node] = true;

    for (int v : adjList[node]) {
        if (!visited[v]) {
            if (detectCycleFromNode(v, node, visited, adjList))
                return true;
        } else if (v != parent) {
            // found a node that has been visited but isnt' the current node's parent
            return true;
        }
    }
    return false;
}

bool detectCycle(vector<bool> &visited, vector<vector<int>> &adjList) {
    int n = (int)visited.size();
    for (int node = 0; node < n; node++) {
        if (!visited[node]) {
            if (detectCycleFromNode(node, -1, visited, adjList)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int n, m; // nodes, edges
    cin >> n >> m;

    // undirected graph
    // 0-based node indexing (0 to n - 1)
    vector<vector<int>> adjList(n, vector<int>());
    vector<bool> visited(n, false);
    int a, b;
    while (m--) {
        cin >> a >> b;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }
}