#include <bits/stdc++.h>
using namespace std;

#define int long long

// disjoint set union (union-find) class
class DSU {
    vector<int> parent, sz;
public:
    int numComp; // number of components

    DSU(int n) {
        parent.resize(n);
        sz.resize(n, 1);
        iota(parent.begin(), parent.end(), 0);
        numComp = n;
    }

    int root(int x) {
        if (parent[x] != x) parent[x] = root(parent[x]);
        return parent[x];
    }

    bool join(int a, int b) {
        a = root(a);
        b = root(b);
        if (a == b) return false;
        if (sz[a] > sz[b]) swap(a, b);
        parent[a] = b;
        sz[b] += sz[a];
        numComp--;
        return true;
    }
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<int,int>> pts(n);
    for (int i = 0; i < n; i++)
        cin >> pts[i].first >> pts[i].second;

    // sort by x ascending, then y ascending
    sort(pts.begin(), pts.end());

    map<int,int> ys; // key = y, value = particle index
    DSU dsu(n);

    for (int r = 0; r < n; r++) {
        auto &[x, y] = pts[r];

        // find largest key <= y
        auto itr = ys.upper_bound(y); // first key > y
        if (itr != ys.begin()) {
            --itr; // largest key <= y
            dsu.join(r, itr->second);
            // optionally erase itr if you want to replace the chain top
            ys.erase(itr);
        }

        // insert current particle as new top
        ys[y] = r;
    }

    cout << dsu.numComp << "\n";
}
