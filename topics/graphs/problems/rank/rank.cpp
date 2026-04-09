#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: rank
// URL: https://dmoj.ca/problem/acsl1p4
// Difficulty: hard
// Tags: 
// Strategy: 

set<int> cycles;

void dfs(int node, vector<int> &pathArr, vector<bool> path, vector<bool> &vis, vector<vector<int>> &graph) {
    vis[node] = true;
    path[node] = true;
    pathArr.push_back(node);

    for (int v : graph[node])
        if (!vis[v])
            vis[v] = true, dfs(v, pathArr, path, vis, graph);
        else if (path[v]) {
            for (auto itr = pathArr.rbegin(); *itr != v; itr++)
                cycles.insert(*itr);
            cycles.insert(v);
        } // cycle detected
            
    path[node] = false;
    pathArr.pop_back();
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;

    int u, v, s1, s2;
    vector<vector<int>> graph(n + 1);   
    while(k--) {
        cin >> u >> v >> s1 >> s2;
        if (s1 > s2) // u beats v
            graph[u].push_back(v);
        else  // v beats u
            graph[v].push_back(u);
    }

    vector<bool> vis(n + 1, false), path(n + 1, false);
    vector<int> pathArr;

    for (int node = 1; node <= n; node++)
        if (!vis[node])
            dfs(node, pathArr, path, vis, graph);
    
    cout << cycles.size() << endl;
    return 0;
}