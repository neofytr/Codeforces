#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: fencePlanning
// URL: https://usaco.org/index.php?page=viewproblem2
// Difficulty: medium
// Tags: 
// Strategy: 


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("fenceplan.in", "r", stdin);
    freopen("fenceplan.out", "w", stdout);
    
    int n, m;  
    cin >> n >> m;

    vector<pair<int, int>> cows(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> cows[r].first >> cows[r].second;  

    int u, v;
    vector<vector<int>> graph(n + 1);
    while(m--)
        cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

    vector<int> vis(n + 1, false);
    queue<int> que;

    int peri = LLONG_MAX;
    for (int node = 1; node <= n; node++)
        if (!vis[node]) {
            int maxX = LLONG_MIN;
            int maxY = LLONG_MIN;
            int minX = LLONG_MAX; 
            int minY = LLONG_MAX;

            int src = node;
            vis[src] = true;
            que.push(src);
            while(!que.empty()) {
                int x = que.front();
                que.pop();

                maxX = max(cows[x].first, maxX);
                minX = min(cows[x].first, minX);
                maxY = max(cows[x].second, maxY);
                minY = min(cows[x].second, minY);

                for (int v : graph[x])
                    if (!vis[v])
                        vis[v] = true, que.push(v);
            }

            peri = min(peri, 2 * (maxX - minX + maxY - minY));
        }
    cout << peri << endl;
    return 0;
}