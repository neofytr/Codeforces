#include <bits/stdc++.h>
#include <vector>
using namespace std;

// Problem: largeIsland
// URL: https://leetcode.com/problems/making-a-large-island/description/
// Difficulty: hard
// Tags:
// Strategy:

class disjointSetUnion {
  public:
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

int n;
#define getIndex(row, col) (row * n + col)

class Solution {
  public:
    int largestIsland(vector<vector<int>> &grid) {
        int n = grid.size();
        ::n = n; // set global n for getIndex macro
        disjointSetUnion dsu(n * n);
        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if (grid[row][col] == 1) {
                    for (int i = 0; i < 4; ++i) {
                        int nrow = row + dr[i], ncol = col + dc[i];
                        if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < n && grid[nrow][ncol] == 1) {
                            dsu.join(getIndex(row, col), getIndex(nrow, ncol));
                        }
                    }
                }
            }
        }

        int maxIsland = 0;
        bool hasZero = false;
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if (!grid[row][col]) {
                    hasZero = true;
                    unordered_set<int> neighborRoots;
                    for (int i = 0; i < 4; ++i) {
                        int nrow = row + dr[i], ncol = col + dc[i];
                        if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < n && grid[nrow][ncol] == 1) {
                            neighborRoots.insert(dsu.getRoot(getIndex(nrow, ncol)));
                        }
                    }
                    int mergedSize = 1; // flip current 0 to 1
                    for (int root : neighborRoots) {
                        mergedSize += dsu.size[root];
                    }
                    maxIsland = max(maxIsland, mergedSize);
                }
            }
        }

        // if no zero was found, the whole grid is already one island
        if (!hasZero)
            return n * n;
        return maxIsland;
    }
};
