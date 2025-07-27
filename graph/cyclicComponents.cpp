// https://codeforces.com/contest/977/problem/E

#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<vector<int>> &graph, vector<bool> &visited, int &nodes, int &degree) {
    visited[node] = true;
    nodes++;
    degree += graph[node].size();
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited, nodes, degree);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<bool> visited(n, false);
    int cycles = 0;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            int nodes = 0, degree = 0;
            dfs(i, graph, visited, nodes, degree);
            if (degree == 2 * nodes) {
                cycles++;
            }
        }
    }

    cout << cycles << endl;
    return 0;
}
