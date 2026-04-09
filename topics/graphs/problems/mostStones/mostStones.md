# mostStones

```markdown
## Documentation for Most Stones Removed with Same Row or Column

This document provides a comprehensive analysis of the provided C++ code, which solves the "Most Stones Removed with Same Row or Column" problem on LeetCode ([https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/description/](https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/description/)).

### 1. Problem Description

The problem asks to find the maximum number of stones that can be removed from a given set of stones in a 2D plane, with the constraint that a stone can be removed only if it shares the same row or column with another stone that hasn't been removed yet.

Formally, you are given a list of `stones` where each `stone = [x, y]` represents a stone's location. A stone can be removed if and only if it shares the same row or column with another stone present in the stone list. The goal is to return the largest possible number of stones that can be removed.

### 2. Approach Explanation

The core idea behind the solution is to model the stones and their connections as a graph and use the Disjoint Set Union (DSU) data structure to find connected components.

Each row and column is treated as a node in a graph.  A stone at `(x, y)` is represented by a connection between the row `y` and column `x`.  Therefore, the coordinates of a stone represents an edge between a row and a column.

Stones that are in the same connected component can be reduced down to a single stone.

The algorithm proceeds as follows:

1. **Represent Rows and Columns as Nodes:** Assign a unique identifier to each row and column. The code uses an offset (`OFFSET = 10001`) to distinguish row indices from column indices. Specifically, row indices are in the range [0, ROWS-1] and column indices are mapped to [OFFSET, OFFSET + COLS -1].
2. **Build the Graph using DSU:** Iterate through the given stones. For each stone `(x, y)`, perform a `join` operation using the Disjoint Set Union (DSU) data structure to connect the row `y` and the column `x + OFFSET`. This step essentially builds the graph where the existence of a stone between a row and column is represented as an edge.
3. **Find Connected Components:** After processing all stones, the DSU structure represents the connected components in the graph. Find the root of each stone's (row or column) and store it in a set. The size of the set is the number of components.
4. **Calculate Removable Stones:** The maximum number of removable stones is equal to the total number of stones minus the number of connected components in the graph.  This is because within each connected component, all stones can be removed except for one (the "representative" of the component).

### 3. Key Insights and Algorithmic Techniques Used

*   **Disjoint Set Union (DSU):**  The DSU data structure is crucial for efficiently finding connected components in a graph. It allows for quick `union` (merging) and `find` (root finding) operations.  Path compression and union by size are implemented to optimize the DSU's performance.
*   **Graph Representation:** The problem cleverly represents the relationships between stones as a graph, where rows and columns are nodes, and stones are edges. This transformation allows us to use graph algorithms (in this case, connectivity analysis).
*   **Component Counting:** The number of connected components is found by extracting the unique roots, where each root represents a connected component.
*   **Offsetting:**  The `OFFSET` value is used to avoid index collisions between row and column indices, ensuring that they are treated as distinct nodes in the DSU.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   DSU Initialization: O(ROWS + COLS).
    *   Building the Graph (DSU `join` operations): O(N * α(ROWS + COLS)), where N is the number of stones and α is the inverse Ackermann function, which grows extremely slowly and can be considered almost constant.
    *   Finding Connected Components: O(K * α(ROWS + COLS)), where K is the number of unique rows and columns used in the stones array.
    *   Overall Time Complexity: O(ROWS + COLS + N * α(ROWS + COLS)). Because  α(ROWS + COLS) is nearly constant, we can write it as O(ROWS + COLS + N), where N is the number of stones.

*   **Space Complexity:**
    *   DSU `parent` and `size` vectors: O(ROWS + COLS).
    *   `used` set: O(K), where K is the number of unique rows and columns used in the stones array.
    *   `roots` set: O(Number of connected components) - Worst case O(K).
    *   Overall Space Complexity: O(ROWS + COLS + K).

### 5. Important Code Patterns or Tricks Used

*   **Row/Column Indexing:** Using `OFFSET` is a neat trick to treat rows and columns as distinct nodes in a single DSU structure.
*   **DSU Optimization (Path Compression and Union by Size):** The DSU implementation includes path compression in the `getRoot` function and union by size in the `join` function, significantly improving the efficiency of the DSU operations.  Path Compression ensures that each `getRoot` operation results in nodes directly pointing to the root of the set.  Union by size ensures that the tree structure is relatively flat to minimize the height of the trees.
*   **Counting Components by Counting Roots:**  The `roots` set effectively counts the number of connected components by only storing the root nodes of each component.

### 6. Any Edge Cases Handled

*   The `checkNodes` function in the DSU handles the case where input node indices might be out of bounds. This is a good practice for robustness.
*   The DSU implementation uses Union by Size, which, together with Path Compression, helps avoid tall, unbalanced trees and keeps the time complexity of DSU operations close to constant in practice.
*   The code handles the case when the input is empty.

```


## Original Code
```cpp
#include <bits/stdc++.h>
#include <vector>
using namespace std;

// Problem: mostStones
// URL: https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/description/
// Difficulty: medium
// Tags:
// Strategy:

// assumes undirected graphs with 0-indexed nodes
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

#define OFFSET 10001
#define ROWS 10001
#define COLS 10001

class Solution {
  public:
    int removeStones(vector<vector<int>> &stones) {
        disjointSetUnion dsu(ROWS + COLS);
        unordered_set<int> used;

        for (auto &vec : stones) {
            int row = vec[1];
            int col = vec[0] + OFFSET;
            dsu.join(row, col);
            used.insert(row);
            used.insert(col);
        }

        set<int> roots;
        for (int x : used) {
            roots.insert(dsu.getRoot(x));
        }

        return stones.size() - roots.size();
    }
};

```

---
*Documentation generated on 2025-08-05 19:36:36*
