# copil

```markdown
# Competitive Programming Solution Documentation

## 1. Problem Description

The problem is [A. Copil and Job](https://codeforces.com/problemset/problem/1830/A) from Codeforces Round #871 (Div. 4).

The problem describes a tree structure with `n` nodes. Each edge of the tree is associated with an index corresponding to its input order.  The goal is to determine the minimum number of "scans" needed to activate all nodes in the tree, starting from node 1. Activation depends on the edge index: a node `v` can be activated from its parent `u` if the edge index between `u` and `v` is greater than the edge index that activated `u`. If it is not, the node requires an additional scan. We aim to find the maximum number of scans needed across all nodes to activate the tree.

## 2. Approach Explanation

The solution utilizes a Breadth-First Search (BFS) approach to traverse the tree and dynamically calculate the number of scans required for each node.  `dp[i]` stores the minimum scans required to activate node `i`. `id[i]` stores the index of the edge that activated node `i`.  The BFS starts from node 1, which is considered the root and initially requires 1 scan.

For each node `u` and its neighbor `v`, the solution checks if the edge index between `u` and `v` (stored in `mp[{u, v}]`) is greater than the edge index that activated `u` (`id[u]`). If it is, then `v` can be activated in the same scan as `u`. Otherwise, `v` requires an additional scan. The `id` of the activated child `v` is updated.

Finally, the maximum value in the `dp` array is found and printed, representing the maximum scans required to activate all nodes.

## 3. Key Insights and Algorithmic Techniques Used

*   **BFS for Tree Traversal:** The core algorithm used for traversing the tree is Breadth-First Search (BFS). BFS is appropriate because it systematically explores the tree level by level, ensuring that the shortest path from the source node is considered first.
*   **Dynamic Programming (DP):** The `dp` array efficiently stores the number of scans needed for each node, avoiding redundant calculations. It leverages the parent-child relationships in the tree.
*   **Edge Index Tracking:** The `id` array stores the index of the edge that was used to activate a node. This is crucial for determining whether an additional scan is needed.
*   **Unordered Map for Edge Index Lookup:** The `unordered_map` (hash map) `mp` provides fast lookup of the edge index between any two connected nodes. This allows for O(1) retrieval of edge indices.
*   **Custom Hash Function for Pairs:** Because `std::pair` isn't hashable by default in older compilers, a custom hash function `pair_hash` is created and used to hash pairs into unique keys in the unordered map. This resolves the error and enables the usage of `unordered_map<pair<int, int>, int>`.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Building the adjacency list and edge index map takes O(n) time, where `n` is the number of nodes (and `n-1` is the number of edges).
    *   The BFS traversal visits each node and edge once, taking O(n) time.
    *   Finding the maximum value in the `dp` array takes O(n) time.
    *   Therefore, the overall time complexity is O(n).

*   **Space Complexity:**
    *   The adjacency list `g` takes O(n) space.
    *   The `unordered_map` `mp` takes O(n) space.
    *   The `dp` array takes O(n) space.
    *   The `id` array takes O(n) space.
    *   The queue `que` can contain at most all nodes in the tree at some point, taking O(n) space.
    *   Therefore, the overall space complexity is O(n).

## 5. Important Code Patterns or Tricks Used

*   **`unordered_map` with Custom Hash:** Using an `unordered_map` with a custom hash function for `pair<int, int>` is essential for efficient edge index lookup.  This approach can be generalized to other situations where you need to hash composite keys.
*   **BFS with State Updates:** The BFS traversal is combined with dynamic state updates (using `dp` and `id`) to efficiently compute the required scans for each node.
*   **Edge index tracking**: Keeping track of the edge index that was used to activate a node is a critical technique. This is used when deciding whether an adjacent node needs an additional scan.

## 6. Any Edge Cases Handled

*   The root node (node 1) is handled as the starting point of the BFS with an initial scan value of 1.
*   The code implicitly handles disconnected components, as each test case constructs a single connected tree. Since BFS starts from Node 1, disconnected components would not be reached or processed. However, the problem constraints guaranteed a single connected component (a tree).
*   The code correctly handles cases where an edge can be encountered in either direction `(u, v)` or `(v, u)`.  The `mp` stores the edge index for both `mp[{u, v}]` and `mp[{v, u}]`.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: copil
// URL: https://codeforces.com/problemset/problem/1830/A
// Difficulty: hard
// Tags:
// Strategy:

#include <bits/stdc++.h>
using namespace std;

#define int long long

struct pair_hash {
    template <class T1, class T2> std::size_t operator()(const std::pair<T1, T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Combine hashes (example method: XOR with shifting)
        return h1 ^ (h2 << 1);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        unordered_map<pair<int, int>, int, pair_hash> mp;
        vector<vector<int>> g(n + 1);
        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
            mp[{u, v}] = mp[{v, u}] = i;
        }

        // dp[r] is the number of scans needed to activate node r
        vector<int> dp(n + 1, -1);

        int src = 1;
        queue<pair<int, int>> que;

        // id[r] is the index of the edge (in the input array) that made the node r
        vector<int> id(n + 1, -1);
        dp[1] = 1;
        id[1] = 0;
        que.push({src, -1});
        while (!que.empty()) {
            auto [node, parent] = que.front();
            que.pop();
            for (const int v : g[node]) {
                if (v == parent)
                    continue;
                const int edgeID = mp[{v, node}];
                if (edgeID > id[node])
                    dp[v] = dp[node];
                else
                    dp[v] = dp[node] + 1;
                id[v] = edgeID;
                que.push({v, node});
            }
        }

        int ans = dp[1];
        for (int r = 1; r <= n; r++)
            ans = max(dp[r], ans);
        cout << ans << endl;
    }
    return 0;
}

```

---
*Documentation generated on 2025-09-04 19:44:21*
