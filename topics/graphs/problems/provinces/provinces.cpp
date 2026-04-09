#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

void traverse(int node, vector<bool> &visited, vector<vector<int>> &adjList) {
    visited[node] = true;

    for (int v : adjList[node]) {
        if (!visited[v]) {
            traverse(v, visited, adjList);
        }
    }
}

int main() {
    // undirected, unweighted graph
    int n, m; // vertices, edges
    cin >> n >> m;

    // 1-based node indexing
    vector<vector<int>> adjList(n + 1, vector<int>());
    int a, b;
    for (int index = 1; index <= m; index++) {
        cin >> a >> b;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }

    // a province is a collection of nodes such that we there is a path from one node to
    // another between any two nodes in the collection, and there is no path from any node of the
    // collection to any node outside the collection

    // we are to count the number of provinces
    int count = 0;
    vector<bool> visited(n + 1);
    for (int node = 1; node <= n; node++) {
        if (!visited[node]) {
            count++;
            traverse(node, visited, adjList);
        }
    }

    cout << count << endl;
    return EXIT_SUCCESS;
}