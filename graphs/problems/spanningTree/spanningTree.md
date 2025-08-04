# spanningTree

```markdown
# Minimum Spanning Tree (MST) - Prim's Algorithm

## 1. Problem Description

The code implements a solution to find the Minimum Spanning Tree (MST) of a given undirected graph. The graph is represented as a list of edges, where each edge is a tuple `(u, v, w)` representing an edge between nodes `u` and `v` with weight `w`.  The task is to find a subset of edges that connects all vertices of the graph without cycles and minimizes the sum of the edge weights.  The problem is available on GeeksforGeeks ([https://www.geeksforgeeks.org/problems/minimum-spanning-tree/1](https://www.geeksforgeeks.org/problems/minimum-spanning-tree/1)). The `spanningTree` function takes the number of nodes `n` and a vector of edges `edges` as input, and returns the total weight of the MST.

## 2. Approach Explanation

The code utilizes Prim's algorithm to find the MST. Prim's algorithm is a greedy algorithm that starts with an arbitrary node and iteratively adds the minimum-weight edge that connects a node in the MST to a node not yet in the MST.  The algorithm continues until all nodes are included in the MST.

The general steps are:

1.  **Initialization:**
    *   Create an adjacency list representation of the graph using the provided edges.  Each node stores a list of its neighbors along with the edge weights connecting to them.
    *   Initialize a priority queue to store candidate edges for inclusion in the MST. The priority queue is ordered by edge weight, allowing efficient retrieval of the minimum-weight edge.
    *   Initialize a boolean vector to track which nodes have already been included in the MST.

2.  **Iteration:**
    *   Start with an arbitrary node (node 0 in this case) and add it to the MST. Add all the edges connecting it to other nodes to the priority queue.
    *   While the priority queue is not empty, repeatedly extract the minimum-weight edge from the priority queue.
    *   If the node connected by this edge is not already in the MST, add it to the MST, add the edge weight to the total MST weight, and add all the edges connecting it to other nodes to the priority queue.

3.  **Termination:**
    *   The algorithm terminates when all nodes have been included in the MST, which can be determined implicitly by the fact that the priority queue becomes empty.
    *   Return the total weight of the MST.

## 3. Key Insights and Algorithmic Techniques Used

*   **Prim's Algorithm:** The core algorithm is Prim's algorithm, a classic greedy algorithm for finding MSTs. Its key idea is to build the MST incrementally by always choosing the smallest edge that connects a node already in the MST to a node outside the MST.
*   **Priority Queue:** A priority queue (`priority_queue`) is used to efficiently select the minimum-weight edge at each step. This data structure allows the algorithm to quickly find the next edge to add to the MST. Using a `greater<>` comparator ensures that the minimum element is always at the top of the queue.
*   **Adjacency List:** The graph is represented using an adjacency list. This representation is suitable for sparse graphs, where the number of edges is much smaller than the square of the number of nodes. It allows efficient access to the neighbors of each node.
*   **Visited Set:** A `vis` vector is used to keep track of which nodes have already been included in the MST. This prevents cycles and ensures that each node is added to the MST only once.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:** The time complexity of Prim's algorithm using a priority queue is O(E log V), where E is the number of edges and V is the number of vertices. This is because each edge is added to the priority queue at most once, and the priority queue operations (insertion and extraction) take O(log E) time, which is equivalent to O(log V) when E is proportional to V^2.
*   **Space Complexity:** The space complexity is O(V + E) for storing the adjacency list and the visited set. The priority queue can also hold up to E edges in the worst case.

## 5. Important Code Patterns or Tricks Used

*   **Adjacency List Representation:** The code demonstrates how to construct an adjacency list from a list of edges. This is a common technique for representing graphs in many algorithms.
*   **Pair and Tuple Usage:**  The use of `pair<int, int>` to store the `(weight, node)` information in the priority queue provides a clear way to associate costs with nodes.
*   **Lambda Expression with `greater<>`:** The `greater<>` functor with a `priority_queue` ensures the queue is a min-heap, which is essential for Prim's algorithm to efficiently retrieve the smallest weight edges.
*   **Structured Bindings (C++17):** The use of `auto [weight, node] = pq.top();` is an example of structured bindings introduced in C++17, which makes the code more readable by directly unpacking the elements of a pair.

## 6. Edge Cases Handled

*   **Disconnected Graph:** If the input graph is disconnected, the algorithm will only find the MST of the connected component containing the starting node (node 0 in this implementation). The return value would be the sum of edge weights within that single component's MST.  The provided GeeksforGeeks problem states that the graph *is* connected.  If disconnected graphs were a possibility, further checks and potentially a loop to start Prim's algorithm from a new unvisited node in each component would be necessary to find an MST for the entire forest of components.
*   **Duplicate Edges:** The code handles duplicate edges correctly. Since the priority queue always chooses the minimum-weight edge, duplicate edges with higher weights will be ignored. If there are duplicate edges with the same weight, the algorithm will arbitrarily choose one of them.
*   **Self-Loops:**  Self-loops (edges from a node to itself) are not explicitly handled, but because `u != v` is not explicitly checked, they *are* processed.  If the self-loop has a weight of 0, it could affect results. A more robust implementation might filter out self-loops.
```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <queue>
#include <vector>
using namespace std;

// Problem: spanningTree
// URL: https://www.geeksforgeeks.org/problems/minimum-spanning-tree/1
// Difficulty: medium
// Tags:
// Strategy:

class Solution {
  public:
    int spanningTree(int n, vector<vector<int>> &edges) {
        int sum = 0;
        vector<vector<pair<int, int>>> graph(n);
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        vector<bool> vis(n, false);

        pq.push({0, 0}); // {weight, node}

        while (!pq.empty()) {
            auto [weight, node] = pq.top();
            pq.pop();

            if (vis[node])
                continue;

            vis[node] = true;
            sum += weight;

            for (auto &[v, w] : graph[node]) {
                if (!vis[v]) {
                    pq.push({w, v});
                }
            }
        }

        return sum;
    }
};

```

---
*Documentation generated on 2025-08-04 23:23:35*
