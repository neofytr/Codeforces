#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

#define int long long

// Problem: maxMinPath
// URL: https://codeforces.com/edu/course/2/lesson/6/3/practice/contest/285083/problem/D
// Difficulty: hard
// Tags:
// Strategy:

// there are n nodes and m edges between them, each edge having a weight
// each edge leads from a lower number node to a higher number one (i guess one way of saying there are no cycles in the graph?)
// all edges are directed

// we are to find all the paths from node 1 to node n that have atmost d edges
// on each of the paths, we take the maximum of all the edge weights on the path, and then
// find the minimum among these maximums

// since each edge leads from a lower number edge to a higher one, we can't revisit nodes
// so, there's no need for a visited array
// so, there are no cycles in the graph

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
    int u, v, w;
};

// It returns true if a path of at most 'd' edges exists with a max weight of 'max_w'.
// It also populates the 'path_output' vector if a path is found.
bool check(int max_w, int n, int d, const vector<Edge> &all_edges, vector<int> &path_output) {
    vector<vector<int>> graph(n + 1);
    for (const auto &edge : all_edges) {
        if (edge.w <= max_w) {
            graph[edge.u].push_back(edge.v);
        }
    }

    vector<int> dist(n + 1, -1);
    vector<int> parent(n + 1, 0);
    queue<int> q;

    q.push(1);
    dist[1] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (dist[u] >= d) {
            continue;
        }

        for (int v : graph[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    if (dist[n] != -1 && dist[n] <= d) {
        path_output.clear();
        int curr = n;
        while (curr != 0) {
            path_output.push_back(curr);
            curr = parent[curr];
        }
        reverse(path_output.begin(), path_output.end());
        return true;
    }

    return false;
}

void solve() {
    int n, m, d;
    cin >> n >> m >> d;

    vector<Edge> all_edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> all_edges[i].u >> all_edges[i].v >> all_edges[i].w;
    }

    int low = 0, high = 1e9 + 7;
    int ans_weight = -1;
    vector<int> best_path;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        vector<int> current_path;
        if (check(mid, n, d, all_edges, current_path)) {
            ans_weight = mid;
            best_path = current_path;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    if (ans_weight == -1) {
        cout << -1 << endl;
    } else {
        cout << best_path.size() - 1 << endl;
        for (size_t i = 0; i < best_path.size(); ++i) {
            cout << best_path[i] << (i == best_path.size() - 1 ? "" : " ");
        }
        cout << endl;
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}