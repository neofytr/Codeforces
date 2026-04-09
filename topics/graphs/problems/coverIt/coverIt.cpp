#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: coverIt
// URL: https://codeforces.com/problemset/problem/1176/E
// Difficulty: hard
// Tags: 
// Strategy: 

void dfs(int x, vector<int> &color, vector<vector<int>> &graph) {
    for (int v : graph[x])
        if (color[v] == -1) {
            color[v] = !color[x];
            dfs(v, color, graph);
        }
}

void solve() {
    int n, m;
    cin >> n >> m;

    int u, v;
    vector<vector<int>> graph(n + 1);
    while(m--) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> color(n + 1, -1);

    color[1] = 0;
    dfs(1, color, graph);
    vector<int> one, zero;

    for (int r = 1; r <= n; r++)
        if (color[r])
            one.push_back(r);
        else 
            zero.push_back(r);

    if (one.size() <= n / 2) {
        cout << one.size() << endl;
        for (int c : one)
            cout << c << " ";
    }
    else  {
        cout << zero.size() << endl;
        for (int c : zero)
            cout << c << " ";
    }
    cout << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;

    while(t--) {
        solve();
    }    
    return 0;
}