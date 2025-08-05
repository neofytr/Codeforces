#include <bits/stdc++.h>
using namespace std;

// Problem: networkConnected
// URL: https://leetcode.com/problems/number-of-operations-to-make-network-connected/description/
// Difficulty: medium
// Tags:
// Strategy:

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

class Solution {
  public:
    int makeConnected(int n, vector<vector<int>> &connections) {
        int ans = 0;
        int leftConnections = 0;

        disjointSetUnion dsu(n);
        for (auto &vec : connections) {
            int a = vec[0];
            int b = vec[1];

            if (dsu.isConnected(a, b)) {
                // if they are already connected, there's no need to have a cable between them
                leftConnections++;
            } else {
                // if they are not already connected, insert a cable between them
                dsu.join(a, b);
            }
        }

        int compSize = dsu.numComponents();
        if (compSize > 1) {
            // this means there are some connected components that aren't connected to each other
            // we need exactly (compSize - 1) edges to connect these together
            // if we have these many, we connect
            // else we don't
            if (leftConnections >= compSize - 1)
                ans = compSize - 1;
            else
                ans = -1;
        }

        return ans;
    }
};