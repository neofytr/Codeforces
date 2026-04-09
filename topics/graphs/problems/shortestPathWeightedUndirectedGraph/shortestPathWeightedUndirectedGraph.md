# shortestPathWeightedUndirectedGraph

```markdown
## Shortest Path in Weighted Undirected Graph

This document provides a comprehensive analysis of a C++ solution for finding the shortest path in a weighted undirected graph. The problem is available on GeeksforGeeks: [https://www.geeksforgeeks.org/problems/shortest-path-in-weighted-undirected-graph/1](https://www.geeksforgeeks.org/problems/shortest-path-in-weighted-undirected-graph/1).

### 1. Problem Description

Given a weighted undirected graph with *n* nodes and *m* edges, the task is to find the shortest path from node 1 (source) to node *n* (destination). The nodes are numbered from 1 to *n*. The input consists of the number of nodes *n*, the number of edges *m*, and a vector of edges where each edge is represented by a vector `{u, v, w}`, indicating an edge between nodes *u* and *v* with weight *w*. If there is no path from the source to the destination, return a vector containing only `-1`. Otherwise, return a vector representing the shortest path from source to destination, and that contains all the nodes in the shortest path in order and the total weight of the shortest path at the end.  Note that the node indices returned must be 1-indexed.

### 2. Approach Explanation

The solution employs Dijkstra's algorithm to find the shortest path. Dijkstra's algorithm is a greedy algorithm that iteratively explores the graph, maintaining a set of visited nodes and a distance estimate for each node from the source.

Here's a breakdown of the steps:

1.  **Graph Representation:** The input edges are used to construct an adjacency list representation of the graph, `graph`. Each entry `graph[i]` stores a vector of pairs `{v, w}`, where `v` is a neighboring node of node `i` and `w` is the weight of the edge between them.
2.  **Initialization:**
    *   `dist`: A vector of size *n* initialized with `INT_MAX`, representing the shortest distance estimate from the source to each node. `dist[src]` is initialized to 0.
    *   `parent`: A vector of size *n*, used to reconstruct the shortest path. `parent[i]` stores the parent of node `i` in the shortest path tree.  Initially, each node is its own parent.
    *   `heap`: A `set` (used as a min-priority queue) storing pairs `{distance, node}`, used to efficiently select the node with the smallest distance estimate to explore next.
3.  **Dijkstra's Algorithm:**
    *   While the heap is not empty:
        *   Extract the node `node` with the smallest distance `dist[node]` from the heap.
        *   Iterate through the neighbors `v` of `node`:
            *   If `dist[node] + w < dist[v]`, where `w` is the weight of the edge between `node` and `v`, then a shorter path to `v` has been found.
            *   Update `dist[v]` to `dist[node] + w`.
            *   Update `parent[v]` to `node`.
            *   Remove the old entry of `v` from the `heap` (if it exists) and insert the new distance to the `heap`.  This reorders the queue to maintain the min-priority queue property.
4.  **Path Reconstruction:**
    *   If `dist[end]` is still `INT_MAX`, it means there is no path from the source to the destination. Return `{-1}`.
    *   Otherwise, reconstruct the path by starting from the destination node and tracing back to the source using the `parent` vector.
5.  **Result Formatting:**
    *   The path is built in reverse order. Reverse the path and adjust for 1-based indexing. Append total cost to the path.

### 3. Key Insights and Algorithmic Techniques

*   **Dijkstra's Algorithm:** The core algorithm used is Dijkstra's algorithm, which efficiently finds the shortest paths from a source node to all other nodes in a weighted graph with non-negative edge weights.
*   **Adjacency List:**  Using an adjacency list to represent the graph is memory-efficient, especially for sparse graphs.
*   **Min-Priority Queue (Set):** Using a `set` in C++ provides a sorted container that can be efficiently used as a min-priority queue. The `set` automatically maintains the elements in sorted order, allowing easy access to the node with the smallest distance estimate. The `heap.erase()` operation allows us to update node priorities.
*   **Parent Array for Path Reconstruction:** The `parent` array is a crucial component for reconstructing the shortest path after Dijkstra's algorithm is complete. By tracing back from the destination to the source using the `parent` array, the shortest path can be efficiently determined.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**  The time complexity is dominated by Dijkstra's algorithm. Using a `set` as the min-priority queue, the time complexity is O((E+V) log V), where V is the number of vertices (nodes) and E is the number of edges.  Each edge is potentially visited at most once, and insertion/deletion to the set is O(log V). Since it is an undirected graph, the number of edges can be as large as O(V^2). Thus, in the worst case, time complexity can be O(V^2 log V).

*   **Space Complexity:**
    *   `graph`: O(E) to store the adjacency list.
    *   `dist`: O(V) to store the distances from the source.
    *   `parent`: O(V) to store the parent nodes.
    *   `heap`: O(V) in the worst case.
    *   `path`: O(V) in the worst case.
    *   Therefore, the overall space complexity is O(V + E).

### 5. Important Code Patterns or Tricks Used

*   **1-based Indexing Adjustment:** The code adjusts for 1-based indexing by decrementing node indices when building the graph and incrementing them when constructing the final path.
*   **Using `set` as a Min-Priority Queue:** The `set` container is used to implement a min-priority queue.  It provides automatic sorting and efficient insertion and removal of elements.  The code correctly handles the case where a node's distance is updated by first erasing the old entry from the `set` before inserting the new entry.
*   **INT_MAX for Initialization:** Using `INT_MAX` to initialize the `dist` vector is a common practice to represent infinite distance.
*   **Edge Case Handling:**  The code handles the edge case where no path exists between the source and destination by checking if `dist[end]` is still `INT_MAX` after Dijkstra's algorithm completes.

### 6. Edge Cases Handled

*   **No Path:** The code correctly returns `{-1}` when no path exists between the source and destination.
*   **Disconnected Graph:** The algorithm works correctly for disconnected graphs, as it will only explore the connected component containing the source node.
*   **Weighted Undirected Graph:** The code correctly implements the symmetric additions to the adjacency list to represent an undirected graph.
*   **1-Based Indexing:** The code correctly converts between 0-based indexing used internally and 1-based indexing required for the output.
```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

// Problem: shortestPathWeightedUndirectedGraph
// URL: https://www.geeksforgeeks.org/problems/shortest-path-in-weighted-undirected-graph/1
// Difficulty: medium
// Tags:
// Strategy:

class Solution {
  public:
    vector<int> shortestPath(int n, int m, vector<vector<int>> &edges) {
        int size = (int)edges.size();
        vector<int> path;
        vector<vector<pair<int, int>>> graph(n);
        for (int i = 0; i < size; i++) {
            int a = edges[i][0];
            int b = edges[i][1];
            int w = edges[i][2];
            a--, b--;
            graph[a].push_back({b, w});
            graph[b].push_back({a, w});
        }

        int src = 0;
        int end = n - 1;
        vector<int> parent(n);
        vector<int> dist(n, INT_MAX);
        set<pair<int, int>> heap;

        for (int node = 0; node < n; node++) {
            parent[node] = node;
        }
        dist[src] = 0;
        heap.insert({dist[src], src});

        while (!heap.empty()) {
            auto elt = *(heap.begin());
            heap.erase(elt);
            int node = elt.second;
            for (auto e : graph[node]) {
                int v = e.first;
                int w = e.second;
                if (dist[node] + w < dist[v]) {
                    heap.erase({dist[v], v});
                    dist[v] = dist[node] + w;
                    parent[v] = node;
                    heap.insert({dist[v], v});
                }
            }
        }

        if (dist[end] == INT_MAX)
            return {-1};

        for (int v = end; v != parent[v]; v = parent[v]) {
            path.push_back(v);
        }
        path.push_back(src);
        path.push_back(dist[end]);
        reverse(path.begin(), path.end());
        for (int index = 1; index < path.size(); index++) {
            path[index]++;
        }

        return path;
    }
};
```

---
*Documentation generated on 2025-08-02 11:17:22*
