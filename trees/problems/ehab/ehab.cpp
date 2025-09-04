#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: ehab
// URL: https://codeforces.com/problemset/problem/1325/C
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    int u, v;
    cin >> n;

    vector<pair<int, int>> edges;    // store edges to preserve input order
    vector<vector<int>> tree(n + 1); // now stores EDGE INDICES, not neighbors

    for (int r = 0; r < n - 1; r++) {
        cin >> u >> v;
        edges.push_back({u, v});
        tree[u].push_back(r); // store edge index
        tree[v].push_back(r); // store edge index
    }

    // since there is always a path that connects the edge 0 and edge 1, the largest MEX will always be at least 2
    // now, if there is some node which has it's degree at least 3, we can assign 0, 1 and 2 on three of its adjacent edges
    // this ensures that the largest MEX through any path is exactly 2; we can then assign all the remaining nodes values arbitrarily

    // otherwise, if there are no nodes with degree at least 3, i.e, all the nodes have degree 2, then, since the graph is a tree
    //, the tree becomes a linear structure,
    // the largest MEX will then just be n - 2; and we assign any node any value arbitrarily

    vector<int> ans(n - 1, -1);

    // find node with degree >= 3
    int node = -1;
    for (int i = 1; i <= n; i++) {
        if (tree[i].size() >= 3) {
            node = i;
            break;
        }
    }

    int label = 0;
    if (node != -1) {
        // assign 0,1,2 to three edges incident to this node
        for (int j = 0; j < 3; j++) {
            ans[tree[node][j]] = label++;
        }
        // assign the rest arbitrarily
        for (int i = 0; i < n - 1; i++) {
            if (ans[i] == -1) {
                ans[i] = label++;
            }
        }
    } else {
        // it's a path → just assign 0..n-2
        for (int i = 0; i < n - 1; i++) {
            ans[i] = i;
        }
    }

    // print in input order
    for (int x : ans)
        cout << x << "\n";

    return 0;
}
