# numDest

```markdown
## Documentation: Number of Ways to Arrive at Destination

This document provides a detailed analysis of the provided C++ code, which solves the "Number of Ways to Arrive at Destination" problem on LeetCode.

**1. Problem Description**

The problem, accessible at [https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/description/](https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/description/), asks to find the number of shortest paths from city 0 to city `n-1` in a given graph. The graph is represented by a list of roads, where each road connects two cities with a specific travel time. The goal is to return the number of shortest paths modulo `10^9 + 7`.

**2. Approach Explanation**

The solution employs Dijkstra's algorithm to find the shortest paths from the source (city 0) to all other cities. It maintains two key data structures:

*   `dist`: A vector storing the shortest distance from the source to each city. Initialized with `LLONG_MAX` for all cities except the source, which is initialized to 0.
*   `paths`: A vector storing the number of shortest paths from the source to each city.  Initialized with 0 for all cities except the source, which is initialized to 1.

The algorithm iterates through the cities, maintaining a min-heap (`set` in the code) containing cities sorted by their current shortest distance from the source.  For each city `node` extracted from the heap, the algorithm examines its neighbors `v`.

*   **Case 1: A shorter path is found:** If the distance to `v` through `node` (i.e., `dist[node] + weight(node, v)`) is less than the current shortest distance to `v` (`dist[v]`), then we've discovered a shorter path. We update `dist[v]` to this new shorter distance, reset the number of paths to `v` to be the same as the number of paths to `node` (`paths[v] = paths[node]`), and add `v` to the heap (or update its position if it's already there, as the `set` implicitly handles updates based on the `dist` value).

*   **Case 2: An equally short path is found:** If the distance to `v` through `node` is equal to the current shortest distance to `v`, then we've found another shortest path.  We increment the number of paths to `v` by the number of paths to `node` (`paths[v] = (paths[v] + paths[node]) % MOD`). The modulo operation (`% MOD`) is crucial to prevent integer overflow.

Finally, the algorithm returns the number of shortest paths to the destination city (`paths[dst]`).

**3. Key Insights and Algorithmic Techniques Used**

*   **Dijkstra's Algorithm:** The core of the solution is Dijkstra's algorithm, which efficiently finds the shortest paths in a weighted graph with non-negative edge weights.
*   **Min-Heap (Priority Queue):** The `set` data structure is used as a min-heap to efficiently select the city with the smallest distance from the source in each iteration.  Using a `set` instead of a `priority_queue` allows for efficient element updates (removal and re-insertion with the updated distance), although at a potentially higher constant factor.
*   **Dynamic Programming:** The `paths` vector can be viewed as a form of dynamic programming. `paths[i]` stores the number of shortest paths to city `i`, and this value is built upon the number of shortest paths to its neighbors with shorter distances.
*   **Modulo Arithmetic:** The use of modulo arithmetic (`% MOD`) is essential to prevent integer overflow when calculating the number of paths, as the number of paths can become very large.
*   **Adjacency List Representation:** The graph is represented using an adjacency list (`graph`), which is efficient for sparse graphs where the number of edges is much smaller than the number of possible edges.

**4. Time and Space Complexity Analysis**

*   **Time Complexity:**
    *   Constructing the graph takes O(E) time, where E is the number of roads.
    *   Dijkstra's algorithm with a `set` typically has a time complexity of O((V + E) log V), where V is the number of cities. In the worst case where E = V^2 this becomes O(E log V).  The set insertions and deletions dominate the complexity.
    *   Overall: O(E + (V + E) log V) which simplifies to O((V+E)logV).

*   **Space Complexity:**
    *   `graph`: O(E) to store the adjacency list.
    *   `dist`: O(V) to store the shortest distances.
    *   `paths`: O(V) to store the number of paths.
    *   `heap`: O(V) in the worst case.
    *   Overall: O(V + E).

**5. Important Code Patterns or Tricks Used**

*   **`typedef pair<long long, long long> edge;`:** This creates an alias for a pair of `long long` integers, used to represent edges in the graph (destination node, weight).  This improves readability.
*   **`auto [di, node] = *(heap.begin());`:**  This uses structured bindings (C++17 feature) to unpack the first element of the `set` (which is the city with the smallest distance) into the `di` (distance) and `node` variables.
*   **Using `set` as a priority queue with updates:** The code cleverly uses `std::set` as a priority queue that also allows efficient updating of priorities. When a shorter distance to a node is found, the node is effectively removed and re-inserted into the `set` with the updated distance. `std::priority_queue` doesn't offer direct update capability, making `set` a suitable alternative in this specific case.  However, it is important to remember that `set` operations usually have a higher constant factor than `priority_queue`.
*   **Using `LLONG_MAX`:** Using `LLONG_MAX` from `<climits>` for initializing `dist` ensures a large enough initial distance, which is crucial for Dijkstra's algorithm to function correctly.

**6. Edge Cases Handled**

*   **Disconnected Graph (Implicit):** If the destination city is not reachable from the source city, Dijkstra's algorithm will never visit the destination, and `paths[dst]` will remain 0 (the initial value).
*   **Source equals destination:** The solution correctly handles the case where the source is equal to the destination since `paths[0]` is initialized to 1, and the loop will not be entered if `n` is equal to 1.
*   **Non-negative edge weights:** Dijkstra's algorithm is guaranteed to work correctly only with non-negative edge weights. The problem statement implicitly enforces this constraint.
*   **Integer Overflow:** The modulo operation (`% MOD`) is crucial to handle the potentially large number of paths and prevents integer overflow.

**Summary of Learning Points**

*   This problem demonstrates the practical application of Dijkstra's algorithm for finding shortest paths in a graph.
*   It highlights the importance of choosing appropriate data structures (e.g., min-heap) to optimize algorithm performance.
*   It showcases how dynamic programming principles can be used in conjunction with graph algorithms to solve complex problems.
*   It emphasizes the need for careful attention to potential integer overflows and the use of modulo arithmetic to prevent them.
*   The use of a `set` as a priority queue with updates demonstrates a useful, albeit potentially less performant compared to specialized priority queues, trick for implementing Dijkstra's algorithm.


## Original Code
```cpp
#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

// Problem: numDest
// URL: https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/description/
// Difficulty: hard
// Tags:
// Strategy:

#define MOD 1000000007

typedef pair<long long, long long> edge;
class Solution {

  public:
    int countPaths(int n, vector<vector<int>> &roads) {
        long long size = (long long)roads.size();
        vector<long long> paths(n, 0); // paths[r] is the number of shortest paths from src to r
        vector<long long> dist(n, LLONG_MAX);
        set<edge> heap;
        vector<vector<edge>> graph(n);

        for (long long index = 0; index < size; index++) {
            vector<int> &road = roads[index];
            long long u = road[0];
            long long v = road[1];
            long long w = road[2];
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }

        long long src = 0, dst = n - 1;
        paths[src] = 1;
        dist[src] = 0;
        heap.insert({dist[src], src});

        while (!heap.empty()) {
            auto [di, node] = *(heap.begin());
            heap.erase(heap.begin());

            for (auto &[v, w] : graph[node]) {
                if (di + w < dist[v]) {
                    paths[v] = paths[node];
                    dist[v] = w + di;
                    heap.insert({dist[v], v});
                } else if (di + w == dist[v]) {
                    paths[v] = (paths[v] + paths[node]) % MOD;
                }
            }
        }

        return paths[dst];
    }
};

#undef MOD
```

---
*Documentation generated on 2025-08-03 20:42:52*
