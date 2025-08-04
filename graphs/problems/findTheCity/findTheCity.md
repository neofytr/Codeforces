# findTheCity

```markdown
# Problem: Find the City With the Smallest Number of Neighbors at a Threshold Distance

## 1. Problem Description

The problem, as found on LeetCode at [https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/description/](https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/description/), asks to find the city with the smallest number of reachable cities within a given distance threshold.  Given a graph representing cities and roads (edges) between them, where each road has a weight (distance), we need to determine, for each city, how many other cities are reachable within a specific `distanceThreshold`. The goal is to return the city that has the minimum number of reachable cities within that threshold.  If there are multiple cities with the same minimum number of reachable cities, return the city with the greatest city number.

## 2. Approach Explanation

The provided code contains two distinct solutions to the problem:

**Solution 1 (Dijkstra's Algorithm):**

*   **Graph Representation:** The code first builds an adjacency list `graph` to represent the network of cities.  Each element `graph[u]` is a vector of pairs, where each pair represents a neighbor `v` of city `u` and the weight `w` of the edge connecting them.
*   **Dijkstra's for Each City:**  For each city `src`, it performs Dijkstra's algorithm to find the shortest distance from `src` to all other cities.
*   **Reachability Count:** After running Dijkstra's for a given `src`, the code counts the number of cities that are reachable from `src` within the given `distanceThreshold`.
*   **Tracking the Best City:** It then keeps track of the city with the smallest count of reachable neighbors. The comparison function `cmp` in the `set` `ans` ensures that if there are ties in the number of neighbors, the city with the *larger* index is preferred, addressing the requirement that ties should be resolved by returning the largest city index.
*   **Return Result:** Finally, it returns the city index with the minimum reachable cities.

**Solution 2 (Floyd-Warshall Algorithm):**

*   **Distance Matrix:** This solution uses the Floyd-Warshall algorithm to compute the shortest distance between *every pair* of cities. It initializes a distance matrix `dist` where `dist[i][j]` represents the shortest distance from city `i` to city `j`. Initially, all distances are set to `INT_MAX`, except for the distance from a city to itself, which is set to 0. Direct edges have their distances set accordingly.
*   **Floyd-Warshall Iteration:** The core of the algorithm is three nested loops. The outer loop iterates through all possible intermediate cities (`via`). The inner loops iterate through all pairs of source and destination cities (`u` and `v`). The algorithm updates `dist[u][v]` if going from `u` to `v` via `via` results in a shorter path.
*   **Reachability Count:** After the Floyd-Warshall algorithm completes, the `dist` matrix contains the shortest distance between every pair of cities.  For each city, the code counts the number of cities reachable within the `distanceThreshold`.
*   **Tracking the Best City:** Similar to the Dijkstra solution, it keeps track of the city with the smallest count of reachable neighbors, also preferring the larger city index in case of ties, though without the need for a custom comparator as the loop order ensures ties are resolved correctly.
*   **Return Result:** Finally, it returns the city with the minimum reachable cities.

## 3. Key Insights and Algorithmic Techniques Used

*   **Dijkstra's Algorithm:** A classic algorithm for finding the shortest paths from a single source node to all other nodes in a weighted graph.  It relies on a priority queue (implemented as a `set` in the code) to efficiently select the next node to visit. The crucial property is that Dijkstra's algorithm finds the shortest paths in order of increasing distance from the source. It's well-suited for single-source shortest path problems.
*   **Floyd-Warshall Algorithm:** An algorithm for finding the shortest paths between *all pairs* of nodes in a weighted graph.  It's based on dynamic programming and iteratively updates the distance matrix. Floyd-Warshall is more suitable for all-pairs shortest path problems. It can also handle negative edge weights (as long as there are no negative cycles), which Dijkstra's algorithm cannot.
*   **Adjacency List Representation:**  Using an adjacency list is efficient for sparse graphs (graphs with relatively few edges). It stores only the existing edges, saving space compared to an adjacency matrix.
*   **Priority Queue (set in C++):** The use of a `set` in the Dijkstra solution acts as a priority queue, enabling efficient selection of the next node to visit based on its distance from the source. C++ sets are implemented as self-balancing binary search trees, providing logarithmic time complexity for insertion, deletion, and finding the minimum element.
*   **Distance Matrix (Floyd-Warshall):** An intuitive way to store all-pairs shortest path information, allowing for efficient updates and lookups.

## 4. Time and Space Complexity Analysis

**Solution 1 (Dijkstra's):**

*   **Time Complexity:** O(N * (E log V)), where N is the number of cities (source nodes), E is the number of edges, and V is the number of vertices (cities).  Dijkstra's algorithm itself takes O(E log V) time because the set operations are logarithmic. This is run N times, once for each source node.
*   **Space Complexity:** O(E + N), where E is the space used to store the adjacency list, and N is the space used to store distances for each node during a run of Dijkstra.

**Solution 2 (Floyd-Warshall):**

*   **Time Complexity:** O(N^3), where N is the number of cities.  The Floyd-Warshall algorithm has three nested loops, each iterating through all the cities.
*   **Space Complexity:** O(N^2) because the distance matrix `dist` is of size N x N.

**Choice of Algorithm:**

For sparse graphs, where E is much smaller than N^2, Dijkstra's algorithm (Solution 1) might be more efficient.  However, for dense graphs, where E is close to N^2, or if the problem requires finding the shortest paths between *all pairs* of nodes regardless, Floyd-Warshall (Solution 2) can be a good choice due to its simpler implementation. Also, consider the problem constraints. If `n` is sufficiently small, O(N^3) can be acceptable. In this particular problem on LeetCode, the constraints allow for either approach.

## 5. Important Code Patterns or Tricks Used

*   **Adjacency List Construction:** Building the adjacency list from the edge list is a common pattern in graph algorithms.
*   **Initialization of Distance Array/Matrix:**  Setting initial distances to `INT_MAX` and the distance from a node to itself to 0 is crucial for both Dijkstra's and Floyd-Warshall algorithms.
*   **Custom Comparator in `set`:** Solution 1 uses a custom comparator (`cmp`) in the `set` to handle ties in the number of reachable neighbors. It ensures that when two cities have the same number of reachable neighbors, the city with the higher index is chosen.
*   **`auto &[v, w] : graph[x]`:** C++'s structured binding syntax simplifies iteration through the adjacency list, making the code more readable.

## 6. Edge Cases Handled

*   **Unreachable Nodes:** The algorithms correctly handle cases where some nodes are unreachable from a given source. The distances to these nodes remain `INT_MAX`, and they are not counted as reachable within the `distanceThreshold`.
*   **Self-Loops:** The distance matrix in the Floyd-Warshall solution is initialized such that `dist[node][node] = 0`, correctly handling self-loops (though the problem description doesn't specifically mention self-loops, this initialization ensures they don't cause issues).
*   **Ties:** The custom comparator (`cmp`) in Dijkstra's version, and the later assignment `ans = node;` in Floyd-Warshall, ensure that when multiple cities have the same minimum number of reachable cities, the city with the largest index is returned, as required by the problem statement.
*   **No Edges:** Both solutions gracefully handle the case where the input `edges` vector is empty.  In this case, the graph will have no connections, and the number of reachable cities for each city will be 0, and either city index will be a valid answer, but the loop and if conditions will lead to the right result (the largest numbered node).
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

class SolutionTwo {
  public:
    int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold) {
        // we find the distance from each to node to every other node
        // using floyd-warshall
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));

        // initialize the distance array
        for (int node = 0; node < n; node++) {
            dist[node][node] = 0;
        }

        for (auto &vec : edges) {
            int u = vec[0];
            int v = vec[1];
            int w = vec[2];
            dist[u][v] = w;
            dist[v][u] = w;
        }

        for (int via = 0; via < n; via++) {
            for (int u = 0; u < n; u++) {
                for (int v = 0; v < n; v++) {
                    int uvia = dist[u][via];
                    int viav = dist[via][v];
                    int uv = dist[u][v];
                    if (uvia != INT_MAX && viav != INT_MAX && uvia + viav < uv) {
                        dist[u][v] = uvia + viav;
                    }
                }
            }
        }

        int minCount = INT_MAX;
        int ans = -1;

        for (int node = 0; node < n; node++) {
            int count = 0;
            for (int x = 0; x < n; x++) {
                if (x != node && dist[node][x] <= distanceThreshold)
                    count++;
            }

            if (count <= minCount) {
                minCount = count;
                ans = node;
            }
        }

        return ans;
    }
};
```

---
*Documentation generated on 2025-08-04 20:16:07*
