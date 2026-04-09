# shortestPathInUndirectedGraph

```markdown
## Documentation for Shortest Path in Undirected Graph with Unit Distances

This document provides a comprehensive analysis of the provided C++ code, which solves the problem of finding the shortest path from a source node to all other nodes in an undirected graph where all edges have a unit distance (weight of 1). The problem is available on GeeksforGeeks at: [https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph-having-unit-distance/1](https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph-having-unit-distance/1).

### 1. Problem Description

The problem requires finding the shortest distance from a given source node (`src`) to every other node in an undirected graph. The graph is represented using an adjacency list (`adj`). Importantly, all edges in the graph have a unit weight (distance of 1).  The output is a vector containing the shortest distances from the source node to each node in the graph. If a node is unreachable from the source, its distance should be represented as -1.

### 2. Approach Explanation

The code implements a Breadth-First Search (BFS) algorithm to find the shortest paths. BFS is ideally suited for this problem due to the unit distance constraint.  BFS explores the graph layer by layer, guaranteeing that the first time a node is visited, it is reached via the shortest path from the source.

Here's a breakdown of the algorithm:

1.  **Initialization:**
    *   `dist`: A vector of size `n` (number of nodes) initialized with -1. This vector will store the shortest distances from the source to each node.  -1 indicates that a node is currently unreachable.
    *   `vis`: A vector of size `n` initialized with `false`.  This vector tracks whether a node has been visited during the BFS traversal.
    *   `queue`: A queue to manage the nodes to be explored in a breadth-first manner.

2.  **Starting Point:**
    *   The distance from the source node (`src`) to itself is set to 0 (`dist[src] = 0`).
    *   The source node is marked as visited (`vis[src] = true`).
    *   The source node is added to the queue (`que.push(src)`).

3.  **BFS Traversal:**
    *   The `while (!que.empty())` loop continues as long as there are nodes in the queue to explore.
    *   Inside the outer loop, `size = (int)que.size()` captures the number of nodes at the current depth/distance from the source. This is important to ensure all nodes at the same distance level are processed before moving to the next distance level.
    *   The inner `while (size--)` loop processes all nodes at the current depth.
    *   For each node `node` dequeued from the queue:
        *   The code iterates through the adjacent nodes `v` of `node` (i.e., `adj[node]`).
        *   If an adjacent node `v` has not been visited (`!vis[v]`):
            *   The adjacent node `v` is marked as visited (`vis[v] = true`).
            *   The distance to `v` is calculated as the distance to `node` plus 1 (`dist[v] = dist[node] + 1`).  Since all edges have unit weight, moving to an adjacent node increases the distance by 1.
            *   The adjacent node `v` is added to the queue (`que.push(v)`) for further exploration.

4.  **Result:**
    *   After the BFS traversal is complete, the `dist` vector contains the shortest distances from the source node to all reachable nodes.  Nodes that remain at a distance of -1 are unreachable from the source. The `dist` vector is returned.

### 3. Key Insights and Algorithmic Techniques Used

*   **BFS for Unit Weight Graphs:** The core insight is that BFS guarantees finding the shortest paths in unweighted graphs or graphs with unit weights.  This is because BFS explores nodes in increasing order of their distance from the source.
*   **Adjacency List Representation:** The use of an adjacency list is efficient for representing sparse graphs (graphs with relatively few edges compared to the number of possible edges).
*   **Visited Array:** The `vis` array is essential for preventing cycles and redundant exploration. It ensures that each node is visited only once, contributing to the algorithm's efficiency.
*   **Distance Tracking:** The `dist` array efficiently stores the shortest distances calculated during the BFS traversal.
*   **Level-Order Processing:**  The code explicitly processes all nodes at the same "level" (distance from the source) before moving on to the next level. This ensures the correctness of the shortest path calculation.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:** O(V + E), where V is the number of vertices (nodes) and E is the number of edges in the graph. This is because BFS visits each vertex and edge at most once. The outer `while` loop iterates at most V times (once for each vertex), and the inner `for` loop iterates through the adjacency list of each vertex, which in total amounts to E edges.
*   **Space Complexity:** O(V), where V is the number of vertices. This is primarily due to the `dist` and `vis` vectors, which both store information for each vertex.  The queue can potentially hold all vertices in the worst-case scenario.

### 5. Important Code Patterns or Tricks Used

*   **Using `-1` to represent infinity/unreachable nodes:**  Initializing the `dist` vector with `-1` is a common technique to indicate that a node is initially unreachable from the source.
*   **Using `queue.size()` in the outer loop for level-order traversal:** The use of `size = queue.size()` before the inner loop allows processing of all nodes at the same level/distance simultaneously.  This is crucial for the correctness of BFS in finding shortest paths.

### 6. Any Edge Cases Handled

*   **Unreachable Nodes:** The algorithm correctly handles unreachable nodes.  If a node is not reachable from the source, its corresponding entry in the `dist` vector will remain at its initial value of -1.
*   **Source Node:** The algorithm correctly handles the source node by initializing its distance to 0.
*   **Empty Graph or Invalid Source:** Although not explicitly checked in the code, if the adjacency list is empty, the function will still execute without error and return a `dist` vector with all values set to -1 (except `dist[src]` which will be -1 if src is a valid index, and the whole vector untouched otherwise). If the `src` index is out of bounds, the code might throw an exception, which should be checked for robust implementation.
```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <climits>
#include <queue>
#include <vector>
using namespace std;

// Problem: easy
// URL: https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph-having-unit-distance/1
// Difficulty: shortestPathInUndirectedGraph
// Tags:
// Strategy:

class Solution {
  public:
    vector<int> shortestPath(vector<vector<int>> &adj, int src) {
        int n = (int)adj.size();
        vector<int> dist(n, -1);
        vector<bool> vis(n, false);
        queue<int> que;

        dist[src] = 0;
        vis[src] = true;
        que.push(src);

        while (!que.empty()) {
            int size = (int)que.size();
            while (size--) {
                // all are in the same depth
                int node = que.front();
                que.pop();
                for (int v : adj[node]) {
                    if (!vis[v]) {
                        vis[v] = true;
                        dist[v] = dist[node] + 1;
                        que.push(v);
                    }
                }
            }
        }

        return dist;
    }
};
```

---
*Documentation generated on 2025-07-30 14:31:33*
