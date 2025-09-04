#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: mocha
// URL: https://codeforces.com/problemset/problem/1559/D1
// Difficulty: hard
// Tags:
// Strategy:

class disjointSetUnion {
  public:
    vector<int> parent;
    vector<int> size;

    disjointSetUnion(int n) {
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int r = 1; r <= n; r++)
            parent[r] = r, size[r] = 1;
    }

    int getRoot(int x) {
        int y = x;
        while (x != parent[x])
            x = parent[x];

        int tmp;
        while (y != parent[y])
            tmp = parent[y], parent[y] = x, y = tmp;
        return x;
    }

    bool isConnected(const int x, const int y) { return getRoot(x) == getRoot(y); }

    void unite(const int x, const int y) {
        int rootX = getRoot(x);
        int rootY = getRoot(y);
        if (rootX == rootY)
            return;

        int sizeX = size[rootX];
        int sizeY = size[rootY];

        if (sizeY > sizeX) {
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        } else {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m1, m2;
    cin >> n >> m1 >> m2;

    int u, v;
    disjointSetUnion mocha(n), diana(n);
    while (m1--)
        cin >> u >> v, mocha.unite(u, v);
    while (m2--)
        cin >> u >> v, diana.unite(u, v);

    // a forest is an undirected graph without cycles (not necessarily connected)
    // mocha and diana are friends
    // both of them have forests with nodes numbered 1 to n
    // they would like to add edges to their forests such that:

    // 1. after adding edges, both their graphs are still forests
    // 2. they add the same edges

    // they want to know the maximum number of edges they can add, and which edges to add

    int cnt = 0;
    vector<pair<int, int>> ans;
    for (int u = 1; u <= n; u++)
        for (int v = u + 1; v <= n; v++)
            if (!mocha.isConnected(u, v) && !diana.isConnected(u, v))
                cnt++, ans.push_back({u, v}), mocha.unite(u, v), diana.unite(u, v);

    cout << cnt << endl;
    for (auto &[u, v] : ans)
        cout << u << " " << v << endl;

    return 0;
}