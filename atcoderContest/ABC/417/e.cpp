#include <bits/stdc++.h>
#include <vector>
using namespace std;

void dfs(int node, int dest, vector<bool> &vis, vector<int> &path, vector<set<int>> &graph) {
    vis[node] = true;
    path.push_back(node);

    if (node == dest) {
        for (int v : path) {
            cout << ++v << " ";
        }
        cout << endl;
        return;
    }

    for (int v : graph[node]) {
        if (!vis[v]) {
            dfs(v, dest, vis, path, graph);
        }
    }

    path.pop_back();
    return;
}

void solve() {
    int n, m, src, dest;
    cin >> n >> m >> src >> dest;
    src--, dest--;

    vector<set<int>> graph(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].insert(v);
        graph[v].insert(u);
    }

    vector<bool> vis(n, false);
    vector<int> path;
    dfs(src, dest, vis, path, graph);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}