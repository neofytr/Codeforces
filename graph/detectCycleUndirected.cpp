#include <bits/stdc++.h>
#include <deque>
#include <vector>
using namespace std;

bool detectCycleFromSrc(int srcNode, vector<bool> &visited, vector<vector<int>> &adjList) {
    deque<pair<int, int>> que; // stores (node, it's parent)
    visited[srcNode] = true;
    que.push_back({srcNode, -1});

    while (!que.empty()) {
        auto elt = que.front();
        int node = elt.first;
        int parent = elt.second;
        que.pop_front();

        for (int v : adjList[node]) {
            if (!visited[v]) {
                visited[v] = true;
                que.push_back({v, node});
            } else if (v != parent) {
                // found a cycle (a node that is connected to the current node that is visited but isnt where it came from)
                return true;
            }
        }
    }

    return false;
}

bool detectCycle(vector<bool> &visited, vector<vector<int>> &adjList) {
    int n = (int)visited.size();
    for (int node = 0; node < n; node++) {
        if (!visited[node]) {
            if (detectCycleFromSrc(node, visited, adjList)) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    int n, m; // nodes, edges
    cin >> n >> m;

    // undirected, unweighted graph
    // 0-indexed nodes
    vector<vector<int>> adjList(n, vector<int>());
    int a, b;
    for (int index = 1; index <= m; index++) {
        cin >> a >> b;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }
    vector<bool> visited(n, false);
}