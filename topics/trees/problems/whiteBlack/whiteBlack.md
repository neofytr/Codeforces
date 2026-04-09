# whiteBlack

```markdown
## Code Documentation: White Black Tree Problem

This document provides a comprehensive analysis of the given C++ code, focusing on the algorithmic techniques, time complexity, and key insights. The code solves a problem related to balancing white and black vertices in a tree.

### 1. Problem Description (Inferred)

Based on the comments and the provided URL ([https://codeforces.com/problemset/problem/1676/G](https://codeforces.com/problemset/problem/1676/G)), the problem can be described as follows:

Given a tree with `n` nodes, where each node is colored either white ('W') or black ('B'), the task is to find the number of subtrees (rooted at any node) where the number of white nodes is equal to the number of black nodes.

**Input:**

*   `t`: The number of test cases.
*   `n`: The number of nodes in the tree.
*   A list of `n-1` integers representing the parent of each node from 2 to `n`.  This implicitly defines a rooted tree structure with node 1 as the root.
*   A string `coloring` of length `n` representing the colors of the nodes. `coloring[i]` is the color of node `i+1`.

**Output:**

For each test case, output the number of subtrees with balanced white and black nodes.

### 2. Approach Explanation

The code employs a Depth-First Search (DFS) approach to traverse the tree and compute the balance of each subtree. The `bal()` function performs the core logic:

1.  **Recursive Traversal:** It recursively calls itself on each child of the current node.
2.  **Balance Calculation:** It calculates the difference between the number of white and black nodes in the subtree rooted at the current node.  Black nodes contribute -1 and white nodes contribute +1 to the difference.
3.  **Counting Balanced Subtrees:** If the calculated difference is zero (i.e., the number of white and black nodes are equal in the subtree), the `cnt` variable (a global variable used to count such balanced subtrees) is incremented.
4.  **Return Value:** The function returns the balance (difference) of the subtree to its parent.

The `main()` function handles input, tree construction, and calls the `bal()` function to start the DFS traversal from the root of the tree. Finally, it outputs the `cnt` value, representing the total number of balanced subtrees.

### 3. Key Insights and Algorithmic Techniques Used

*   **Depth-First Search (DFS):** The DFS traversal is crucial for exploring the tree structure and calculating the subtree balance in a systematic manner.  It allows for efficient computation of the balance by accumulating results from the children nodes to the parent node.
*   **Subtree Balance Calculation:** The key idea is to represent the balance of a subtree as the difference between the number of white and black nodes.  This simplification makes it easy to determine if a subtree is balanced (difference is zero).
*   **Tree Representation:** The tree is represented using an adjacency list (`vector<vector<int>> tree`). Each `tree[i]` stores a vector of the children of node `i`.
*   **Post-Order Traversal:**  The DFS effectively performs a post-order traversal of the tree.  The balance of each child is calculated before updating the balance of the parent. This ensures correct accumulation of subtree balances.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:** The code performs a DFS traversal of the tree.  Each node is visited exactly once. Therefore, the time complexity is O(N), where N is the number of nodes in the tree.
*   **Space Complexity:**
    *   The adjacency list `tree` requires O(N) space to store the tree structure.
    *   The recursion stack used by the DFS can have a depth of at most N in the worst-case scenario (e.g., a skewed tree). Therefore, the recursion stack has a space complexity of O(N).
    *   The string `coloring` takes O(N) space.
    *   Thus, the overall space complexity is O(N).

### 5. Important Code Patterns or Tricks Used

*   **Adjacency List Tree Representation:** This is a standard and efficient way to represent trees, allowing easy access to the children of any node.
*   **Global Variable for Counting:**  The code uses a global variable `cnt` to accumulate the number of balanced subtrees. While global variables can sometimes be problematic, in this case, it simplifies the logic of the `bal()` function and avoids passing the count as a parameter in each recursive call. However, it is crucial to reset the `cnt` variable to 0 for each test case.
*   **Integer Data Type:** The code uses `long long` (`int long long`) for integer variables. This is a good practice in competitive programming to avoid potential integer overflow issues, especially when dealing with large numbers.
*   **Optimized Input/Output:** `ios_base::sync_with_stdio(false); cin.tie(NULL);` are used to disable synchronization between C++ streams and C streams, which can significantly improve the input/output performance.

### 6. Edge Cases Handled

*   **Root Node:** The code assumes that node 1 is the root of the tree. This assumption is based on how the input is structured (parents of nodes 2 to n are given).
*   **Empty Subtrees (Leaves):** The `bal()` function implicitly handles leaf nodes correctly.  For a leaf node, the balance is simply determined by the color of the node itself. If a leaf is colored such that its balance is 0, then `cnt` will be incremented.
*   **Disconnected Graph:** The problem statement specifies that the input is a *tree*.  The code does not explicitly handle cases where the input is not a tree (e.g., a disconnected graph or a graph with cycles).  If the input violates the problem statement, the code's behavior is undefined. However, assuming it is a tree, the DFS approach will work correctly.

### Learning Points

*   **DFS for Tree Traversal:** This problem provides a good example of how DFS can be used to solve tree-related problems efficiently.
*   **Subtree Properties Calculation:**  The concept of calculating subtree properties recursively (e.g., balance, size, sum) is a fundamental technique in tree algorithms.
*   **Importance of Clear Problem Understanding:**  Understanding the problem constraints and edge cases is crucial for writing correct code.  The code assumes that the input is a valid tree, which is an important implicit constraint.
*   **Choice of Data Structures:**  The choice of the adjacency list for representing the tree is suitable and efficient for this problem.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: whiteBlack
// URL: https://codeforces.com/problemset/problem/1676/G
// Difficulty: medium
// Tags:
// Strategy:

int cnt = 0;
// this returns the number of white vertices - black vertices in the subtree rooted at node
int bal(const int node, const string &coloring, const vector<vector<int>> &tree) {
    int diff = 0;
    for (const int v : tree[node])
        diff += bal(v, coloring, tree);
    diff += ((coloring[node - 1] == 'B') ? -1 : 1);
    if (!diff)
        cnt++;
    return diff;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        int root = 1;
        int pt;
        vector<vector<int>> tree(n + 1);
        for (int r = 2; r <= n; r++)
            cin >> pt, tree[pt].push_back(r); // we store the tree as a directed graph

        string coloring;
        cin >> coloring;
        // bal(n) = true iff the number of white vertices and black vertices in the subtree rooted at n are equal
        bal(root, coloring, tree);
        cout << cnt << endl;
        cnt = 0;
    }
    return 0;
}
```

---
*Documentation generated on 2025-09-04 09:09:03*
