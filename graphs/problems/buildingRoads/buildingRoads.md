# buildingRoads

```markdown
# Competitive Programming Solution Documentation: Building Roads

This document provides a detailed analysis of the provided C++ code, which solves the "Building Roads" problem on CSES.

## 1. Problem Description

The problem (CSES Problem Set, task 1666, available at [https://cses.fi/problemset/task/1666](https://cses.fi/problemset/task/1666)) asks us to find the minimum number of roads that need to be built to connect all the cities in a country.  We are given the number of cities `n` and the number of existing roads `m`. Each road connects two cities. The goal is to output the number of additional roads needed and the pairs of cities that should be connected to ensure all cities are reachable from each other.

## 2. Approach Explanation

The provided code uses a simple graph traversal approach to solve the problem. The core idea is to find the connected components within the given graph of cities and roads. For each connected component, we need to add edges to connect it with other components.

Here's a breakdown:

1. **Graph Representation:** The code represents the cities and roads as an adjacency list graph using `vector<vector<int>> graph(n)`.
2. **Connected Component Detection:** The code iterates through all cities (nodes). For each unvisited city, it performs a Breadth-First Search (BFS) to identify all cities within the same connected component.  A `vector<bool> vis(n, false)` keeps track of visited cities. A `queue<int> que` is used for the BFS traversal.
3. **Connecting Components:**  For each new connected component found (an unvisited node encountered), the code maintains a `prev` variable that stores the node visited in the previous connected component. It stores the pair of `prev` and the current node in the `res` vector. This pair represents the new road that needs to be built to connect the two connected components. The number of such roads required is one less than the number of connected components.
4. **Output:** Finally, the code prints the number of additional roads needed (which is the number of connected components minus 1) and the list of city pairs that need to be connected by new roads.

## 3. Key Insights and Algorithmic Techniques Used

*   **Connected Components:** Identifying connected components is the fundamental step in solving this problem.  Understanding that the minimum number of roads needed to connect `k` components is `k-1` is crucial.
*   **Breadth-First Search (BFS):**  BFS is used to efficiently traverse each connected component. While Depth-First Search (DFS) could also be used, BFS is often preferred due to its simpler iterative implementation.
*   **Adjacency List:** Using an adjacency list (`vector<vector<int>>`) is an efficient way to represent the graph, especially when the graph is sparse (i.e., the number of edges is significantly less than the maximum possible number of edges).

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Building the graph: O(m), where `m` is the number of roads.
    *   Iterating through all nodes: O(n), where `n` is the number of cities.
    *   BFS traversal: O(n + m) in the worst case (visiting all nodes and edges).
    *   Therefore, the overall time complexity is O(n + m).

*   **Space Complexity:**
    *   Graph representation: O(n + m) (adjacency list stores `m` edges, and the `n` nodes).
    *   `vis` vector: O(n).
    *   `que` queue: O(n) in the worst case.
    *   `res` vector: O(n) in the worst case (when all nodes are disconnected).
    *   Therefore, the overall space complexity is O(n + m).

## 5. Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**: This is a common optimization technique used in competitive programming to disable synchronization between the C++ standard input/output streams and the C standard input/output streams, which can significantly improve input/output performance.
*   **`u--, v--`**:  The code subtracts 1 from the input city numbers (`u` and `v`) because the problem uses 1-based indexing, while the code uses 0-based indexing for the graph.
*   **`auto &[u, v] : res`**: This is a C++17 feature called structured binding, used to unpack the elements of the pair directly into the `u` and `v` variables within the loop, avoiding the need to access them using `pair.first` and `pair.second`. This is generally preferred for readability.

## 6. Edge Cases Handled

*   **Disconnected Graph:** The code correctly handles the case where the graph is not connected.  The BFS ensures that each connected component is visited and the necessary roads are added to connect them.
*   **Empty Graph:** The code works correctly even if `m = 0`.  In this case, the number of connected components would be `n`.
*   **No edges needed:** If the graph is already connected i.e. consists of single connected component, the code correctly outputs `0` in the number of additional edges and no connection pairs.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: buildingRoads
// URL: https://cses.fi/problemset/task/1666
// Difficulty: medium
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;

    int u, v;
    vector<vector<int>> graph(n);
    while(m--) 
        cin >> u >> v, u--, v--, graph[v].push_back(u), graph[u].push_back(v);

    int cnt = 0;
    vector<bool> vis(n, false);
    queue<int> que;
    vector<pair<int, int>> res;
    int prev = -1;
    for (int node = 0; node < n; node++)
        if (!vis[node]) {
            cnt++;
            if (prev != -1)
                res.push_back({prev, node}), prev = node;
            else 
                prev = node;
            int src = node;
            vis[src] = true;
            que.push(src);
            while(!que.empty()) {
                int x = que.front();
                que.pop();

                for (int v : graph[x])
                    if (!vis[v])
                        vis[v] = true, que.push(v);
            }
        }
    cout << cnt - 1 << endl;
    for (auto &[u, v] : res)
        cout << u + 1 << " " << v + 1 << endl;
    return 0;
}

```

---
*Documentation generated on 2025-10-04 10:26:25*
