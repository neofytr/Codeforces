# findTheCity

```markdown
## Documentation: Find the City With the Smallest Number of Neighbors at a Threshold Distance

This document provides a comprehensive analysis of the provided C++ code, which solves the "Find the City With the Smallest Number of Neighbors at a Threshold Distance" problem on LeetCode ([https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/description/](https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/description/)).

### 1. Problem Description

Given `n` cities numbered from `0` to `n-1`, and a list of bidirectional edges `edges` where `edges[i] = [ui, vi, weighti]` represents a bidirectional edge between cities `ui` and `vi` with weight `weighti`. Also, given an integer `distanceThreshold`.  The distance between two cities is defined as the length of the shortest path between them.

The task is to find the city that has the smallest number of cities reachable from it within the `distanceThreshold`. If there are multiple such cities, return the city with the greatest number.

### 2. Approach Explanation

The code implements the following steps:

1.  **Build the Graph:** Construct an adjacency list representation of the graph from the given `edges`.  Each city is a node, and each edge is a connection between two nodes with a specific weight. The graph is undirected, meaning edges are bidirectional.

2.  **Iterate Through Cities (Source Nodes):** For each city from `0` to `n-1`, treat it as the source node and calculate the shortest distances to all other cities using Dijkstra's algorithm.

3.  **Dijkstra's Algorithm:** For each source city:
    *   Initialize a `dist` vector to store the shortest distances from the source city to all other cities. Initially, all distances are set to `INT_MAX`.
    *   Use a `set` (implemented as a min-heap with custom comparator) called `heap` to efficiently extract the node with the smallest distance.  The `heap` stores pairs of `(distance, city_index)`.
    *   The main loop of Dijkstra's algorithm continues as long as the heap is not empty. In each iteration, it extracts the node with the smallest distance from the heap, explores its neighbors, and updates their distances if a shorter path is found. The comparator `cmp` within the set ensures cities with smaller number of reachable neighbors are preferred and among neighbors, the one with the higher number is returned.
    *   If a shorter path to a neighbor `v` is found (i.e., `dist[x] + w < dist[v]` ) AND the distance to that neighbor is within the `distanceThreshold` (i.e. `dist[x] + w <= distanceThreshold`), update `dist[v]` and insert the updated distance and node into the heap.

4.  **Count Reachable Cities:** After running Dijkstra's algorithm for a source city, iterate through the `dist` vector and count the number of cities reachable from the source city within the `distanceThreshold` (i.e., where `dist[node] != INT_MAX`).

5.  **Store Results:** Store the number of reachable cities and the corresponding city index in a `set` called `ans`. The custom comparator `cmp` in the `set` ensures that the city with the smallest number of reachable neighbors is at the beginning of the set. If two cities have the same number of reachable cities, the city with the larger index is prioritized.

6.  **Return Result:** Return the city index of the first element in the `ans` set. This will be the city with the smallest number of reachable neighbors (and largest index if there's a tie).

### 3. Key Insights and Algorithmic Techniques Used

*   **Dijkstra's Algorithm:**  This is a fundamental algorithm for finding the shortest paths from a single source node to all other nodes in a weighted graph.  Its efficiency relies on using a priority queue (in this case, a `set`) to efficiently extract the node with the smallest distance in each iteration.
*   **Adjacency List Representation:** Using an adjacency list to represent the graph is efficient for sparse graphs, as it only stores the connections that exist.
*   **Custom Comparator for the Priority Queue:**  The `cmp` struct defines a custom comparator for the `set`.  This allows us to prioritize nodes based on their distance from the source node *and* break ties based on the city index to satisfy the requirement in the problem that in case of ties, the city with the largest index is chosen.
*   **Set for Automatic Sorting and Tie-Breaking:** The `set` data structure is used with the custom comparator `cmp` to maintain a sorted list of reachable city counts and their corresponding city indices.  This simplifies the process of finding the city with the smallest number of reachable neighbors.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Building the graph: O(E), where E is the number of edges.
    *   Outer loop iterating through all cities (source nodes): O(N), where N is the number of cities.
    *   Dijkstra's algorithm within each iteration: O((N + E) log N). In this problem, since we're exploring and potentially inserting each node into the heap, the time complexity for Dijkstra's is O(E log N) as E is generally greater than N.
    *   Counting reachable cities: O(N) within each iteration of the outer loop.
    *   Overall time complexity: O(N * (E log N + N)) =  O(N * E log N) in the worst case.  Note that E can be O(N^2) in a dense graph, in which case the complexity becomes O(N^3 log N).

*   **Space Complexity:**
    *   Graph (adjacency list): O(E)
    *   `dist` vector: O(N)
    *   `heap` (priority queue): O(N) in the worst case.
    *   `ans` set: O(N)
    *   Overall space complexity: O(E + N) = O(N^2) in the worst case (dense graph)

### 5. Important Code Patterns or Tricks Used

*   **Using `std::set` as a Min-Heap with a Custom Comparator:**  This is a common technique in C++ competitive programming for implementing priority queues.  The custom comparator allows for more flexible prioritization rules. In this case, the custom comparator orders nodes based on the shortest distance calculated by Dijkstra's algorithm and when distances are equal, picks the city with the larger index.
*   **`auto &[v, w] : graph[x]`**: Using structured bindings (C++17) to concisely iterate through the neighbors and weights of a node. This makes the code more readable.
*   **Initialization with `INT_MAX`:** Initializing the `dist` vector with `INT_MAX` is a common pattern for representing "infinity" in shortest-path algorithms. It ensures that any actual path will be shorter than the initial "infinite" distance.

### 6. Edge Cases Handled

*   **Disconnected Graph:** The algorithm correctly handles disconnected graphs. Cities that are unreachable from the source city will have a distance of `INT_MAX` in the `dist` vector and will not be counted as reachable neighbors.
*   **Zero-Weight Edges:**  The algorithm correctly handles zero-weight edges. Dijkstra's algorithm works correctly even with zero-weight edges.
*   **Ties for the Smallest Number of Neighbors:**  The custom comparator in the `set` `ans` ensures that if multiple cities have the same number of neighbors within the `distanceThreshold`, the city with the largest index will be selected. This fulfills the problem requirement.
*   **All nodes are reachable:** If all nodes are reachable from a source within `distanceThreshold`, the algorithm counts `n-1` reachable cities (excluding itself). The comparison is `node != src`, which prevents counting the source city as a neighbor.

```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

// Problem: findTheCity
// URL: https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/description/
// Difficulty: medium
// Tags:
// Strategy:

struct cmp {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) const {
        if (a.first != b.first)
            return a.first < b.first; // ascending by the first element
        else
            return a.second > b.second; // descending by the first
    }
};

class Solution {
  public:
    int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold) {
        vector<vector<pair<int, int>>> graph(n);
        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }

        set<pair<int, int>, cmp> ans;
        for (int src = 0; src < n; src++) {
            vector<int> dist(n, INT_MAX);
            set<pair<int, int>> heap;

            dist[src] = 0;
            heap.insert({dist[src], src});
            while (!heap.empty()) {
                auto [d, x] = *heap.begin();
                heap.erase(heap.begin());

                for (auto &[v, w] : graph[x]) {
                    if (dist[x] + w < dist[v] && dist[x] + w <= distanceThreshold) {
                        dist[v] = dist[x] + w;
                        heap.insert({dist[v], v});
                    }
                }
            }

            int count = 0;
            for (int node = 0; node < n; node++) {
                if (node != src && dist[node] != INT_MAX) {
                    count++;
                }
            }

            ans.insert({count, src});
        }

        return (ans.begin())->second;
    }
};
```

---
*Documentation generated on 2025-08-04 20:06:35*
