#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: wormholeSort
// URL: https://usaco.org/index.php?page=viewproblem2
// Difficulty: hard
// Tags: 
// Strategy: 

class disjointSetUnion {
private:
    vector<int> parent;
    vector<int> size;
    int nodes;

    int root(int x) {
        int y = x;
        while(x != parent[x])
            x = parent[x];

        int tmp;
        while(y != parent[y])
            tmp = parent[y], parent[y] = x, y = tmp;
        return x;
    }
public:
    disjointSetUnion(int n) {
        nodes = n;
        parent.resize(n);
        size.resize(n);

        for (int r = 0; r < n; r++)
            parent[r] = r, size[r] = 1;
    }

    void unite(int x, int y) {
        int rootX = root(x), rootY = root(y);
        if (rootX == rootY)
            return;

        int sizeX = size[rootX];
        int sizeY = size[rootY];

        if (sizeX >= sizeY) {
            // attach y's root to x's root
            parent[rootY] = rootX;
            size[rootX] += sizeY;
        } else {
            parent[rootX] = rootY;
            size[rootY] += sizeX;
        }
    }

    bool connected(int x, int y) {
        return root(x) == root(y); 
    }
};

bool can(int sz, vector<int> &location, vector<pair<pair<int, int>, int>> &edges) {
    // can we sort the cows by taking only those edges which have weights >= sz?

    int k = location.size();
    disjointSetUnion dsu(k);

    for (auto &[v, w] : edges)
        if (w >= sz)
            dsu.unite(v.first, v.second);

    for (int i = 1; i <= k - 1; i++) {
        if (!dsu.connected(i, location[i]))
            return false;
    }
    return true;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("wormsort.in", "r", stdin);
    freopen("wormsort.out", "w", stdout);
    
    int n, m;
    cin >> n >> m;

    vector<pair<pair<int, int>, int>> edges;
    vector<int> location(n + 1); // cow to initial location
    for (int cow = 1; cow <= n; cow++)
        cin >> location[cow];

    int a, b, w;
    while(m--)
        cin >> a >> b >> w, edges.push_back({{a, b}, w});

    int left = 0;
    int right = 1e9 + 1;

    while(right != left + 1) {
        int mid = left + (right - left) / 2;
        if (can(mid, location, edges))
            left = mid;
        else 
            right = mid;
    }

    if (left == 1e9)
        cout << -1 << endl;
    else 
        cout << left << endl;
    return 0;
}