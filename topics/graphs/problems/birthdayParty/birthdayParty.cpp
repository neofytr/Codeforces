#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: birthdayParty
// URL: https://open.kattis.com/problems/birthday
// Difficulty: medium
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int p, c;
    while(cin >> p >> c, p) {
        int a, b;
        vector<vector<int>> graph(p);
        vector<pair<int, int>> edges(c);
        bool done = false;
        while(c--)
            cin >> a >> b, edges.push_back({a, b}), graph[a].push_back(b), graph[b].push_back(a);

        queue<int> que;
        for (auto &[m, n] : edges) {
            int src = m;
            vector<bool> vis(p, false);
            vis[src] = true;
            que.push(src);
            while(!que.empty()) {
                int x = que.front();
                que.pop();

                for (int v : graph[x])
                    if (x == m && v == n)
                        continue;
                    else if (!vis[v])
                        vis[v] = true, que.push(v);
            }

            if (!vis[n]) {
                cout << "Yes\n";
                done = true;
                break;
            }
        }
        if (!done)
            cout << "No\n";
    }    
    return 0;
}