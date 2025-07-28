#include <bits/stdc++.h>
using namespace std;

int dfs(int node, int parent, int m, int currConsCat, const vector<int> &cat, const vector<vector<int>> &graph) {
    if (cat[node])
        currConsCat++;
    else
        currConsCat = 0;

    if (currConsCat > m)
        return 0;

    bool isLeaf = true;
    int total = 0;

    for (int v : graph[node]) {
        if (v == parent)
            continue;
        isLeaf = false;
        total += dfs(v, node, m, currConsCat, cat, graph);
    }

    if (isLeaf)
        return 1;

    return total;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> cat(n);
    for (int &val : cat)
        cin >> val;

    vector<vector<int>> graph(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    cout << dfs(0, -1, m, 0, cat, graph) << '\n';
    return 0;
}
