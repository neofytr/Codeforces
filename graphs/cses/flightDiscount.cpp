#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <vector>
using namespace std;

#define int long long
#define MAXN (int)(1e5 + 1)
#define NUMSTATES (2)

int32_t main() {
    int n, m;
    cin >> n >> m;

    int u, v, w;
    vector<pair<int, int>> graph[MAXN];
    while (m--) {
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }

    int src, dst;
    set<tuple<int, int, int>> heap; // (dist, node, used coupon along the way or not)
    int dist[MAXN][NUMSTATES];      // dist[r][0] is the min distance to reach r from src not having used coupon along the way
                                    // dist[r][1] is the min distance to reach r from src having used the coupon somewhere along the way

    src = 1;
    dst = n;
    for (int node = src; node <= dst; node++) {
        dist[node][0] = dist[node][1] = LLONG_MAX;
    }
    dist[src][0] = dist[src][1] = 0;
    heap.insert({dist[src][0], src, 0});
    while (!heap.empty()) {
        auto [d, x, used] = *heap.begin();
        heap.erase(heap.begin());

        for (auto &[v, w] : graph[x]) {
            // either if we have used the coupon along the way or not, we will
            // add a case when we don't use coupon for this edge
            if (d + w < dist[v][used]) {
                heap.erase({dist[v][used], v, used});
                dist[v][used] = d + w;
                heap.insert({dist[v][used], v, used});
            }

            // if we have not used the coupon until now, we can use
            if (!used && (d + w / 2) < dist[v][1]) {
                heap.erase({dist[v][1], v, 1});
                dist[v][1] = d + w / 2;
                heap.insert({dist[v][1], v, 1});
            }
        }
    }

    cout << dist[dst][1] << endl;
    return EXIT_SUCCESS;
}