# largeIsland

```markdown
# Largest Island Problem Documentation

This document describes the solution to the "Making A Large Island" problem, found on LeetCode ([https://leetcode.com/problems/making-a-large-island/description/](https://leetcode.com/problems/making-a-large-island/description/)).

## 1. Problem Description

Given an `n x n` binary grid, where `0` represents water and `1` represents land, you are allowed to change one `0` to a `1`.  Find the largest island you could possibly create. An island is a group of `1`s connected 4-directionally (horizontal or vertical).  If there are no `0`s, then you can convert the entire grid to land which will also form a single island.

## 2. Approach Explanation

The solution uses the Disjoint Set Union (DSU) data structure (also known as Union-Find) to efficiently determine the size of connected components (islands) of `1`s in the grid. The algorithm proceeds in two main phases:

1.  **Island Identification and Union:**
    *   Iterate through the grid.
    *   If a cell is `1` (land), consider its four neighbors.
    *   If a neighbor is also `1` (land), use the DSU `join` operation to merge the two land cells into the same connected component.  A DSU object `dsu` represents the relationship of each cell in the grid with its island.

2.  **Maximize Island Size by Flipping a `0`:**
    *   Iterate through the grid again.
    *   If a cell is `0` (water), consider its four neighbors.
    *   If a neighbor is `1` (land), find the root of that neighbor's connected component using DSU `getRoot`.
    *   Keep track of the unique connected components (islands) that are adjacent to the water cell.
    *   Calculate the size of the potential island formed by flipping the water cell to land. This is the sum of the sizes of the adjacent connected components plus 1 (for the flipped cell).
    *   Update the `maxIsland` variable with the maximum size found so far.

Finally, handle the case where there are no `0`s in the grid. In this case, the entire grid is already one island, and its size is `n * n`.

## 3. Key Insights and Algorithmic Techniques

*   **Disjoint Set Union (DSU):**  DSU is crucial for efficiently tracking connected components in a graph (in this case, the grid).  The `join` operation merges two components, and the `getRoot` operation finds the representative node (root) of a component.  Path compression during `getRoot` significantly improves performance.
*   **Grid as a Graph:** Representing the grid as a graph where adjacent land cells are connected.  This allows DSU to be effectively applied.
*   **Space Optimization with Hashing:** Using `unordered_set` to store the roots of neighboring components for `0` cells avoids counting the same island multiple times when calculating the merged size.
*   **Global Variable for Indexing:** The `getIndex` macro efficiently maps 2D grid coordinates (row, col) to a 1D index used by the DSU, reducing code duplication.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   DSU initialization: O(N), where N is the total number of cells in the grid (`n * n`).
    *   First grid traversal (union operations):  O(N \* α(N)), where α(N) is the inverse Ackermann function, which grows extremely slowly and is practically constant. This is because the `join` and `getRoot` operations in DSU take near-constant time on average due to path compression.
    *   Second grid traversal (finding max island): O(N) in the worst-case scenario when finding a merged island.
    *   Overall time complexity:  O(N \* α(N)) which can be effectively considered O(N).

*   **Space Complexity:**
    *   DSU: O(N) for storing `parent` and `size` arrays.
    *   Grid: O(N) space for the `grid` vector.
    *   The `neighborRoots` set can grow at most O(4) = O(1) in size because there are only four possible neighbors.
    *   Overall space complexity: O(N)

## 5. Important Code Patterns or Tricks Used

*   **`getIndex` Macro:**  A simple macro to convert row and column indices to a single index, simplifying the DSU operations. It is also critical for using a 1D DSU to represent a 2D grid.
*   **Path Compression in DSU:**  The `getRoot` function uses path compression to flatten the tree structure of the DSU, significantly improving the performance of subsequent `getRoot` and `join` operations.
*   **Weighted Union:** The `join` function attaches the smaller tree to the larger tree, which helps to keep the tree structure flatter, further optimizing the DSU performance.
*   **Neighbor Iteration:** The `dr` and `dc` arrays provide a concise and efficient way to iterate over the four neighbors of a cell.
*   **`hasZero` Flag:** The `hasZero` flag avoids unnecessary calculation and correctly handles the corner case where there are no `0` cells in the grid.
*   **Using `unordered_set` to track neighbor roots:** This ensures each connected component neighboring a 0 cell is only counted once.

## 6. Edge Cases Handled

*   **Empty Grid (Implicitly):** The code handles empty or invalid grids implicitly by returning 0 if `grid.size()` is zero.
*   **Grid with Only 1s:** The code explicitly handles the case where there are no `0`s in the grid by returning `n * n` (the size of the entire grid).
*   **Out-of-Bounds Access:** The code checks for out-of-bounds neighbor indices (`nrow >= 0 && nrow < n && ncol >= 0 && ncol < n`) before accessing the grid.
*   **Isolated Islands:** The DSU correctly handles cases where there are isolated islands of `1`s.
*   **All Zeros:** The algorithm functions correctly if the entire grid contains only '0's and finds largest island size of 1.
```

## Original Code
```cpp
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

```

---
*Documentation generated on 2025-08-05 20:45:45*
