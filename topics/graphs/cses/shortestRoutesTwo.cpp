#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <vector>
using namespace std;

#define int long long

int32_t main() {
    int n, m, q;
    cin >> n >> m >> q;

    int u, v, w;
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, LLONG_MAX));
    while (m--) {
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[u][v], w); // there may be multiple roads between cities, choose the least distance one
    }

    for (int node = 1; node <= n; node++)
        dist[node][node] = 0;

    for (int via = 1; via <= n; via++) {
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {
                int uvia = dist[u][via];
                int viav = dist[via][v];
                int uv = dist[u][v];

                if (uvia != LLONG_MAX && viav != LLONG_MAX && uv > uvia + viav) {
                    dist[u][v] = uvia + viav;
                }
            }
        }
    }

    while (q--) {
        cin >> u >> v;
        if (dist[u][v] == LLONG_MAX)
            cout << -1 << endl;
        else
            cout << dist[u][v] << endl;
    }
    return EXIT_SUCCESS;
}