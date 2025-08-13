#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

// undirected graph
// 0-indexed nodes
class disjointSetUnion {
  public:
    int nodes;
    int comp;
    vector<int> parent;
    vector<int> size;

    disjointSetUnion(int n) {
        nodes = n;
        parent.resize(n);
        size.resize(n);
        for (int node = 0; node < nodes; node++) {
            parent[node] = node;
            size[node] = 1;
        }
        comp = n;
        return;
    }

    int getRoot(int x) {
        int y = x;
        while (x != parent[x])
            x = parent[x];

        int tmp;
        while (y != parent[y]) {
            tmp = parent[y];
            parent[y] = x;
            y = tmp;
        }

        return x;
    }

    void join(int x, int y) {
        if (getRoot(x) == getRoot(y))
            return;

        comp--;
        if (size[y] > size[x])
            swap(x, y);

        // size[x] >= size[y]
        int rootX = getRoot(x);
        int rootY = getRoot(y);
        parent[rootY] = rootX;
        size[rootX] += size[rootY];
        return;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    disjointSetUnion dsu(n);
    int a, b;
    while (m--) {
        cin >> a >> b;
        a--, b--;
        dsu.join(a, b);
    }

    cout << dsu.comp - 1 << endl;
    vector<int> req;
    for (int i = 0; i < n; i++) {
        if (dsu.parent[i] == i)
            req.push_back(i);
    }

    for (int i = 0; i < req.size() - 1; i++) {
        cout << req[i] + 1 << " " << req[i + 1] + 1 << endl;
    }
    return EXIT_SUCCESS;
}