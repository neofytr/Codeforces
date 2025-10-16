#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: buglife
// URL: https://www.spoj.com/problems/BUGLIFE/
// Difficulty: medium
// Tags: 
// Strategy: 

bool solve() {
    int n, m;
    cin >> n >> m;
    int u, v;
    vector<vector<int>> graph(n + 1);
    while(m--) 
        cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);
    vector<int> gender(n + 1, -1);
    queue<int> que;

    for (int r = 1; r <= n; r++)
        if (gender[r] == -1) {
            gender[r] = 0;
            que.push(r);
            while(!que.empty()) {
                int x = que.front();
                que.pop();

                for (int v : graph[x])
                    if (gender[v] == -1)
                        gender[v] = !gender[x], que.push(v);
                    else if (gender[v] != !gender[x])
                        return false;
            }
        }
    return true;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    for (int r = 1; r <= t; r++) {
        cout << "Scenario #" << r << ":" << endl;
        if(!solve())
            cout << "Suspicious bugs found!";
        else 
            cout << "No suspicious bugs found!";
        cout << endl;
    }
        
    return 0;
}