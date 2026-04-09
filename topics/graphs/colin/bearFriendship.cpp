#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

// assumes undirected graphs with 0-indexed nodes
class disjointSetUnion {
  public:
    int numNodes;
    int numComp;
    vector<int> parent;
    vector<int> size;
    vector<int> edges;

    inline bool checkNode(int x) { return x < numNodes && x >= 0; }
    inline bool checkNodes(int x, int y) { return checkNode(x) && checkNode(y); }
    int getRoot(int x) {
        int y = x;
        while (x != parent[x])
            x = parent[x];

        // path compression
        int temp;
        while (y != parent[y]) {
            temp = parent[y]; // store the parent of the current node
            parent[y] = x;    // make the root node parent of the current node
            y = temp;         // go to the stored parent node
        }
        return x;
    }
    inline int getSize(int x) { return size[getRoot(x)]; }

  public:
    disjointSetUnion(int numNodes) {
        this->numNodes = numNodes;
        parent.resize(numNodes);
        size.resize(numNodes);
        edges.resize(numNodes);
        for (int node = 0; node < numNodes; node++) {
            parent[node] = node;
            size[node] = 1; // each node is in it's own connected component
            edges[node] = 0;
        }
        numComp = numNodes;
        return;
    }

    bool join(int x, int y) { // joins node x and y via an edge if they are not already joined
        if (!checkNodes(x, y))
            return false;

        int rootX = getRoot(x);
        int rootY = getRoot(y);

        if (rootX == rootY) {
            edges[rootX]++;
            return false;
        } // already in the same component

        // x and y are not in the same component
        // they will be after these operations
        // so decrease the component number by 1
        numComp--;
        int sizeX = getSize(x);
        int sizeY = getSize(y);

        if (sizeX > sizeY) {
            swap(sizeX, sizeY);
            swap(rootX, rootY);
        }

        // from here, sizeY >= sizeX always
        // attach X root to Y root
        parent[rootX] = rootY;
        size[rootY] += sizeX;
        edges[rootY] += edges[rootX] + 1;
        return true;
    }

    int isConnected(int x, int y) {
        if (!checkNodes(x, y))
            return -1;

        return getRoot(x) == getRoot(y);
    }

    int componentSize(int x) { return checkNode(x) ? getSize(x) : -1; }
    int numComponents() { return numComp; }
};

int32_t main() {
    int n, m;
    cin >> n >> m;

    disjointSetUnion dsu(n);

    // no member pairs will appear more than once in the input
    int u, v;
    while (m--) {
        cin >> u >> v;
        u--, v--;
        dsu.join(u, v);
    }

    for (int node = 0; node < n; node++) {
        if (dsu.parent[node] == node) {
            int size = dsu.size[node];
            if (dsu.edges[node] != size * (size - 1) / 2) {
                cout << "NO\n";
                return EXIT_SUCCESS;
            }
        }
    }

    cout << "YES\n";
    return EXIT_SUCCESS;
}