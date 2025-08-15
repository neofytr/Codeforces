#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
using namespace std;

#define int long long

int32_t main() {
    int n, m;
    cin >> n >> m;
    vector<int> coins(n + 1);
    for (int node = 1; node <= n; node++)
        cin >> coins[node];

    int u, v;
    vector<vector<int>> graph(n + 1);
    while (m--) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<bool> vis(n + 1, false);
    int totalCost = 0;

    for (int node = 1; node <= n; node++) {
        if (!vis[node]) {
            int src = node;
            int minCost = coins[src];

            queue<int> que;
            vis[src] = true;
            que.push(src);
            while (!que.empty()) {
                int x = que.front();
                que.pop();

                for (int v : graph[x]) {
                    if (!vis[v]) {
                        vis[v] = true;
                        minCost = min(minCost, coins[v]);
                        que.push(v);
                    }
                }
            }

            totalCost += minCost;
        }
    }

    cout << totalCost << endl;
    return EXIT_SUCCESS;
}