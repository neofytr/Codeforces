# shortestPathInDAG

```markdown
## Shortest Path in a Directed Acyclic Graph (DAG)

This document provides a detailed explanation of a C++ solution for finding the shortest path from a source node (node 0) to all other nodes in a Directed Acyclic Graph (DAG). The problem is based on the "Shortest path in Directed Acyclic Graph" problem available on GeeksforGeeks: [https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph/1](https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph/1).  While the URL mentions "undirected graph," the code solves the directed version as specified in the problem description of the linked page.

### 1. Problem Description

Given a DAG represented by a list of edges, where each edge `(u, v, w)` indicates a directed edge from node `u` to node `v` with weight `w`, find the shortest path from source node 0 to all other nodes in the graph. If a node is unreachable from the source, its shortest distance should be represented as -1.

### 2. Approach Explanation

The solution utilizes the following steps:

1.  **Graph Representation:** The input edges are used to construct an adjacency list representation of the DAG. Each element `graph[u]` contains a vector of pairs `(v, w)`, indicating a directed edge from node `u` to node `v` with weight `w`.

2.  **Topological Sort:** A topological sort of the DAG is performed using Depth-First Search (DFS). A stack `st` is used to store the nodes in reverse topological order.  This is crucial because processing nodes in topological order ensures that when we're calculating shortest paths, we've already considered all possible paths leading *to* the current node.

3.  **Shortest Path Calculation:** After obtaining the topological order, the algorithm iterates through the nodes in the stack. It maintains a `dist` vector to store the shortest distance from the source node to each node.  It initializes all distances to `INT_MAX`.  The following key logic applies:

    *   If a node is encountered *before* the source node in the topological order, its distance is set to -1, indicating that it is unreachable from the source (0).  This is implemented via the `found` flag.
    *   For each node, the algorithm iterates through its neighbors and updates the shortest distance to each neighbor. If the distance to a neighbor can be reduced by going through the current node, the `dist` vector is updated using the formula: `dist[v] = min(dist[v], dist[node] + w)`.

4.  **Return Value:**  The `dist` vector, containing the shortest distances from the source node to all other nodes, is returned. Nodes unreachable from the source have a distance of -1.

### 3. Key Insights and Algorithmic Techniques Used

*   **Topological Sort:** Topological sort is a fundamental algorithm for DAGs.  It allows us to process nodes in an order such that all dependencies of a node are processed before the node itself. This makes it ideal for shortest path problems in DAGs because we can guarantee that we've considered all possible paths to a node before calculating its shortest distance.
*   **Relaxation:** The core of the shortest path algorithm is the relaxation step. This step checks if the current shortest distance to a node can be improved by going through another node. This technique forms the basis for many shortest path algorithms.
*   **DAG Property:** This solution exploits the property of DAGs that there are no cycles. This guarantees that the shortest path algorithm will converge, as there is no possibility of infinitely decreasing the distance due to a negative weight cycle.  The topological sort is only possible on a DAG.
*   **Initialization:** Initializing the `dist` vector to `INT_MAX` is essential.  It ensures that the relaxation step correctly updates the shortest distances.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   DFS for topological sort: O(V + E)
    *   Iterating through the topological order and relaxing edges: O(V + E)
    *   Total Time Complexity: **O(V + E)**, where V is the number of vertices and E is the number of edges.

*   **Space Complexity:**
    *   `graph`: O(V + E) to store the adjacency list.
    *   `vis`: O(V) for visited nodes during topological sort.
    *   `st`: O(V) to store the topological order.
    *   `dist`: O(V) to store the shortest distances.
    *   Total Space Complexity: **O(V + E)**

### 5. Important Code Patterns or Tricks Used

*   **Adjacency List Representation:** Using an adjacency list to represent the graph is efficient for sparse graphs (graphs with relatively few edges compared to the number of vertices).
*   **Pair for Edge Representation:** Storing edges as pairs `(neighbor, weight)` in the adjacency list makes it easy to access both the neighbor node and the edge weight.
*   **Stack for Topological Order:** The stack data structure is used naturally in DFS to maintain the reverse topological order of the graph's nodes.
*   **INT_MAX Initialization:**  Initializing distances to `INT_MAX` facilitates the relaxation process, as any finite distance will be smaller.
*   **`found` flag for unreachability**: Using the `found` flag simplifies the determination and handling of unreachable nodes. It ensures only the vertices from the source vertex and beyond in the topological order are processed.
### 6. Edge Cases Handled

*   **Unreachable Nodes:** The `found` flag and the initial `INT_MAX` initialization of the `dist` vector handle unreachable nodes.  If a node remains at `INT_MAX` after the shortest path calculation, it is guaranteed to be unreachable from the source, and will be set to -1.
*   **Source Node Not Present:** The initial part of the `while(!st.empty())` loop effectively skips processing any node that comes *before* the source in the topological sort, ensuring they are set to -1 (unreachable).
*   **DAG Guarantee:** This solution explicitly relies on the input being a DAG. It does *not* handle cycles. If the graph had cycles, topological sort would not be possible, and the algorithm would likely enter an infinite loop or produce incorrect results. No specific error handling exists for non-DAG input.


## Original Code
```cpp
#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

// Problem: shortestPathInDAG
// URL: https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph/1
// Difficulty: easy
// Tags:
// Strategy:

class Solution {
  private:
    void dfs(int node, vector<bool> &vis, stack<int> &st, vector<vector<pair<int, int>>> &graph) {
        vis[node] = true;
        for (auto elt : graph[node]) {
            int v = elt.first;
            if (!vis[v]) {
                dfs(v, vis, st, graph);
            }
        }
        st.push(node);
        return;
    }

  public:
    vector<int> shortestPath(int V, int E, vector<vector<int>> &edges) {
        vector<int> dist(V, INT_MAX);
        int source = 0;
        vector<vector<pair<int, int>>> graph(V);
        for (int edge = 0; edge < E; edge++) {
            int a = edges[edge][0];
            int b = edges[edge][1];
            int w = edges[edge][2];
            graph[a].push_back({b, w});
        }

        // do a topo sort
        stack<int> st;
        vector<bool> vis(V, false);
        for (int node = 0; node < V; node++) {
            if (!vis[node])
                dfs(node, vis, st, graph);
        }

        bool found = false;
        while (!st.empty()) {
            int node = st.top();
            st.pop();
            if (node == source) {
                found = true;
            }
            if (!found) {
                dist[node] = -1;
                continue;
            }

            for (auto elt : graph[node]) {
                int v = elt.first;
                int w = elt.second;
                dist[v] = min(dist[v], dist[node] + w);
            }
        }

        return dist;
    }
};

```

---
*Documentation generated on 2025-07-30 13:33:43*
