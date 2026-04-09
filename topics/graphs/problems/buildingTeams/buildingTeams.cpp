#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: buildingTeams
// URL: https://cses.fi/problemset/task/1668
// Difficulty: easy
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;

    int u, v;
    vector<vector<int>> graph(n + 1);    
    while(m--) 
        cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

    queue<pair<int, int>> que;
    vector<int> color(n + 1, -1);
    for (int node = 1; node <= n; node++)
        if (color[node] == -1) {
            int src = node;
            color[src] = 1;
            que.push({src, -1});
            while(!que.empty()) {
                auto [x, p] = que.front();
                que.pop();

                for (int v : graph[x])
                    if (color[v] == -1)
                        color[v] = ((color[x] == 1) ? 2 : 1), que.push({v, x});
                    else if (v != p) {
                        cout << "IMPOSSIBLE\n";
                        return 0;
                    }
            }
        }
    for (int node = 1; node <= n; node++)
        cout << color[node] << " ";
    cout << "\n";
    return 0;
}