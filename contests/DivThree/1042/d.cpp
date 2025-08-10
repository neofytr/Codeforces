#include <bits/stdc++.h>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> graph(n);
    int u, v;
    for (int i = 1; i <= n - 1; i++) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}