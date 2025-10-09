#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: roundDance
// URL: https://codeforces.com/contest/1833/problem/E
// Difficulty: hard
// Tags: 
// Strategy: 

void solve() {
    int n;
    cin >> n;

    int v;
    vector<vector<int>> graph(n + 1);
    map<pair<int, int>, bool> mp;
    for (int r = 1; r <= n; r++) {
        cin >> v;
        if (mp[{v, r}] || mp[{r, v}])
            continue;
        graph[r].push_back(v), graph[v].push_back(r);
        mp[{r, v}] = true;
    }

    queue<int> que;
    vector<bool> vis(n + 1, false);

    int linearCount = 0;
    int cycleCount = 0;

    for (int node = 1; node <= n; node++)
        if (!vis[node]) {
            int src = node;
            vis[src] = true;

            bool cycle = true;
            que.push(src);
            while(!que.empty()) {
                int x = que.front();
                que.pop();

                if (graph[x].size() != 2)
                    cycle = false;

                for (int v : graph[x])
                    if (!vis[v])
                        vis[v] = true, que.push(v);
            }

            if (!cycle)
                linearCount++;
            else 
                cycleCount++;
        }

    int mini = cycleCount + (linearCount ? 1 : 0);
    int maxi = cycleCount + linearCount;
    cout << mini << " " << maxi << endl; 
    cycleCount = 0;
    linearCount = 0;
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