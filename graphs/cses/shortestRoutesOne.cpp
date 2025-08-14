#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <vector>
using namespace std;

#define int long long

int32_t main() {
    int n, m;
    cin >> n >> m;

    int u, v, w;
    vector<vector<pair<int, int>>> graph(n + 1);
    while (m--) {
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }

    vector<int> dist(n + 1, LLONG_MAX);
    set<pair<int, int>> que; // dist, node

    int src = 1;
    dist[src] = 0;
    que.insert({dist[src], src});
    while (!que.empty()) {
        auto [d, x] = *que.begin();
        que.erase(que.begin());

        for (auto &[v, w] : graph[x]) {
            if (dist[v] > d + w) {
                que.erase({dist[v], v});
                dist[v] = d + w;
                que.insert({dist[v], v});
            }
        }
    }

    for (int node = 1; node <= n; node++)
        cout << dist[node] << " ";
    cout << endl;
    return EXIT_SUCCESS;
}