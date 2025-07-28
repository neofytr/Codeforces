#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

void traverse(int node, vector<int> &dfs, vector<int> &visited, vector<vector<int>> &adjList) {
    visited[node] = true; // we can mark a node visited after actually visiting it in DFS since we immediately visit a node
    dfs.push_back(node);

    // do work on the vertex node

    for (int v : adjList[node]) {
        if (!visited[v]) {
            traverse(v, dfs, visited, adjList);
        }
    }

    return;
}

int main() {
    int n, m; // nodes, edges
    cin >> n >> m;

    // 1-based node indexing
    vector<vector<int>> adjList(n + 1, vector<int>());
    int a, b;
    for (int index = 0; index < m; index++) {
        cin >> a >> b;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }

    int start;
    cin >> start; // starting node

    vector<int> dfs;
    vector<int> visited(n + 1, false);

    traverse(start, dfs, visited, adjList);
    return EXIT_SUCCESS;
}

void traverseCopy(int node, vector<bool> &visited, vector<int> &dfs, vector<vector<int>> &adjList) {
    visited[node] = true;
    dfs.push_back(node);

    for (int v : adjList[node]) {
        if (!visited[v]) {
            traverseCopy(node, visited, dfs, adjList);
        }
    }

    return;
}

int mainCopy() {
    int n, m; // nodes, edges
    cin >> n >> m;

    // 1-based node indexing
    vector<vector<int>> adjList(n + 1, vector<int>());
    int a, b;
    for (int index = 0; index < m; index++) {
        cin >> a >> b;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }

    int start;
    cin >> start; // starting node

    vector<bool> visited;
    vector<int> dfs;

    traverseCopy(start, visited, dfs, adjList);
    return EXIT_SUCCESS;
}