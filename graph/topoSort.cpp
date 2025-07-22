#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

void traverse(int node, vector<bool> &visited, vector<vector<int>> &graph, stack<int> &st) {
    visited[node] = true;
    for (int v : graph[node]) {
        if (!visited[v]) {
            traverse(v, visited, graph, st);
        }
    }

    st.push(node);
    return;
}

int main() {
    // directed, acyclic graph
    // 0-indexed nodes
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n, vector<int>());
    int a, b;
    while (m--) {
        cin >> a >> b; // a -> b
        graph[a].push_back(b);
    }

    vector<int> topoSort;
    // topological ordering for the nodes of a graph is a linear ordering of the nodes of
    // the graph such that if there are nodes a and b in the graph such that a -> b, then, in the
    // ordering, if i and j are the indexed of a and b respectively, then i < j

    vector<bool> visited(n, false);
    stack<int> st;
    for (int node = 0; node < n; node++) {
        if (!visited[node]) {
            traverse(node, visited, graph, st);
        }
    }

    while (!st.empty()) {
        topoSort.push_back(st.top());
        st.pop();
    }

    for (int node : topoSort) {
        cout << node << " ";
    }
    cout << endl;
    return EXIT_SUCCESS;
}