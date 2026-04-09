#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    long long w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
    }

    const long long INF = (1LL << 62);
    vector<long long> dist(n + 1, 0);
    vector<int> parent(n + 1, -1);

    int x = -1; // to store a vertex updated in the nth iteration

    // bellman–Ford with super source
    for (int i = 1; i <= n; ++i) {
        x = -1;
        for (const auto &e : edges) {
            if (dist[e.v] > dist[e.u] + e.w) {
                dist[e.v] = dist[e.u] + e.w;
                parent[e.v] = e.u;
                x = e.v;
            }
        }
    }

    if (x == -1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";

        // move n times to ensure we're inside the cycle
        for (int i = 0; i < n; ++i) {
            x = parent[x];
        }

        // reconstruct the cycle
        vector<int> cycle;
        int start = x;
        cycle.push_back(start);
        for (int v = parent[start]; v != start; v = parent[v]) {
            cycle.push_back(v);
        }
        cycle.push_back(start); // close the cycle

        reverse(cycle.begin(), cycle.end());

        for (int v : cycle) {
            cout << v << " ";
        }
        cout << "\n";
    }

    return 0;
}
