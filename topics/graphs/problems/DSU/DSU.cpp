#include <bits/stdc++.h>
#include <cstdlib>
#include <utility>
#include <vector>
using namespace std;

// we assume zero-indexed nodes and an undirected graph
class disjointSetUnion {
  private:
    long long n;
    long long numOfComponents;
    vector<long long> size;   // only really valid if you do size[rootNode], which gives the size of the component the rootNode belongs to
    vector<long long> parent; // parent[r] stores the parent of r in a node tree; parent[r] = r for root node r
    vector<long long> edge;   // edge[r] only really valid if r is a rootNode; stores the number of edges in the component rooted at r

    long long getRoot(long long x) {
        long long init = x;
        while (x != parent[x]) {
            x = parent[x];
        }

        // path compression
        long long temp;
        while (init != parent[init]) {
            temp = parent[init];
            parent[init] = x;
            init = temp;
        }

        return x;
    }

  public:
    disjointSetUnion(long long numOfNodes) {
        n = numOfNodes;
        numOfComponents = n;
        size.resize(n);
        parent.resize(n);
        edge.resize(n);

        for (long long node = 0; node < n; node++) {
            size[node] = 1;
            edge[node] = 0;
            parent[node] = node;
        }
        return;
    }

    bool createEdge(long long x, long long y) { // connect x and y via a direct edge
        if (x >= n || y >= n || x < 0 || y < 0) {
            return false;
        }

        long long rootX = getRoot(x);
        long long rootY = getRoot(y);
        long long sizeX = size[rootX];
        long long sizeY = size[rootY];

        if (rootX == rootY) {
            // already in the same component; but since a new edge is being added between x and y
            edge[rootX]++;
            return true;
        }

        if (sizeX <= sizeY) {
            swap(sizeX, sizeY);
            swap(rootX, rootY);
        }

        // join y to x
        parent[rootY] = rootX;
        size[rootX] += size[rootY];
        edge[rootX] += edge[rootY] + 1;

        numOfComponents--;
        return true;
    }

    long long getEdges(long long x) {
        if (x >= n || x < 0)
            return -1;

        return edge[getRoot(x)];
    } // get the number of edges in the component x is a part of

    long long isConnected(long long x, long long y) { // checks if x and y are in the same component
        if (x >= n || y >= n || x < 0 || y < 0) {
            return -1;
        }

        return getRoot(x) == getRoot(y);
    }

    long long getNumOfComponents(void) { return numOfComponents; }

    long long getComponentSize(long long x) { // returns the size of the component node x is part of
        if (x >= n || x < 0)
            return -1;

        return size[getRoot(x)];
    }
};