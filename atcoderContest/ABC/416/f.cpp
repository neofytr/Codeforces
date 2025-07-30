#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

int dfs(int node, vector<int> &arr, vector<bool> &colored, vector<vector<int>> &graph) {
    
}
 
int32_t main() {
    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    int u, v;
    int edges = n - 1;
    vector<vector<int>> graph(n);
    while (edges--) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<bool> colored(n, false);
    int total = 0;
    for (int node = 0; node < n; node++) {
        if (!colored[node])
            total += dfs(node, arr, colored, graph);
    }
    cout << total << endl;
}