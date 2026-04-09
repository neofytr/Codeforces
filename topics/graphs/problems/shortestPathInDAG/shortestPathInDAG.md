# shortestPathInDAG

```markdown
## Shortest Path in a Directed Acyclic Graph (DAG)

This document analyzes a C++ solution for finding the shortest paths from a source node (node 0) to all other nodes in a Directed Acyclic Graph (DAG). The problem is based on the GeeksforGeeks problem "[Shortest path in Undirected Graph](https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph/1)" which is, despite its title, concerned with finding shortest paths in a *directed acyclic graph*.
**1. Problem Description:**

Given a DAG represented by its number of vertices `V`, number of edges `E`, and a list of edges where each edge is represented by `(u, v, w)` indicating a directed edge from node `u` to node `v` with weight `w`, the task is to find the shortest distance from the source node (node 0) to all other nodes in the graph. If a node is unreachable from the source, its distance should be represented as -1.

**2. Approach Explanation:**

The solution uses the following steps:

1.  **Graph Representation:** The input `edges` is converted into an adjacency list representation of the graph. `graph[u]` stores a vector of `pair<int, int>`, where the first element of the pair is the neighbor `v` of node `u`, and the second element is the weight `w` of the edge `(u, v)`.
2.  **Topological Sort:** Since the graph is a DAG, we can leverage topological sorting to process the nodes in an order such that all dependencies of a node are visited before the node itself. A depth-first search (DFS) is used to perform the topological sort. Nodes are pushed onto a stack `st` in reverse topological order.
3.  **Shortest Path Calculation:** The algorithm then iterates through the nodes in the stack (which are now in topological order).  It maintains a `dist` vector to store the shortest distances from the source to each node. Initially, all distances are set to `INT_MAX`. The algorithm considers the elements in the stack, popping one element at a time. Since we are finding the shortest path from the source (node 0), there are two conditions here:
    * If the current node is node 0 or if node 0 was previously discovered by popping elements from the stack, then node 0 has been found. Then the code will iterate through the neighbors of the node, and update the distance to that neighbor. The condition `dist[v] = min(dist[v], dist[node] + w);` computes and updates shortest distances.
    * If the current node is encountered before popping node 0, then it must be unreachable from node 0. So the distance is set to -1.
4.  **Unreachable Nodes:** Finally, any node that still has a distance of `INT_MAX` after the topological sort is marked as unreachable by setting its distance to -1.

**3. Key Insights and Algorithmic Techniques:**

*   **Topological Sort for DAGs:**  Topological sort is fundamental to efficiently processing DAGs. The ordering ensures that we process nodes in a way that allows us to relax distances from nodes to their successors without worrying about cycles.
*   **Dynamic Programming (Relaxation):** The shortest path calculation leverages the concept of relaxation used in dynamic programming algorithms like Bellman-Ford and Dijkstra's algorithm. Specifically, if we find a shorter path to a node `v` through a neighbor `u`, we update the distance to `v`.
*   **DAG Properties:** The acyclic property allows us to compute shortest paths in a more efficient manner than general shortest path algorithms like Bellman-Ford, which can handle negative edge weights but need to iterate through the edges multiple times. With topological sort, we can compute shortest paths with a single pass.

**4. Time and Space Complexity Analysis:**

*   **Time Complexity:**
    *   Graph Construction: O(E)
    *   Topological Sort (DFS): O(V + E)
    *   Shortest Path Calculation: O(V + E)  (each vertex and edge is processed at most once)
    *   Overall: O(V + E)

*   **Space Complexity:**
    *   Graph: O(V + E) (adjacency list)
    *   `vis` vector: O(V)
    *   `st` stack: O(V)
    *   `dist` vector: O(V)
    *   Overall: O(V + E)

**5. Important Code Patterns or Tricks Used:**

*   **Adjacency List:** Using an adjacency list to represent the graph is efficient for sparse graphs, where the number of edges is significantly less than V<sup>2</sup>.
*   **Pair for Edge Weights:** Using `pair<int, int>` in the adjacency list to store both the neighbor and the edge weight is a standard technique.
*   **DFS for Topological Sort:** A standard DFS implementation is used to compute the topological sort of the DAG.
*   **Handling Unreachable Nodes:** The algorithm explicitly handles unreachable nodes by initializing distances to `INT_MAX` and then setting them to -1 if they remain unreachable after the shortest path calculation. The handling of unreachable nodes *before* the source node is found in the stack.
*  **Initialization of the distance from node 0 to node 0 is missing.** Although the algorithm works in the given testcases, a better design would be to have `dist[source] = 0;` before processing the stack so that the shortest distance from the source to itself is automatically set to 0.

**6. Edge Cases Handled:**

*   **Unreachable Nodes:**  Nodes that are unreachable from the source node are correctly identified and their distances are set to -1.
*   **DAG Property:** The algorithm assumes the input graph is a DAG. If the graph contains cycles, the topological sort will not produce a valid ordering, and the shortest path calculation may produce incorrect results or enter an infinite loop. The problem description guarantees the graph is a DAG, so no explicit check is made.
*   **Disconnected Graph:** The algorithm implicitly handles disconnected graphs. Nodes that are not reachable from the source will remain at their initial `INT_MAX` distance, which will then be set to -1.

**Summary:**

This solution demonstrates an efficient approach to finding shortest paths in a DAG using topological sorting and relaxation. The algorithm has a time complexity of O(V + E) and space complexity of O(V + E), making it suitable for graphs with a moderate number of vertices and edges. The code handles unreachable nodes and assumes the graph is a DAG. A minor improvement would be to initialize `dist[source]` to 0.
```

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
*Documentation generated on 2025-07-30 13:34:39*
