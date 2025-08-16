# iceSkating

```markdown
## Code Documentation and Analysis: Ice Skating Problem (Codeforces 217A)

This document provides a comprehensive analysis of the provided C++ code, focusing on its algorithmic aspects and learning points.

### 1. Problem Description (Inferred from Code and Comments)

The code solves the "Ice Skating" problem on Codeforces (Problem 217A, URL: [https://codeforces.com/problemset/problem/217/A](https://codeforces.com/problemset/problem/217/A)).

**Problem Statement:** Given `n` points on a 2D plane, two points are in the same connected component if they share the same x-coordinate or the same y-coordinate. The task is to find the minimum number of ice blocks needed to connect all the points so that they form a single connected component. In other words, determine how many connected components need to be merged to form a single one. The answer will be the number of connected components - 1.

### 2. Approach Explanation

The code employs a Disjoint Set Union (DSU) data structure to efficiently determine the connected components of the points. The core idea is:

1.  **Initialization:** Each point is initially considered a separate connected component.  A DSU is initialized with `n` nodes, each representing a point.
2.  **Connectivity Check:** Iterate through all pairs of points (i, j). If points `i` and `j` share the same x-coordinate OR the same y-coordinate, it implies that they are directly connected and belong to the same connected component.
3.  **Union Operation:** If two points are connected (share the same x or y coordinate), perform a `join` (union) operation in the DSU. This merges the connected components to which the two points belong.
4.  **Count Components:** After iterating through all pairs of points, the `numComponents()` function of the DSU returns the total number of connected components.
5.  **Calculate Result:** The answer is the number of connected components minus 1.  This is because to connect `k` components, we need `k-1` edges (ice blocks in this context).

### 3. Key Insights and Algorithmic Techniques Used

*   **Disjoint Set Union (DSU):** The DSU data structure is crucial for efficiently tracking and merging connected components. It provides near-constant time complexity for `find` and `union` operations, especially with path compression and union by size.
*   **Connected Components:** The problem's core relies on the concept of connected components in a graph. The graph here is implicit, defined by the rule: two points are connected if they share an x or y coordinate.
*   **Union by Size (or Rank):**  The `join` operation in the DSU implementation incorporates union by size.  When merging two sets, the smaller set is attached to the root of the larger set. This helps to keep the tree structures in the DSU relatively flat, improving the performance of the `find` operation (getRoot).
*   **Path Compression:** The `getRoot` function implements path compression.  When finding the root of a node, all nodes along the path to the root are directly attached to the root.  This drastically reduces the path length for subsequent `find` operations.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   DSU Initialization: O(n)
    *   Iterating through all pairs of points: O(n^2)
    *   DSU `join` operation (with path compression and union by size): Amortized almost O(1)
    *   Overall Time Complexity: O(n^2 * α(n)), where α(n) is the inverse Ackermann function, which grows extremely slowly and can be considered almost constant for practical input sizes.  Therefore, it is effectively O(n^2).

*   **Space Complexity:**
    *   DSU `parent` and `size` vectors: O(n)
    *   `pts` vector to store point coordinates: O(n)
    *   Overall Space Complexity: O(n)

### 5. Important Code Patterns or Tricks Used

*   **`#define int long long`:** Using `#define int long long` is a common practice in competitive programming to avoid integer overflow issues, especially when dealing with large input values and potential multiplication operations.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This disables synchronization between the C++ standard streams (cin, cout) and the C standard streams (stdio), and unties `cin` from `cout`, leading to faster input/output operations.
*   **Inlining:**  The use of `inline` keyword for functions like `checkNode`, `checkNodes`, `getSize` and `getRoot` hints to the compiler to potentially inline these functions to reduce the function call overhead.
*   **Path Compression and Union by Size:** As explained before, these are core optimization techniques for DSU, significantly improving its efficiency.

### 6. Edge Cases Handled

*   **`checkNode(x)` and `checkNodes(x, y)`:**  These functions check if the node indices `x` and `y` are within the valid range (0 to `numNodes` - 1), preventing potential out-of-bounds access and errors.
*   **`isConnected(x, y)` returns -1:** This handles the case when either `x` or `y` is an invalid node, returning -1 to indicate an error.
*   **Joining nodes already in the same component:** The `join` function explicitly checks `if (rootX == rootY)` before performing the union, avoiding unnecessary operations.

### Additional Notes

The `/* ... */` comment at the end of the code appears to be leftover from a different problem and is irrelevant to the ice skating problem's solution.  It involves parsing a signed integer from a string.
```

## Original Code
```cpp
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

// Problem: iceSkating
// URL: https://codeforces.com/problemset/problem/217/A
// Difficulty: medium
// Tags:
// Strategy:

#define MAXCOORD (1000)

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    int x, y;
    disjointSetUnion dsu(n);
    vector<pair<int, int>> pts;
    int r = n;
    while (r--) {
        cin >> x >> y;
        pts.push_back({x, y});
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (pts[i].first == pts[j].first || pts[i].second == pts[j].second) {
                dsu.join(i, j);
            }
        }
    }

    cout << dsu.numComponents() - 1 << endl;
}

/*

int left = 0;
while(s[left] == ' ')
    left++;

if (s[left] == '+')
    left++;
else if (s[left] == '-') {
sign = -1;
left++;}

int right = left;
while(isdigit(s[right]))
    right++;

if (left == right)
    cout << 0 << endl;
for (int i = right - 1; i >= left; i--) {
}
*/

```

---
*Documentation generated on 2025-08-16 22:11:04*
