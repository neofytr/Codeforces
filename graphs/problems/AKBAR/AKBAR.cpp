#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: AKBAR
// URL: https://www.spoj.com/problems/AKBAR/
// Difficulty: medium
// Tags: 
// Strategy: 

void solve() {
    int n, r, m;
        cin >> n >> r >> m;

        int u, v;
        vector<vector<int>> graph(n + 1);
        while(r--)
            cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

        vector<int> vis(n + 1, -1);
        queue<int> que;
        while(m--) {
            int k, maxS;
            cin >> k >> maxS;

            int currS = 0;
            int src = k;
            if (vis[src] != -1) {
                cout << "No\n";
                return;
            }
            vis[src] = k;
            que.push(src);

            while(!que.empty()) {
                if (currS >= maxS)
                    break;
                int sz = que.size();
                while(sz--) {
                    int x = que.front();
                    que.pop();

                    for (int v : graph[x])
                        if (vis[v] == -1)
                            vis[v] = k, que.push(v);
                        else if (vis[v] != k) {
                            cout << "No\n";
                            return;
                        }
                }
                currS++;
            }

            while(!que.empty())
                que.pop();
        }

    for (int node = 1; node <= n; node++)
        if (vis[node] == -1) {
            cout << "No\n";
            return;
        }
    cout << "Yes\n";
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