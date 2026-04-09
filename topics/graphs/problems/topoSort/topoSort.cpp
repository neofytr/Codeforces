#include <bits/stdc++.h>
#include <cstdlib>
#include <stack>
#include <vector>
using namespace std;

void dfs(int node, vector<bool> &visited, vector<vector<int>> &graph, stack<int> &st) {
    visited[node] = true;
    for (int v : graph[node]) {
        if (!visited[v]) {
            dfs(v, visited, graph, st);
        }
    }
    st.push(node); // starts pushing from the last node
    return;
}

int main() {
    int n, m;
    cin >> n >> m;

    // directed acyclic graph
    vector<vector<int>> graph(n + 1, vector<int>());
    int a, b;
    while (m--) {
        cin >> a >> b; // a -> b
        graph[a].push_back(b);
    }

    // a topological ordering for a directed graph is a linear ordering of all of it's nodes
    // such that if there are nodes a and b in the graph such that a -> b, then, a comes before b
    // in the ordering

    // a directed graph has a topological ordering only if it doesn't have any cycles

    stack<int> st;
    vector<bool> visited(n + 1, false);
    for (int node = 1; node <= n; node++) {
        if (!visited[node]) {
            dfs(node, visited, graph, st);
        }
    }

    vector<int> topoSort;
    while (!st.empty()) {
        topoSort.push_back(st.top());
        st.pop();
    }

    for (int v : topoSort) {
        cout << v << " ";
    }
    cout << "\n";
    return EXIT_SUCCESS;
}