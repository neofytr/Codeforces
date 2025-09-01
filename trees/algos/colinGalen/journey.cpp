#include <bits/stdc++.h>
using namespace std;

#define int long long

double expec(const int node, const int parent, const vector<vector<int>> &tree) {
    double ex = 0.0;
    int children = 0;

    for (const int v : tree[node]) {
        if (v != parent) {
            ex += expec(v, node, tree);
            children++;
        }
    }

    // if leaf, no more steps
    if (!children)
        return 0.0;

    // expected steps = 1 (this step) + avg of children
    return 1.0 + ex / children;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // there are n cities and n - 1 roads, each connecting two cities
    // we can reach any city from any other city through the roads

    // so we have a graph of n vertices and n - 1 edges that is connected
    // so, its a tree
    int n;
    cin >> n;

    int u, v;
    vector<vector<int>> tree(n + 1);
    for (int r = 1; r <= n - 1; r++) {
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u); // add both directions since we don't know if u is the parent of v or vice versa through the given order
    }

    int root = 1;
    // the journey starts at the root node
    // at each node, they go to a node that is not previously visited, until they can't do this anymore
    // the length of the journey is the number of edges they pass through
    // since the graph is a tree, and they only visit not previously visited nodes at each step, any journey
    // is just a simple path from the root node to a leaf node in the tree
    // the number of possible journeys is the number of leaf nodes since there is exactly one simple path to each leaf
    // from the root

    cout << setprecision(24) << expec(root, -1, tree) << endl;
    return EXIT_SUCCESS;
}