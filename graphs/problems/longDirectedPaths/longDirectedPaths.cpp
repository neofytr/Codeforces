#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: longDirectedPaths
// URL: https://codeforces.com/contest/1144/problem/F
// Difficulty: hard
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;

    int u, v;
    vector<pair<int, int>> edges;
    vector<vector<int>> graph(n + 1);    

    while(m--)
        cin >> u >> v, edges.push_back({u, v}), graph[u].push_back(v), graph[v].push_back(u);

    // 0 for incoming and 1 for outgoing
    vector<int> dir(n + 1, -1);
    queue<int> que;

    for (int r = 1; r <= n; r++)
        if (dir[r] == -1) {
            dir[r] = 0;
            que.push(r);

            while(!que.empty()) {
                int x = que.front();
                que.pop();

                for (int v : graph[x])
                    if (dir[v] == -1)
                        dir[v] = !dir[x], que.push(v);
                    else if (dir[v] != !dir[x]) {
                        cout << "NO\n";
                        return 0;
                    }
            }
        }

    cout << "YES\n";
    for (auto &[u, v] : edges) {
        if (!dir[u])
            cout << 1;
        else 
            cout << 0;
    }
    cout << endl;
    return 0;
}