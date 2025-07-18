#include <bits/stdc++.h>
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
    vector<int> bfs;
    deque<int> que;
    que.push_back(start);

    while (!que.empty()) {
        node = que.front();
        que.pop_front();

        bfs.push_back(node);
        // do work on the vertex number node

        for (int v : adjList[node]) {
            if (!visited[v]) {     // so that we don't do unnecessary cycles
                visited[v] = true; // since we don't visit the vertices v immediately, it may so happen that some v1 is linked to v2,
                                   // and v1 is pushed first, then v2, and when v1 is visited, v2 isnt visited yet, but v2 is one
                                   // of the neighbours of v1 and isn't marked visited yet and thus gets added to the queue again
                que.push_back(v);
            }
        }
    }

    return EXIT_SUCCESS;
}