// https://codeforces.com/contest/977/problem/E

#include <bits/stdc++.h>
using namespace std;

bool dfs(int node, vector<vector<int>> &graph, vector<bool> &visited) {
    visited[node] = true;
    bool ans = true;
    if (graph[node].size() != 2)
        ans = false;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            if (!dfs(neighbor, graph, visited)) {
                ans = false;
            }
        }
    }

    return ans;
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
            if (dfs(i, graph, visited)) {
                cycles++;
            }
        }
    }

    cout << cycles << endl;
    return 0;
}
