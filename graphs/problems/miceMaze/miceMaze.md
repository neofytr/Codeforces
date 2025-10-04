# miceMaze

```markdown
# Mice Maze Problem Solution Analysis

This document provides a comprehensive analysis of the provided C++ code that solves the "Mice Maze" problem on SPOJ (Sphere Online Judge).

## 1. Problem Description

The problem, available at [https://www.spoj.com/problems/MICEMAZE/](https://www.spoj.com/problems/MICEMAZE/), can be described as follows:

Given a maze represented as a directed graph with `n` nodes, `e` the exit node, and a time limit `t`, find the number of mice that can reach the exit within the given time limit. The graph represents the connections between cells in the maze, with edges having associated weights representing the time it takes to travel between them. The mice start at each node and try to reach the exit. The goal is to count how many mice starting at any given node can reach the exit node `e` within time `t`.

**Input:**

*   `n`: The number of cells in the maze (nodes in the graph).
*   `e`: The exit cell (node).
*   `t`: The time limit.
*   `m`: The number of connections (edges) in the maze.
*   `m` lines, each with three integers `a`, `b`, and `w`, representing a directed edge from cell `a` to cell `b` with weight `w`.

**Output:**

*   The number of mice that can reach the exit cell `e` within time `t`.

## 2. Approach Explanation

The solution utilizes a single-source shortest path algorithm (specifically, a modified Dijkstra-like algorithm using a queue for efficiency) to compute the shortest distance from each node to the exit node `e`.  The core idea is:

1.  **Reverse the Graph:** The input graph represents the connections from a cell *to* another.  To find the shortest distance *to* the exit `e` *from* all other cells, the graph is reversed.  This allows us to start at the exit node and find the shortest path to every other node.
2.  **Shortest Path Computation:** A modified breadth-first search (BFS) with distance relaxation is performed starting from the exit node `e` on the reversed graph.  This is similar to Dijkstra's algorithm, but uses a queue instead of a priority queue.
3.  **Count Reachable Nodes:** After computing the shortest distances, the solution iterates through all nodes and counts how many have a shortest distance to the exit node `e` that is less than or equal to the given time limit `t`.

## 3. Key Insights and Algorithmic Techniques Used

*   **Graph Reversal:** The graph reversal is crucial. Instead of trying to find the shortest path *from* each node *to* the exit (which would require running Dijkstra's or BFS `n` times), reversing the graph allows us to run it once *from* the exit *to* all other nodes.
*   **Single-Source Shortest Path:**  The code implements a variant of Dijkstra's algorithm. Because edge weights are positive, Dijkstra's algorithm is applicable. Since a queue is used, it resembles BFS but includes distance relaxation. While not a true BFS (which only applies to unweighted graphs), the relaxation ensures correct distances are computed.
*   **Distance Relaxation:**  The `dist[v] > dist[x] + w` condition performs distance relaxation. If a shorter path to node `v` is found through node `x`, the distance `dist[v]` is updated, and `v` is added to the queue to propagate the update to its neighbors.
*   **Optimization (Queue):** The use of a simple queue instead of a priority queue is based on the fact that the problem is not too large. If `n` and `m` were very large, a priority queue based Dijkstra might perform better in certain cases, although in practice, this variant often gives good performance.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Graph Reversal: O(m)
    *   Shortest Path Computation: In the worst case, each edge can be processed multiple times. The time complexity of the main loop is O(m * V)  where V is the number of vertices, `n`. Using a priority queue would reduce this to O(m log n).
    *   Counting Reachable Nodes: O(n)
    *   Overall: approximately O(n*m) in the worst case, though likely faster in practice.
*   **Space Complexity:**
    *   `graph`: O(m) to store the adjacency list representation of the graph.
    *   `dist`: O(n) to store the shortest distances from the exit node to each node.
    *   `que`: O(n) in the worst case (when all nodes are in the queue).
    *   Overall: O(n + m)

## 5. Important Code Patterns or Tricks Used

*   **`#define int long long`:** This macro is used to avoid integer overflow issues when dealing with large numbers.  It changes the default `int` type to `long long`.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** These lines are used to optimize input/output operations in C++.  They disable synchronization between C's standard input/output streams and C++'s standard input/output streams and untie `cin` from `cout`, which can significantly improve performance, especially for problems with a lot of input and output.
*   **`for (auto &[v, w] : graph[x])`:**  This uses structured bindings (C++17) to iterate through the neighbors of node `x` and their associated edge weights in a concise manner.
*   **`LLONG_MAX`:** This is the maximum value for `long long`, used to initialize distances as "infinity."

## 6. Any Edge Cases Handled

*   **Unreachable Nodes:** Nodes that are not reachable from the exit node will have a distance of `LLONG_MAX`, which will automatically be excluded from the count of reachable mice because `LLONG_MAX > t`.
*   **Initialization:** Correctly initializing the distance array to `LLONG_MAX` ensures that the shortest path algorithm correctly updates the distances.
*   **Exit Node:** The exit node's distance is initialized to 0, which is crucial for the shortest path algorithm to start correctly.

In summary, this solution demonstrates an efficient use of graph reversal and a modified Dijkstra's algorithm using a queue to solve the Mice Maze problem. The code is well-structured, optimized for performance, and handles potential edge cases correctly.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: miceMaze
// URL: https://www.spoj.com/problems/MICEMAZE/
// Difficulty: hard
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, e, t;
    cin >> n >> e >> t;

    vector<vector<pair<int, int>>> graph(n + 1);

    int m;
    cin >> m;
    int a, b, w;
    while(m--) {
        cin >> a >> b >> w;
        graph[b].push_back({a, w}); // reverse the graph
    }    

    vector<int> dist(n + 1, LLONG_MAX);
    queue<int> que;

    dist[e] = 0;
    que.push(e);
    while(!que.empty()) {
        int x = que.front();
        que.pop();

        for (auto &[v, w] : graph[x])
            if (dist[v] > dist[x] + w)
                dist[v] = dist[x] + w, que.push(v);
    }

    int cnt = 0;
    for (int node = 1; node <= n; node++)
        if (dist[node] <= t)
            cnt++;
    cout << cnt << endl;
    return 0;
}
```

---
*Documentation generated on 2025-10-04 20:09:12*
