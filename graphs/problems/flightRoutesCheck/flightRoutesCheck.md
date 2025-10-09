# flightRoutesCheck

```markdown
# Flight Routes Check Solution Documentation

This document describes the solution to the "Flight Routes Check" problem, which can be found on the CSES problemset ([https://cses.fi/problemset/task/1682](https://cses.fi/problemset/task/1682)).

## 1. Problem Description

The "Flight Routes Check" problem asks whether a given directed graph is strongly connected.  More specifically, given a directed graph with *n* nodes and *m* edges, the task is to determine if it's possible to travel from any node to any other node in the graph.  If the graph is not strongly connected, the program should output "NO" and provide two nodes *a* and *b* such that it's not possible to travel from *a* to *b*. If the graph is strongly connected, the program should output "YES".

## 2. Approach Explanation

The core idea is to check if it's possible to reach all nodes from a chosen source node and if the chosen source node can be reached from all other nodes. If both conditions are met, the graph is strongly connected.  The solution leverages two Depth-First Searches (DFS) or Breadth First Searches (BFS) to achieve this.

1. **Forward Traversal:**  Starting from an arbitrary source node (here, node 1 is chosen as the source), perform a traversal (either DFS or BFS) to identify all reachable nodes.  This utilizes the original directed graph.

2. **Reverse Traversal:** Construct the reverse graph, where the direction of each edge is flipped. Again, starting from the same source node (node 1), perform a traversal on the reverse graph to identify all nodes that can reach the source node.

3. **Connectivity Check:**  If all nodes are reachable from the source and the source is reachable from all nodes, the graph is strongly connected. Otherwise, find a pair of nodes that violate the strong connectivity condition and output them. If a node *u* is not reachable from the source in the original graph, it means you can't get from the source to *u*.  If a node *v* cannot reach the source in the original graph (which means it's not reachable from the source in the reverse graph), it means you can't get from *v* to the source.

## 3. Key Insights and Algorithmic Techniques Used

*   **Strong Connectivity:** The concept of strong connectivity is fundamental. A directed graph is strongly connected if, for every pair of vertices *u* and *v*, there is a path from *u* to *v* and a path from *v* to *u*.

*   **Reversed Graph:** Constructing the reversed graph is crucial. It allows us to efficiently determine all nodes that can reach a specific source node.  This avoids performing separate reachability checks from every node to the source.

*   **DFS/BFS for Reachability:**  Both DFS and BFS are efficient algorithms for exploring a graph and determining the set of reachable nodes from a given starting point.  The provided solution uses BFS to explore the graphs. DFS could also be used, as illustrated in the commented out `dfs` function.

*   **Arbitrary Source Node:**  The choice of the starting node is arbitrary. If it turns out that node 1 cannot reach every node and every node cannot reach node 1, then the algorithm will correctly identify a violating pair.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Building the graph and the reversed graph takes O(m) time, where *m* is the number of edges.
    *   The two traversals (BFS or DFS) each take O(n + m) time, where *n* is the number of nodes.
    *   The final loop to check for unconnected nodes takes O(n) time.
    *   Therefore, the overall time complexity is **O(n + m)**.

*   **Space Complexity:**
    *   The `graph` and `revGraph` vectors take O(n + m) space to store the adjacency lists.
    *   The `vis` and `revVis` vectors take O(n) space to track visited nodes.
    *   The `que` in BFS takes, at worst, O(n) space.
    *   Therefore, the overall space complexity is **O(n + m)**.

## 5. Important Code Patterns or Tricks Used

*   **Using Adjacency Lists:** The solution uses adjacency lists to represent the directed graph, which is an efficient way to store sparse graphs (graphs where the number of edges is much smaller than *n*<sup>2</sup>).

*   **Direct Output on Failure:**  The code immediately outputs "NO" and the violating node pair as soon as it finds one. This avoids unnecessary computation after detecting that the graph is not strongly connected.

*   **Using `std::queue` for BFS:** The code utilizes `std::queue` for implementing breadth-first search, demonstrating a standard C++ library usage pattern.

## 6. Any Edge Cases Handled

*   **Disconnected Graph:** The code explicitly handles the case where the graph is not strongly connected. It identifies and outputs a pair of nodes (*a*, *b*) such that there is no path from *a* to *b*.
*   **Empty Graph:** While not explicitly handled, if *m* is 0, the code will still function correctly.  If *n* is 1, the graph is trivially strongly connected.  If *n* > 1 and *m* = 0, the code will correctly identify a pair of unconnected nodes (1, 2).
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: flightRoutesCheck
// URL: https://cses.fi/problemset/task/1682
// Difficulty: medium
// Tags: 
// Strategy: 

void dfs(int x, vector<bool> &vis, vector<vector<int>> &graph) {
    vis[x] = true;

    for (int v : graph[x])
        if (!vis[v])
            dfs(v, vis, graph);
}

int32_t main() {
    int n, m;
    cin >> n >> m;

    int u, v;
    vector<vector<int>> graph(n + 1);
    vector<vector<int>> revGraph(n + 1);
    while(m--)
        cin >> u >> v, graph[u].push_back(v), revGraph[v].push_back(u);

    int src = 1;
    // We want to find all the nodes in the SCC of src
    vector<int> vis(n + 1, false), revVis(n + 1, false);
    queue<int> que;

    que.push(src);
    vis[src] = true;
    while(!que.empty()) {
        int x = que.front();
        que.pop();

        for (int v : graph[x])
            if (!vis[v])
                vis[v] = true, que.push(v);
    }

    que.push(src);
    revVis[src] = true;
    while(!que.empty()) {
        int x = que.front();
        que.pop();

        for (int v : revGraph[x])
            if (!revVis[v])
                revVis[v] = true, que.push(v);
    }

    for (int node = 1; node <= n; node++) {
        if (!revVis[node]) {
            cout << "NO\n";
            cout << node << " " << src << "\n";
            return 0;
        }
        if (!vis[node]) {
            cout << "NO\n";
            cout << src << " " << node << "\n";
            return 0;
        }
    }
        

    cout << "YES\n";
    return 0;
}
```

---
*Documentation generated on 2025-10-09 13:09:31*
