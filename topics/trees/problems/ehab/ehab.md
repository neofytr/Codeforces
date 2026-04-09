# ehab

```markdown
## Competitive Programming Solution Documentation

This document analyzes a C++ solution to the Codeforces problem 1325C - Ehab and Path-etic MEXs ([https://codeforces.com/problemset/problem/1325/C](https://codeforces.com/problemset/problem/1325/C)).

### 1. Problem Description

The problem asks us to assign integer weights from `0` to `n-2` (inclusive) to the `n-1` edges of a tree with `n` nodes such that the minimum value among the weights along any path between two nodes in the tree is maximized.  The goal is to print the assignment of edge weights.

### 2. Approach Explanation

The solution distinguishes between two cases:

1.  **Existence of a high-degree node:** If there exists a node with a degree of 3 or more, then we can guarantee that the maximum MEX (minimum excluded value) along any path will be at most 2.  The strategy is to find such a node, assign the values 0, 1, and 2 to three of the edges connected to it, and then assign the remaining edge weights arbitrarily.

2.  **No high-degree node:** If all nodes have a degree of at most 2, then the tree must be a path (a linear structure).  In this case, the solution can assign edge weights from 0 to `n-2` to the edges in any order. This ensures that the minimum edge weight along any path between two nodes is as large as possible. The provided solution simply assigns i to the i-th edge.

### 3. Key Insights and Algorithmic Techniques Used

*   **Observation about MEX:** The key insight is understanding the relationship between high-degree nodes and the maximum possible MEX. If a node has at least three edges, we can force the minimum edge weight across any path to be no greater than 2. This is because any path must pass either through or around that high-degree node. By assigning 0, 1, and 2 to edges adjacent to this node, we guarantee any path including these edges will have at least one of these small values.

*   **Case Analysis:**  The solution uses a case-based analysis to simplify the problem. The presence or absence of a high-degree node dramatically affects the optimal assignment strategy.

*   **Graph Representation:** The solution uses an adjacency list (`tree`) to represent the graph. Crucially, it stores *edge indices* within the adjacency list rather than node neighbors. This allows for easy access to edge index given a node and avoids more complex lookups.  The `edges` vector stores the edges in the order they appeared in the input, which is important because the final output must be printed in the same input order.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:** O(n), where n is the number of nodes. The algorithm iterates through the nodes to find a node with a degree of at least 3. Then, it iterates through the edges to assign weights.
*   **Space Complexity:** O(n). The `edges` vector stores `n-1` edges, the `tree` vector stores edge indices, and the `ans` vector stores the assigned edge weights.

### 5. Important Code Patterns or Tricks Used

*   **Storing Edge Indices in the Adjacency List:** Storing edge indices, instead of node neighbors, in the adjacency list simplifies the task of assigning weights to the correct edges. This avoids having to search for the corresponding edge when assigning the weights.

*   **Input Order Preservation:** The problem requires the output of edge weights in the same order as the input.  The `edges` vector preserves this original input order.

*   **Initialization:** The `ans` vector is initialized with -1 values which are then filled with appropriate labels.

### 6. Edge Cases Handled

*   **Handling the Path Case:** The code correctly identifies and handles the case where the graph is a path (no node has degree >= 3).

*   **Connectivity:** The problem statement guarantees that the input is a tree, so connectivity is not an explicit concern.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: ehab
// URL: https://codeforces.com/problemset/problem/1325/C
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    int u, v;
    cin >> n;

    vector<pair<int, int>> edges;    // store edges to preserve input order
    vector<vector<int>> tree(n + 1); // now stores EDGE INDICES, not neighbors

    for (int r = 0; r < n - 1; r++) {
        cin >> u >> v;
        edges.push_back({u, v});
        tree[u].push_back(r); // store edge index
        tree[v].push_back(r); // store edge index
    }

    // since there is always a path that connects the edge 0 and edge 1, the largest MEX will always be at least 2
    // now, if there is some node which has it's degree at least 3, we can assign 0, 1 and 2 on three of its adjacent edges
    // this ensures that the largest MEX through any path is exactly 2; we can then assign all the remaining nodes values arbitrarily

    // otherwise, if there are no nodes with degree at least 3, i.e, all the nodes have degree 2, then, since the graph is a tree
    //, the tree becomes a linear structure,
    // the largest MEX will then just be n - 2; and we assign any node any value arbitrarily

    vector<int> ans(n - 1, -1);

    // find node with degree >= 3
    int node = -1;
    for (int i = 1; i <= n; i++) {
        if (tree[i].size() >= 3) {
            node = i;
            break;
        }
    }

    int label = 0;
    if (node != -1) {
        // assign 0,1,2 to three edges incident to this node
        for (int j = 0; j < 3; j++) {
            ans[tree[node][j]] = label++;
        }
        // assign the rest arbitrarily
        for (int i = 0; i < n - 1; i++) {
            if (ans[i] == -1) {
                ans[i] = label++;
            }
        }
    } else {
        // it's a path → just assign 0..n-2
        for (int i = 0; i < n - 1; i++) {
            ans[i] = i;
        }
    }

    // print in input order
    for (int x : ans)
        cout << x << "\n";

    return 0;
}

```

---
*Documentation generated on 2025-09-04 23:25:37*
