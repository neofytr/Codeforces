#include <bits/stdc++.h>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int n, m; // n nodes, m edges
    cin >> n >> m;

    // undirected, unweighted graph
    // 1-based node indexing
    vector<vector<int>> adjList(n + 1, vector<int>());
    int a, b;
    for (int index = 0; index < m; index++) {
        cin >> a >> b;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }

    int start, node;
    cin >> start; // starting node
    vector<bool> visited(n + 1, 0);
    deque<int> que;
    visited[start] = true;
    que.push_back(start);

    while (!que.empty()) {
        node = que.front();
        que.pop_front();

        // do work on the vertex number node

        for (int v : adjList[node]) {
            if (!visited[v]) { // so that we don't do unnecessary cycles
                visited[v] = true;
                que.push_back(v);
            }
        }
    }

    return EXIT_SUCCESS;
}