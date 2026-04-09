#include <bits/stdc++.h>
#include <cstdlib>
#include <deque>
#include <vector>
using namespace std;

// checks if a cycle is reachable from the starting node srcNode
bool detectCycleFromSrc(int srcNode, vector<vector<int>> &adjList, vector<bool> &visited) {
    int n = (int)visited.size();
    deque<pair<int, int>> que; // (node, parentNode)
    visited[srcNode] = true;
    que.push_back({srcNode, -1}); // srcNode has no parent

    while (!que.empty()) {
        auto elt = que.front();
        int node = elt.first;
        int parent = elt.second;

        for (int v : adjList[node]) {
            if (!visited[v]) {
                visited[v] = true;
                que.push_back({v, node});
            } else if (v != parent) {
                // v is visited during traversal but is not the parent node
                // of the current node; this means we have a cycle somewhere
                return true;
            }
        }
    }

    return false;
}

// checks if there is a cycle in the connected components
bool detectCycle(vector<vector<int>> &adjList, vector<bool> &visited) {
    int n = (int)visited.size();
    for (int node = 0; node < n; node++) {
        if (!visited[node]) {
            if (detectCycleFromSrc(node, adjList, visited)) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    int n, m; // vertices, edges
    cin >> n >> m;

    // undirected, unweighted graph
    // 0-indexed nodes (0 to n - 1)
    vector<vector<int>> adjList(n, vector<int>());
    vector<bool> visited(n, false);
    int a, b;
    for (int index = 0; index < m; index++) {
        cin >> a >> b;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }

    return EXIT_SUCCESS;
}