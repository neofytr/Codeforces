#include <bits/stdc++.h>
#include <vector>
using namespace std;

// we assume zero-indexed nodes and an undirected graph
class disjointSetUnion {
  private:
    int n;
    vector<int> size;   // only really valid if you do size[rootNode], which gives the size of the component the rootNode belongs to
    vector<int> parent; // parent[r] stores the parent of r in a node tree; parent[r] = r for root node r
    vector<int> edge;   // edge[r] only really valid if r is a rootNode; stores the number of edges in the component rooted at r

    int getRoot(int x) {
        int init = x;
        while (x != parent[x]) {
            x = parent[x];
        }

        // path compression
        int temp;
        while (init != parent[init]) {
            temp = parent[init];
            parent[init] = x;
            init = temp;
        }

        return x;
    }

  public:
    void create(int numOfNodes) { // create an empty DS
        n = numOfNodes;
        size.resize(n);
        parent.resize(n);
        edge.resize(n);

        for (int node = 0; node < n; node++) {
            size[node] = 1;
            edge[node] = 0;
            parent[node] = node;
        }
        return;
    }

    bool unite(int x, int y) { // there is an edge between x and y
        if (x >= n || y >= n || x < 0 || y < 0) {
            return false;
        }

        int rootX = getRoot(x);
        int rootY = getRoot(y);
        int sizeX = size[rootX];
        int sizeY = size[rootY];

        if (sizeX > sizeY) {
            // join y to x
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
            edge[rootX] += edge[rootY] + 1;
        } else {
            // join x to y
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
            edge[rootY] += edge[rootX] + 1;
        }

        return true;
    }

    int getEdges(int x) {
        if (x >= n || x < 0)
            return -1;

        return edge[getRoot(x)];
    } // get the number of edges in the component x is a part of

    int isConnected(int x, int y) { // checks if x and y are in the same component
        if (x >= n || y >= n || x < 0 || y < 0) {
            return -1;
        }

        return getRoot(x) == getRoot(y);
    }

    int getComponentSize(int x) { // returns the size of the component node x is part of
        if (x >= n || x < 0)
            return -1;

        return size[getRoot(x)];
    }
};