#include <bits/stdc++.h>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;

// dfs to collect all paths from start to end in the modified graph
void dfs(int node, int end, vector<bool> &path, vector<vector<int>> &modifiedGraph, vector<vector<int>> &paths) {
    int n = (int)path.size();
    path[node] = true; // mark node as visited in current path
    if (node == end) {
        vector<int> temp;
        for (int x = 0; x < n; x++) {
            if (path[x])
                temp.push_back(x); // collect nodes in the current path
        }
        paths.push_back(temp); // store one complete path
        path[node] = false;    // backtrack
        return;
    }

    for (int v : modifiedGraph[node]) {
        if (!path[v]) // don't revisit in same path
            dfs(v, end, path, modifiedGraph, paths);
    }

    path[node] = false; // backtrack
    return;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);         // original graph
    vector<vector<int>> modifiedGraph(n); // graph that only contains shortest path edges

    int start, end;
    cin >> start >> end;

    // read m edges
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // assuming undirected graph
    }

    vector<int> dist(n, -1); // distance from start
    queue<int> que;

    dist[start] = 0;
    que.push(start);

    // bfs to calculate distance and build modified graph
    while (!que.empty()) {
        int size = (int)que.size();
        while (size--) {
            int node = que.front();
            que.pop();

            for (int v : graph[node]) {
                if (dist[v] == -1) {
                    // not explored till now
                    dist[v] = dist[node] + 1;
                    modifiedGraph[node].push_back(v); // one-way edges since there's no need for undirected edges
                    que.push(v);                      // next level
                } else {
                    // the node is visited
                    // there can be two cases, either it's on the same level as node, or on the next level
                    // if it's on the same level, there's no need to consider it, it won't give the shortest path anyway
                    if (dist[v] == dist[node] + 1) {
                        modifiedGraph[node].push_back(v); // valid next node on shortest path
                    }
                }
            }
        }
    }

    vector<vector<int>> paths;                   // all shortest paths
    vector<bool> path(n, false);                 // visited marker per path
    dfs(start, end, path, modifiedGraph, paths); // enumerate all shortest paths

    // print the paths
    for (auto &p : paths) {
        for (int x : p)
            cout << x << " ";
        cout << "\n";
    }

    return EXIT_SUCCESS;
}
