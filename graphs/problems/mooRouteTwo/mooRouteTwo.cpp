#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;

    int u, dept, v, arri;
    vector<int> layover(n + 1);
    for (int r = 1; r <= n; r++) layover[r] = 0;

    // adjacency list: adj[u] = list of (v, dept, arr)
    vector<vector<tuple<int,int,int>>> adj(n + 1);

    while(m--) {
        cin >> u >> dept >> v >> arri;
        adj[u].push_back({v, dept, arri});
    }

    for (int r = 1; r <= n; r++) cin >> layover[r];

    vector<int> arrivalTime(n + 1, LLONG_MAX);
    int src = 1;
    arrivalTime[src] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, src});

    while(!pq.empty()) {
        auto [time, u] = pq.top(); pq.pop();
        if (time > arrivalTime[u]) continue;

        for (auto &[v, dep, arr] : adj[u]) {
            if (u == src || dep >= arrivalTime[u] + layover[u]) {
                if (arr < arrivalTime[v]) {
                    arrivalTime[v] = arr;
                    pq.push({arr, v});
                }
            }
        }
    }

    for (int r = 1; r <= n; r++) {
        if (arrivalTime[r] == LLONG_MAX) cout << -1 << endl;
        else cout << arrivalTime[r] << endl;
    }

    return 0;
}
