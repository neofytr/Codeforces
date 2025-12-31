#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n, k;
    cin >> n >> k;

    int u, v;
    vector<vector<int>> graph(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

    vector<int> type(n + 1, 0);
    vector<int> dp(n + 1, 0);                        // dp[r] is the number of industrial cities in the tree rooted at r
    vector<vector<int>> depth(n + 1, vector<int>()); // depth[r] are the nodes at depth r

    int d = 1;
    queue<pair<int, int>> que;

    que.push({1, -1});
    while (!que.empty()) {
        int sz = que.size();
        while (sz--) {
            auto [x, p] = que.front();
            que.pop();
            depth[d].push_back(x);

            for (const int c : graph[x])
                if (c != x)
                    que.push({c, x});
        }
        d++;
    }
}