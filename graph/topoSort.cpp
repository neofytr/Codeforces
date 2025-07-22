#include <bits/stdc++.h>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;

void bfs(int node, vector<bool> &visited, vector<int> &topSort, vector<vector<int>> &graph) {
    queue<int> que;
    bool addAtEnd = false;
    que.push(node);
    if (graph[node].size()) {
        topSort.push_back(node);
    } else {
        addAtEnd = true;
    }

    while (!que.empty()) {
        int n = que.front();
        que.pop();

        for (int v : graph[n]) {
            if (!visited[v]) {
                topSort.push_back(v);
                visited[v] = true;
                que.push(v);
            }
        }
    }

    if (addAtEnd) {
        topSort.push_back(node);
    }
    return;
}

int main() {
    // Directed, Acyclic Graph
    // 0-indexed nodes
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n, vector<int>());
    int a, b;
    while (m--) {
        cin >> a >> b; // a -> b
        graph[a].push_back(b);
    }

    vector<int> topSort;
    // if some nodes a, b in the graph are such that a -> b, then
    // the index of a and b in topSort, say, i and j, should be such that i < j
    // if the graph is acylic, such a ordering always exists

    vector<bool> visited(n, false);
    for (int node = 0; node < n; node++) {
        if (!visited[node]) {
            visited[node] = true;
            bfs(node, visited, topSort, graph);
        }
    }

    for (int v : topSort) {
        cout << v << " ";
    }

    cout << "\n";
    return EXIT_SUCCESS;
}