#include <bits/stdc++.h>
#include <vector>
using namespace std;

bool detectCycleFromSrc(int currNode, int parent, vector<bool> &visited, vector<vector<int>> &adjList) {
    int n = (int)visited.size();
    visited[currNode] = true;

    for (int v : adjList[currNode]) {
        if (!visited[v]) {
            if (detectCycleFromSrc(v, currNode, visited, adjList)) {
                return true;
            }
        } else if (v != parent) {
            // cycle found; a node that is not the current node's parent is already visited
            return true;
        }
    }

    return false;
}

bool detectCycle(vector<bool> &visited, vector<vector<int>> &adjList) {
    int n = (int)visited.size();
    // check for all connected components
    for (int node = 0; node < n; node++) {
        if (!visited[node]) {
            if (detectCycleFromSrc(node, -1, visited, adjList))
                return true;
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