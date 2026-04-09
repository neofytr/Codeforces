#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: flightRoutesCheck
// URL: https://cses.fi/problemset/task/1682
// Difficulty: medium
// Tags: 
// Strategy: 

void dfs(int x, vector<bool> &vis, vector<vector<int>> &graph) {
    vis[x] = true;

    for (int v : graph[x])
        if (!vis[v])
            dfs(v, vis, graph);
}

int32_t main() {
    int n, m;
    cin >> n >> m;

    int u, v;
    vector<vector<int>> graph(n + 1);
    vector<vector<int>> revGraph(n + 1);
    while(m--)
        cin >> u >> v, graph[u].push_back(v), revGraph[v].push_back(u);

    int src = 1;
    // We want to find all the nodes in the SCC of src
    vector<int> vis(n + 1, false), revVis(n + 1, false);
    queue<int> que;

    que.push(src);
    vis[src] = true;
    while(!que.empty()) {
        int x = que.front();
        que.pop();

        for (int v : graph[x])
            if (!vis[v])
                vis[v] = true, que.push(v);
    }

    que.push(src);
    revVis[src] = true;
    while(!que.empty()) {
        int x = que.front();
        que.pop();

        for (int v : revGraph[x])
            if (!revVis[v])
                revVis[v] = true, que.push(v);
    }

    for (int node = 1; node <= n; node++) {
        if (!revVis[node]) {
            cout << "NO\n";
            cout << node << " " << src << "\n";
            return 0;
        }
        if (!vis[node]) {
            cout << "NO\n";
            cout << src << " " << node << "\n";
            return 0;
        }
    }
        

    cout << "YES\n";
    return 0;
}