# shortestPathInDAG

```markdown
## Shortest Path in a Directed Acyclic Graph (DAG)

### 1. Problem Description

The problem, as indicated by the inline comments and URL (`https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph/1`), requires finding the shortest path from a source node (node 0) to all other nodes in a given Directed Acyclic Graph (DAG). The graph is represented by a list of edges, where each edge has a source node, a destination node, and a weight. The goal is to return a vector containing the shortest distance from the source node (0) to each other node. If a node is unreachable from the source, its distance should be represented as -1 in the output vector. Note that the problem description on GeeksforGeeks uses the term 'undirected graph', but the solution implemented here correctly finds shortest paths in a DAG.

### 2. Approach Explanation

The solution utilizes a combination of Topological Sort and Distance Relaxation to find the shortest paths in the DAG. The main steps are:

1.  **Graph Construction:** The input `edges` vector is used to construct an adjacency list representation of the graph, where each node stores a list of its adjacent nodes along with the corresponding edge weights.

2.  **Topological Sort:** A Depth-First Search (DFS) based topological sort is performed on the graph. The `dfs` function recursively visits all reachable nodes from a given node, marking them as visited. After exploring all adjacent nodes, the current node is pushed onto a stack (`st`). This ensures that nodes are added to the stack in reverse topological order.

3.  **Distance Initialization:** A `dist` vector is initialized with `INT_MAX` for all nodes, representing infinite distance from the source. The `source` node (node 0) is the starting point for finding shortest paths.

4.  **Distance Relaxation:** The algorithm iterates through the nodes in the order provided by the topological sort (popping nodes from the `st` stack).  For each node, it relaxes the distances to its adjacent nodes.  Relaxation means checking if the distance to an adjacent node can be reduced by going through the current node.  If `dist[v] > dist[node] + w`, where `v` is an adjacent node, `w` is the weight of the edge between `node` and `v`, then `dist[v]` is updated to `dist[node] + w`.

5.  **Unreachable Nodes:** A crucial optimization is present to handle unreachable nodes from the source node. During the processing of the topological order, the algorithm uses a boolean `found` to track if the source node (0) has been encountered. Before the source node is reached, all distances remain at `INT_MAX`. Nodes that appear in the topological sort before the source are automatically marked as unreachable (distance -1) since there's no path *from* the source *to* them. This cleverly leverages topological order to identify and handle unreachable nodes efficiently.

6.  **Result:** The `dist` vector, now containing the shortest distances from the source to all nodes, is returned. Distances that remain `INT_MAX` after the relaxation step indicate that the corresponding nodes are unreachable from the source. They are implicitly kept as `INT_MAX`, but the unreachable nodes logic above sets some to -1 even before any distance relaxations.

### 3. Key Insights and Algorithmic Techniques Used

*   **Topological Sort:**  Topological sort is a fundamental algorithm for DAGs.  It provides an ordering of nodes such that for every directed edge `u -> v`, node `u` comes before node `v` in the ordering. This ordering is crucial for processing nodes in a way that allows distances to be correctly relaxed.

*   **Distance Relaxation:**  Distance relaxation is a core concept in shortest path algorithms.  It iteratively updates the estimated shortest distances until the optimal distances are found. The topological sort ensures that when relaxing the distance to a node, the distances to all its predecessors have already been finalized.

*   **DAG Property:** The algorithm leverages the property of DAGs that shortest paths are well-defined and can be found efficiently using dynamic programming (through relaxation) along the topological order.  No negative cycles exist in a DAG, eliminating the need for more complex algorithms like Bellman-Ford.

*   **Handling Unreachable Nodes:** The `found` flag and the logic of setting distances to -1 *before* the source node is encountered in the topological sort is a smart and efficient way to handle nodes that are not reachable from the source. This avoids the need for a separate post-processing step to identify unreachable nodes based on distances remaining as `INT_MAX`.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Graph Construction: O(E), where E is the number of edges.
    *   Topological Sort: O(V + E), where V is the number of vertices and E is the number of edges.  The DFS traversal visits each node and edge once.
    *   Distance Relaxation: O(V + E). We iterate through each node in the topological order (O(V)) and relax the distances to its neighbors (O(E) in total across all nodes).
    *   Overall: O(V + E).

*   **Space Complexity:**
    *   `graph`: O(V + E) to store the adjacency list.
    *   `vis`: O(V) for the visited array in DFS.
    *   `st`: O(V) for the stack used in topological sort.
    *   `dist`: O(V) to store the shortest distances.
    *   Overall: O(V + E).

### 5. Important Code Patterns or Tricks Used

*   **Adjacency List Representation:**  Using an adjacency list to represent the graph is efficient for sparse graphs (graphs with relatively few edges).

*   **Pair<int, int> for Weighted Edges:** Using `pair<int, int>` to represent edges allows storing both the destination node and the weight associated with the edge in the adjacency list.

*   **Stack for Topological Sort:**  Using a stack to store the nodes in reverse topological order is a common technique in topological sort implementations.

*   **INT_MAX for Infinity:**  Using `INT_MAX` to represent infinity for initial distances is a standard practice in shortest path algorithms.

*   **Early Unreachable Node Marking:** Marking unreachable nodes before processing the source node by inspecting the topological sort order is an elegant optimization.

### 6. Edge Cases Handled

*   **Unreachable Nodes:** As described above, the solution explicitly handles nodes unreachable from the source node by marking their distances as -1.

*   **DAG Property:** Although not explicitly checked, the algorithm assumes that the input graph is a DAG. It will not work correctly if the graph contains cycles.

*   **Source Node Only:** If the source node is the only node in the graph, or if all other nodes are unreachable, the distances will be handled correctly; unreachable nodes will have a distance of -1, and the source will have a distance of 0.

```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <climits>
#include <queue>
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
            if (!found && node != source) {
                dist[node] = -1;
                continue;
            }
            if (node == source) {
                found = true;
                dist[node] = 0;
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
*Documentation generated on 2025-07-30 13:12:58*
