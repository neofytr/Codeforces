#include <bits/stdc++.h>
#include <vector>
using namespace std;

void dfs(int node, vector<int> &path, vector<bool> &vis, vector<vector<int>> &graph) {
    vis[node] = true;
    path.push_back(node);

    for (int v : graph[node]) {
        if (!vis[v]) {
            
        }
    }

    path.pop_back();
}

void solve() {
    int n;
    vector<int> A(n);
    vector<int> B(n);
    vector<vector<int>> graph(n, vector<int>());

    for (int index = 0; index < n; index++) {
        cin >> A[index] >> B[index];
        graph[A[index]].push_back(B[index]);
        graph[B[index]].push_back(A[index]);
    }

    // find the smallest cycle in the graph
    vector<bool> vis(n, false);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}