#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <ostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;                           // n = number of nodes, m = number of edges
    vector<vector<pair<int, int>>> graph(n); // adjacency list for the graph

    int start;
    cin >> start; // the starting node for dijkstra

    // read m edges and construct the graph
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w; // the weight is non-negative, since dijkstra's algorithm only works with non-negative weight
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // since the graph is undirected
    }

    vector<int> dist(n, INT_MAX);
    vector<int> parent(n);
    for (int x = 0; x < n; x++) {
        parent[x] = x;
    }
    set<pair<int, int>> minHeap;

    dist[start] = 0;
    minHeap.insert({dist[start], start});
    while (!minHeap.empty()) {
        auto elt = *(minHeap.begin());
        int x = elt.second;
        minHeap.erase(elt);
        for (auto elt : graph[x]) {
            int v = elt.first;
            int w = elt.second;

            if (dist[x] + w < dist[v]) {
                // since we've reached v again with a smaller distance than it was last time visited with,
                // this path isn't coming from the original {dist[v], v}; so it's already in the queue
                // remove it
                minHeap.erase({dist[v], v});
                parent[v] = x;
                dist[v] = dist[x] + w;
                minHeap.insert({dist[v], v});
            }
        }
    }

    // print one of the shortest paths from start to node
    // print -1 if there is no path
    for (int node = 0; node < n; node++) {
        if (dist[node] == INT_MAX)
            cout << -1 << endl;
        else {
            stack<int> path;
            int x = node;
            while (parent[x] != x) {
                path.push(x);
                x = parent[x];
            }
            path.push(start);

            while (!path.empty()) {
                cout << path.top() << " ";
                path.pop();
            }
            cout << endl;
        }
    }

    return EXIT_SUCCESS;
}