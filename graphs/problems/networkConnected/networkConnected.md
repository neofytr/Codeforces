# networkConnected

```markdown
# Solution Documentation: Number of Operations to Make Network Connected

This document analyzes a C++ solution to the "Number of Operations to Make Network Connected" problem, found on LeetCode at [https://leetcode.com/problems/number-of-operations-to-make-network-connected/description/](https://leetcode.com/problems/number-of-operations-to-make-network-connected/description/).

## 1. Problem Description

The problem asks for the minimum number of operations (cable transfers) required to connect all computers in a network.  Given `n` computers and a list of `connections` (edges), each connecting two computers, determine the number of operations needed to make the network connected. If it's not possible to connect all computers, return -1. You can only move cables, not create new ones.

## 2. Approach Explanation

The solution uses the Disjoint Set Union (DSU) data structure to efficiently determine the number of connected components in the network. The core idea is that if the number of connected components is `c`, then we need at least `c - 1` additional connections (cables) to connect all the components into a single, fully connected network.

1. **DSU Initialization:** A DSU is initialized with `n` nodes, representing the computers. Initially, each computer is considered a separate connected component.

2. **Iterate through Connections:** The code iterates through the given `connections`. For each connection (edge) between computers `a` and `b`:
   - **Check if Already Connected:** Using `dsu.isConnected(a, b)`, it checks if `a` and `b` are already in the same connected component.
   - **If Connected:** If they are already connected, it means this connection is redundant.  The `leftConnections` counter is incremented, representing the number of "spare" cables that could be used elsewhere.
   - **If Not Connected:** If they are not connected, the DSU's `join(a, b)` operation merges the connected components of `a` and `b`, effectively connecting them using the given cable.

3. **Determine the Number of Operations:** After processing all connections, the DSU's `numComponents()` method returns the number of remaining connected components (`compSize`).
   - **If More Than One Component:** If `compSize > 1`, it means the network is not fully connected.  The code checks if we have enough spare cables (`leftConnections`) to connect all the components. We need `compSize - 1` spare cables.
     - **Sufficient Cables:** If `leftConnections >= compSize - 1`, the network can be connected, and the result is `compSize - 1`.
     - **Insufficient Cables:** If `leftConnections < compSize - 1`, the network cannot be connected, and the result is -1.
   - **If Only One Component:** If `compSize == 1`, the network is already connected, so the result is 0.

## 3. Key Insights and Algorithmic Techniques Used

- **Disjoint Set Union (DSU):** The core technique used is DSU (also known as Union-Find). DSU is very efficient for managing connected components in a graph. It provides `find` (getRoot) and `union` (join) operations, which have near-constant amortized time complexity.
- **Connected Components:** The number of connected components is the key to solving this problem.
- **Greedy Approach:** The algorithm greedily merges connected components whenever possible.

## 4. Time and Space Complexity Analysis

- **Time Complexity:**
    - DSU initialization: O(n)
    - Iterating through connections: O(m), where m is the number of connections.
    - DSU `getRoot` operation with path compression: O(α(n)) amortized time complexity, where α(n) is the inverse Ackermann function, which grows extremely slowly.  For practical purposes, it can be considered almost constant.
    - DSU `join` operation: Also O(α(n)) amortized.

    Therefore, the overall time complexity is O(n + m * α(n)), which is practically O(n + m).

- **Space Complexity:**
    - DSU data structures (`parent`, `size`): O(n)
    - Input connections: O(m)

    Therefore, the overall space complexity is O(n + m).

## 5. Important Code Patterns or Tricks Used

- **Path Compression in DSU:** The `getRoot` function uses path compression to optimize the DSU's performance.  This technique flattens the tree structure of the DSU, making subsequent `find` operations faster.
- **Union by Size:** The `join` function uses union by size to keep the trees in the DSU relatively balanced.  It always attaches the root of the smaller tree to the root of the larger tree. This helps prevent the creation of tall, skinny trees, which would degrade the performance of the `find` operation.
- **Clear Variable Names:**  The code uses meaningful variable names (e.g., `numNodes`, `numComp`, `leftConnections`), improving readability.
- **Concise Conditionals:** The use of `inline` functions for simple operations (like `checkNode` and `checkNodes`) and clear conditional statements (especially in `join` and `makeConnected`) makes the code easier to understand.

## 6. Any Edge Cases Handled

- **Insufficient Cables:** The algorithm correctly handles the case where there are not enough spare cables to connect all the components. It returns -1 in this scenario.
- **Already Connected Network:** The algorithm correctly handles the case where the network is already connected (i.e., only one connected component). It returns 0 in this scenario.
- **Invalid Nodes:** The `checkNodes` and `checkNode` functions in the DSU ensure that the input nodes are within the valid range [0, numNodes). This avoids potential out-of-bounds access errors. This check adds robustness to the DSU implementation.


## Original Code
```cpp
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
```

---
*Documentation generated on 2025-08-05 18:40:42*
