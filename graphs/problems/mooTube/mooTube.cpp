#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: mooTube
// URL: https://usaco.org/index.php?page=viewproblem2&cpid=788
// Difficulty: hard
// Tags: 
// Strategy: 

int32_t main() {
    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);
    
    int n, queries;
    cin >> n >> queries;

    int p, q, r;
    vector<vector<pair<int, int>>> graph(n + 1);  
    for (int i = 1; i <= n - 1; i++)
        cin >> p >> q >> r, graph[p].push_back({q, r}), graph[q].push_back({p, r});

    int k, src;
    queue<pair<int, int>> que;
    while(queries--) {
        cin >> k >> src;

        vector<bool> vis(n + 1, false);

        int cnt = 0;
        que.push({src, LLONG_MAX});
        vis[src] = true;
        while(!que.empty()) {
            auto [x, d] = que.front();
            que.pop();

            if (x != src && d >= k)
                cnt++;

            for (auto &[v, w] : graph[x]) 
                if (!vis[v] && w >= k)
                    vis[v] = true, que.push({v, min(d, w)});
        }
        cout << cnt << endl;
    }  
    return 0;
}