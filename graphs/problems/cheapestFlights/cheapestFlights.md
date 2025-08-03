# cheapestFlights

```markdown
## Documentation for Cheapest Flights Within K Stops Solution

This document provides a comprehensive analysis of the provided C++ code, which solves the "Cheapest Flights Within K Stops" problem on LeetCode (https://leetcode.com/problems/cheapest-flights-within-k-stops/description/).

### 1. Problem Description

The "Cheapest Flights Within K Stops" problem asks us to find the cheapest price to travel from a source city `src` to a destination city `dst` with at most `k` stops.  We are given:

*   `n`: The number of cities, labeled from 0 to n-1.
*   `flights`: A list of flights where `flights[i] = [from_i, to_i, price_i]` indicates a flight from city `from_i` to city `to_i` with a price of `price_i`.
*   `src`: The source city.
*   `dst`: The destination city.
*   `k`: The maximum number of stops allowed.

If there is no route from `src` to `dst` within `k` stops, return -1.

### 2. Approach Explanation

Both `Solution` and `SolutionTwo` classes provide solutions to the problem, differing slightly in implementation details but sharing the core algorithmic approach: Breadth-First Search (BFS) with some optimization to handle constraints and find the minimum cost.

**General Approach:**

1.  **Graph Representation:** The flight information is represented as an adjacency list. `graph[u]` stores a list of pairs `(v, price)`, where there's a flight from city `u` to city `v` with the given `price`.

2.  **BFS Traversal:** A BFS-like traversal is performed starting from the source city. The state maintained during the traversal includes:

    *   `cost`: The total cost to reach the current city.
    *   `current_city`: The current city being visited.
    *   `stops`: The number of stops taken to reach the current city.

3.  **Stop Constraint:** The BFS traversal is constrained by the maximum number of stops allowed (`k`).  If the number of stops exceeds `k`, the path is abandoned.

4.  **Cost Minimization:** The algorithm keeps track of the minimum cost to reach each city and uses this information to prune the search space. The approach ensures that only promising paths (those with lower costs) are explored further.

**Specific Differences between `Solution` and `SolutionTwo`:**

*   **`Solution`:** Uses a `set` as a priority queue (`pq`) to store `(cost, city, stops)`.  The `visited` array tracks the minimum cost to reach a city with a specific number of stops. This prevents revisits if a better path with the same number of stops is already known.

*   **`SolutionTwo`:** Uses a standard `queue` for BFS. It maintains a `minCost` vector to track the minimum cost to reach each city so far. This version relies on the fact that each queue element stores the exact cost to reach the current node through its path, avoiding issues with potentially outdated costs if multiple paths reach a node. It also updates `minCost` as the algorithm finds better paths.

### 3. Key Insights and Algorithmic Techniques Used

*   **BFS with Cost Tracking:** The core idea is to use BFS to explore all possible paths from the source to the destination. The cost is tracked to find the *cheapest* path.

*   **Stop Constraint Handling:** The `k` stops constraint is crucial and is enforced by terminating the search down paths that exceed this limit.

*   **Cost Optimization:** The algorithm prioritizes exploration based on the cost.  Both solutions implement optimization techniques that prevent exploration of paths that are guaranteed to be more expensive than previously found paths to the same node. `Solution` uses a `visited` array to prevent revisits for the same number of stops, while `SolutionTwo` uses the `minCost` vector.

*   **Graph Representation:** Using an adjacency list is suitable for representing the flight network, as it allows efficient access to the neighbors of a given city.

### 4. Time and Space Complexity Analysis

**`Solution`:**

*   **Time Complexity:**  O(E * K * log(N * K)). The while loop potentially visits all edges, and the `set` operations (insert, erase) take logarithmic time. The number of entries in the set is proportional to N*K (where N is nodes and K is the number of stops). So `log(N * K)`. E is the number of edges in graph, K is the maximum stops
*   **Space Complexity:** O(N * K + E).  O(N * K) for `visited` array and `set` and O(E) for the adjacency list.

**`SolutionTwo`:**

*   **Time Complexity:** O(E * K). In the worst case, we may enqueue each edge for each allowed stop.
*   **Space Complexity:** O(N + E). O(N) for `minCost` and O(E) for the adjacency list.

Where:
*   N is the number of cities (nodes).
*   E is the number of flights (edges).
*   K is the maximum number of stops allowed.

`SolutionTwo` generally performs better because the complexity is not burdened by log function.

### 5. Important Code Patterns or Tricks Used

*   **Adjacency List Representation:** Using `vector<vector<pair<int, int>>>` to represent a weighted graph efficiently.
*   **Tuple for State Tracking:** Using `tuple<int, int, int>` to compactly store the cost, city, and stop count during BFS.
*   **Min Cost Tracking (Optimization):** Both algorithms track the minimum cost to reach each node, preventing the algorithm from exploring more expensive paths.
*   **Early Termination:** Terminating the BFS exploration if the number of stops exceeds `k` prevents unnecessary computations.

### 6. Edge Cases Handled

*   **No Path Found:** Both solutions return -1 if no path is found from `src` to `dst` within `k` stops. This happens when the BFS traversal finishes without reaching the destination, indicated by `minCost[dst] == INT_MAX` or the priority queue becomes empty.
*   **Direct Flight:** The algorithm correctly handles the case where there is a direct flight from `src` to `dst`.
*   **Source and Destination are the same:** The logic inherently covers this as the initialization includes the starting node. The loop will exit upon finding `u == dst` in `Solution`, and the `minCost[src] = 0` correctly handles this scenario in `SolutionTwo`.
```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

// Problem: cheapestFlights
// URL: https://leetcode.com/problems/cheapest-flights-within-k-stops/description/
// Difficulty: hard
// Tags:
// Strategy:

class Solution {
  public:
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k) {
        vector<vector<pair<int, int>>> graph(n);
        for (auto &f : flights) {
            int from = f[0], to = f[1], price = f[2];
            graph[from].emplace_back(to, price);
        }

        // min-heap: (cost_so_far, current_node, stops_used)
        set<tuple<int, int, int>> pq;
        pq.insert({0, src, 0});

        // visited[node][stops] = minimum cost to reach `node` with `stops` stops
        vector<vector<int>> visited(n, vector<int>(k + 2, INT_MAX));
        visited[src][0] = 0;

        while (!pq.empty()) {
            auto [cost, u, stops] = *pq.begin();
            pq.erase(pq.begin());

            if (u == dst)
                return cost;

            if (stops > k)
                continue;

            for (auto &[v, price] : graph[u]) {
                int newCost = cost + price;
                if (newCost < visited[v][stops + 1]) {
                    visited[v][stops + 1] = newCost;
                    pq.insert({newCost, v, stops + 1});
                }
            }
        }

        return -1;
    }
};

class SolutionTwo {
  public:
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k) {
        // build adjacency list: graph[u] = {v, price}
        vector<vector<pair<int, int>>> graph(n);
        for (auto &f : flights) {
            int from = f[0], to = f[1], price = f[2];
            graph[from].emplace_back(to, price);
        }

        // queue holds: (current total cost, current node, number of stops so far)
        queue<tuple<int, int, int>> que;
        que.push({0, src, 0});

        // this stores the minimum cost to reach each node
        // if a cheaper cost is found via a path with allowed stops, update it
        vector<int> minCost(n, INT_MAX);
        minCost[src] = 0;

        while (!que.empty()) {
            auto [currCost, currNode, stops] = que.front();
            que.pop();

            // if we’ve used more than k stops, this path is not allowed
            if (stops > k)
                continue;

            // explore all neighbors of the current node
            for (auto &[next, price] : graph[currNode]) {
                int newCost = currCost + price; // if multiple paths lead to currNode, using minCost[currNode] may give us the minimum cost to reach currNode via previously explored paths
                                                // and that may not be equal to the cost to reach currNode from the current path

                /*

                1. we do not use dist[currNode] + w because that may be outdated if multiple paths reach currNode
                2. instead, we track currCost, which is the exact cost of the path that reached currNode in this BFS
                3. by checking newCost < minCost[next], we make sure we only explore better (cheaper) paths
                4. we only go deeper if we haven’t used more than k stops (stops > k check)

                */

                // only proceed if this path to next is cheaper than what we’ve seen before
                // this ensures we avoid unnecessary revisits unless we find a cheaper way
                if (newCost < minCost[next]) {
                    minCost[next] = newCost;

                    // push this next node to explore further, with updated cost and stop count
                    que.push({newCost, next, stops + 1});
                }
            }
        }

        // if we never found a path to dst within k stops, return -1
        return minCost[dst] == INT_MAX ? -1 : minCost[dst];
    }
};

```

---
*Documentation generated on 2025-08-03 09:12:35*
