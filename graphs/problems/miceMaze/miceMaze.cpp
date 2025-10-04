#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: miceMaze
// URL: https://www.spoj.com/problems/MICEMAZE/
// Difficulty: hard
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, e, t;
    cin >> n >> e >> t;

    vector<vector<pair<int, int>>> graph(n + 1);

    int m;
    cin >> m;
    int a, b, w;
    while(m--) {
        cin >> a >> b >> w;
        graph[b].push_back({a, w}); // reverse the graph
    }    

    vector<int> dist(n + 1, LLONG_MAX);
    queue<int> que;

    dist[e] = 0;
    que.push(e);
    while(!que.empty()) {
        int x = que.front();
        que.pop();

        for (auto &[v, w] : graph[x])
            if (dist[v] > dist[x] + w)
                dist[v] = dist[x] + w, que.push(v);
    }

    int cnt = 0;
    for (int node = 1; node <= n; node++)
        if (dist[node] <= t)
            cnt++;
    cout << cnt << endl;
    return 0;
}