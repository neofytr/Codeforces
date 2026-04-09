#include <bits/stdc++.h>
using namespace std;

#define int long long
#define USACO
#define INPUT "closing.in"
#define OUTPUT "closing.out"


// Problem: closingTheFarm
// URL: https://usaco.org/index.php?page=viewproblem2
// Difficulty: medium
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifdef USACO
    freopen(INPUT, "r", stdin);
    freopen(OUTPUT, "w", stdout);
#endif

    int n, m;
    cin >> n >> m;

    int u, v;
    vector<vector<int>> graph(n + 1);
    while(m--) 
        cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

    vector<bool> isOn(n + 1, true);
    int nd;
    for (int r = 0; r < n; r++) {
        if (r) {
            cin >> nd;
            isOn[nd] = false;
        }
        vector<bool> vis(n + 1, false);
        int src = -1;
        for (int i = 1; i <= n; i++) {
            if (isOn[i]) {
                src = i;
                break;
            }
        }
        
        if (src != -1) {
            queue<int> que;
            que.push(src);
            vis[src] = true;
            while (!que.empty()) {
                int x = que.front(); que.pop();
                for (int v : graph[x]) {
                    if (isOn[v] && !vis[v]) {
                        vis[v] = true;
                        que.push(v);
                    }
                }
            }
        }
    
        bool allConn = true;
        for (int node = 1; node <= n; node++)
            if (isOn[node] && !vis[node]) {
                allConn = false;
                break;
            }
    
        if (allConn)
            cout << "YES\n";
        else 
            cout << "NO\n";
    }
    return 0;
}