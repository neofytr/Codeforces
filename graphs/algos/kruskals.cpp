#include <bits/stdc++.h>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;

// assumes undirected graphs with 0-indexed nodes
class disjointSetUnion {
  private:
    int numNodes;
    int numComp;
    vector<int> parent;
    vector<int> size;

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
        for (int node = 0; node < numNodes; node++) {
            parent[node] = node;
            size[node] = 1; // each node is in it's own connected component
        }
        numComp = numNodes;
        return;
    }

    bool join(int x, int y) { // joins node x and y via an edge if they are not already joined
        if (!checkNodes(x, y))
            return false;

        int rootX = getRoot(x);
        int rootY = getRoot(y);

        if (rootX == rootY) // already in the same component
            return true;

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

typedef tuple<int, int, int> edge; // wt, u, v
int main() {
    // undirected, weighted graph with 0-indexed nodes
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> mst;
    disjointSetUnion dsu(n);
    priority_queue<edge, vector<edge>, greater<>> heap;
    int u, v, w;
    while (m--) {
        cin >> u >> v >> w;
        heap.push({w, u, v});
    }

    int sum = 0;
    while (!heap.empty()) {
        auto [w, u, v] = heap.top();
        heap.pop();

        if (dsu.isConnected(u, v))
            continue;

        dsu.join(u, v);
        mst.push_back({u, v});
        sum += w;

        if (mst.size() == n - 1)
            break;
    }

    if (mst.size() != n - 1) {
        cout << "Graph is not connected! No MST possible!\n";
        return EXIT_FAILURE;
    }

    cout << "MST total weight -> " << sum << endl;
    cout << "MST edges -> \n";
    for (auto &[u, v] : mst) {
        cout << u << " " << v << endl;
    }
    return EXIT_SUCCESS;
}