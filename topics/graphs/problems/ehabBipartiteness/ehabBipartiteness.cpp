#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: ehabBipartiteness
// URL: https://codeforces.com/contest/862/problem/B
// Difficulty: medium
// Tags: 
// Strategy: 

void dfs(int x, vector<int> &color, vector<vector<int>> &graph) {
    for (int v : graph[x])
        if (color[v] == -1)
            color[v] = !color[x], dfs(v, color, graph);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;

    int u, v;
    vector<vector<int>> graph(n + 1);
    for (int r = 1; r <= n - 1; r++) 
        cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

    vector<int> color(n + 1, -1);

    color[1] = 0;
    dfs(1, color, graph);

    int zero = 0, one = 0;
    for (int r = 1; r <= n; r++)
        if (color[r])
            one++;
        else 
            zero++;

    cout << zero * one - (n - 1) << endl;
    return 0;
}