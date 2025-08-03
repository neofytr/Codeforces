# cheapestFlights

```markdown
## Cheapest Flights Within K Stops

This document analyzes a C++ solution to the "Cheapest Flights Within K Stops" problem, found on LeetCode: [https://leetcode.com/problems/cheapest-flights-within-k-stops/description/](https://leetcode.com/problems/cheapest-flights-within-k-stops/description/)

### 1. Problem Description

Given a set of flights represented as a list of edges `flights`, where each edge `flights[i] = [from_i, to_i, price_i]` represents a flight from city `from_i` to city `to_i` with a cost of `price_i`.  Also given the number of cities `n`, a source city `src`, a destination city `dst`, and a maximum number of stops `k`, find the cheapest price from `src` to `dst` with at most `k` stops. If there is no such route, return -1.

### 2. Approach Explanation

The problem can be solved using graph traversal algorithms.  The solutions provided showcase three approaches:

*   **SolutionTwo (Dijkstra with Stops):** This solution employs a modified Dijkstra's algorithm using a priority queue (implemented as a `std::set` in this case) to explore the graph.  It maintains a `visited` array to store the minimum cost to reach each node with a specific number of stops.  The priority queue stores tuples of (cost, node, stops), prioritizing nodes with lower costs.

*   **SolutionThree (DFS with Memoization):** This solution uses Depth-First Search (DFS) with memoization to avoid redundant calculations. The `dfs` function recursively explores possible paths from the source to the destination. The `dp` array stores the minimum cost to reach each node with a given number of remaining flights.

*   **Solution (BFS with Cost Optimization):** This is generally the optimal solution and uses Breadth-First Search (BFS) and a cost optimization approach. The solution constructs an adjacency list representation of the flights. It then uses a queue to perform a BFS traversal of the graph, keeping track of the current cost, the current node, and the number of stops taken. It also uses a `minCost` array to store the minimum cost to reach each node seen so far. It only enqueues a neighbor if a cheaper path is found to that neighbor.

### 3. Key Insights and Algorithmic Techniques Used

*   **Graph Representation:** Using an adjacency list (`vector<vector<pair<int, int>>> graph`) is efficient for representing the flight connections, where `graph[u]` stores a list of pairs `(v, price)` representing flights from city `u` to city `v` with a given price.

*   **Dijkstra's Algorithm (Modified):**  SolutionTwo utilizes Dijkstra's algorithm, which finds the shortest path from a source node to all other nodes in a graph. The modification lies in the `stops` parameter, which ensures that we explore paths with at most `k` stops.  The `visited` array with `k+2` columns is crucial to tracking the minimum cost to a node with a *specific* number of stops. This prevents the algorithm from choosing a more costly route simply because it has fewer steps initially.  Using a `std::set` ensures the lowest cost node is always processed next.

*   **DFS with Memoization (Dynamic Programming):** SolutionThree combines DFS with memoization to optimize performance. Memoization stores intermediate results in the `dp` array, so redundant computations are avoided. The state `dp[node][remainingFlights]` represents the minimum cost to reach the destination from `node` with `remainingFlights` allowed. This top-down dynamic programming approach improves efficiency.

*   **BFS for Shortest Paths (with Optimization):** The core insight in the `Solution` class is to use BFS, along with the crucial optimization of only enqueuing a neighbor if a strictly *cheaper* path to it is found.  The `minCost` array holds the minimum cost found so far to reach each node.  The condition `newCost < minCost[next]` is vital for pruning the search space and preventing revisiting nodes unnecessarily, leading to significant performance gains. This approach guarantees finding the shortest path (least cost) while adhering to the `k` stops constraint.

*   **Stops vs. Flights:**  It's essential to understand that `k` represents the *maximum number of stops*, which translates to a maximum of `k+1` flights. This is reflected in the size of the `visited` array (SolutionTwo), the bounds of the `dfs` recursion in SolutionThree, and the termination condition in the main BFS loop (`stops >= k + 2` in Solution).

### 4. Time and Space Complexity Analysis

*   **SolutionTwo (Dijkstra with Stops):**

    *   **Time Complexity:** O(E * K * log(N * K)), where E is the number of flights (edges), N is the number of cities (nodes), and K is the maximum number of stops.  The `set` operations (`insert`, `erase`) take O(log(N*K)), and each edge is potentially visited up to K times.
    *   **Space Complexity:** O(N * K) for the `visited` array.

*   **SolutionThree (DFS with Memoization):**

    *   **Time Complexity:** O(N * E * K), where N is the number of cities, E is the number of flights, and K is the maximum number of stops. Each state `dp[node][remainingFlights]` is computed at most once, and the DFS explores at most E neighbors for each node.
    *   **Space Complexity:** O(N * K) for the `dp` array and O(N+K) for the recursion call stack, which in worst case can grow to O(N) or O(K).

*   **Solution (BFS with Cost Optimization):**

    *   **Time Complexity:** O(V * E) where V is the number of vertices (cities) and E is the number of edges (flights). While it appears similar to a standard BFS, the optimization of only enqueuing a node if a cheaper path is found drastically reduces the number of nodes visited.  In the worst case, we might still visit all edges but practical performance is very high.
    *   **Space Complexity:** O(V + E) for the graph representation, the `minCost` array (size V), and the queue, where V is the number of cities and E is the number of flights.

### 5. Important Code Patterns or Tricks Used

*   **Adjacency List Representation:**  Efficiently storing graph connections.

*   **Tuple Usage:**  Using `std::tuple` to store multiple related values (cost, node, stops) for each entry in the priority queue or the main queue for BFS.

*   **INT_MAX Initialization:**  Initializing cost/distance arrays with `INT_MAX` to represent initially unreachable nodes.  This is a common pattern in shortest path algorithms.

*   **Early Exit/Pruning:**  The `if (stops >= k + 2) continue;` statement in `Solution` is a crucial optimization that prevents exploring paths that exceed the allowed number of stops. The `if (newCost < minCost[next])` condition ensures that only cheaper paths are explored.

*   **Memoization with -1:** SolutionThree employs -1 to denote uncomputed states in the DP array, distinguishing them from valid costs of 0.

### 6. Edge Cases Handled

*   **No Path Found:**  All solutions return -1 if no path from `src` to `dst` is found within the allowed number of stops. This is achieved by checking if the cost to reach `dst` remains `INT_MAX` after the graph traversal.

*   **Source and Destination Same:** If `src` and `dst` are the same, the algorithm should ideally return 0. This scenario might not be explicitly handled in the code but would naturally result in the correct answer. However, an explicit check would make the code more robust and readable.

*   **Empty Flights List:** The code gracefully handles the case where the `flights` list is empty, as the loops iterating through the flights would simply be skipped.

*   **Zero Stops Allowed:** The algorithms correctly handle the case where `k` is 0, meaning only direct flights from `src` to `dst` are considered.
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

class SolutionTwo {
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

class SolutionThree {
  public:
    int dfs(int node, int dst, int remainingFlights, vector<vector<int>> &dp, vector<vector<pair<int, int>>> &graph) {
        // Base Case 1: If we've reached the destination, the cost from here is 0.
        if (node == dst) {
            return 0;
        }

        // Base Case 2: If we have no more flights left but haven't reached the destination.
        if (remainingFlights == 0) {
            return INT_MAX;
        }

        // Memoization Check: Use -1 to check if state is already computed.
        if (dp[node][remainingFlights] != -1) {
            return dp[node][remainingFlights];
        }

        int minCost = INT_MAX;
        for (auto &[neighbor, cost] : graph[node]) {
            int costFromNeighbor = dfs(neighbor, dst, remainingFlights - 1, dp, graph);

            // If a valid path exists from the neighbor
            if (costFromNeighbor != INT_MAX) {
                minCost = min(minCost, cost + costFromNeighbor);
            }
        }

        // Store the result (which could be INT_MAX) and return.
        return dp[node][remainingFlights] = minCost;
    }

    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k) {
        vector<vector<pair<int, int>>> graph(n);
        for (auto &f : flights) {
            graph[f[0]].emplace_back(f[1], f[2]);
        }

        // DP State: dp[node][flights_left]
        // Initialize with -1 to distinguish from a computed cost of 0 or INT_MAX.
        vector<vector<int>> dp(n, vector<int>(k + 2, -1));

        // k stops means k+1 flights.
        int result = dfs(src, dst, k + 1, dp, graph);

        return (result == INT_MAX) ? -1 : result;
    }
};

class Solution {
  public:
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k) {
        // build adjacency list: graph[u] = {v, price}
        vector<vector<pair<int, int>>> graph(n);
        for (auto &f : flights) {
            int from = f[0], to = f[1], price = f[2];
            graph[from].emplace_back(to, price);
        }

        // queue holds: (current total cost, current node, number of nodes seen so far)
        queue<tuple<int, int, int>> que;
        que.push({0, src, 1});

        // this stores the minimum cost to reach each node
        // if a cheaper cost is found via a path with allowed stops, update it
        vector<int> minCost(n, INT_MAX);
        minCost[src] = 0;

        // the algorithm explores the graph in increasing number of steps
        // if currDist + w < dist[v], this means we can reach v in possibly greater number of nodes, but in a smaller distance
        // we can try this path out since we may reach dst from this lesser cost path in a total lesser cost than
        // dst was previously visited with
        // however, if currDist + w >= dist[v], this means we again reached v, with a greater number of nodes, but also
        // at a greater cost, there's no need to consider this path

        // The algorithm explores the graph in increasing number of steps (or "stops").
        // For each neighbor `v` of the current node `currNode`, we compute a possible new cost: `currDist + w`.

        // Now, we consider two scenarios:

        // 1. If (currDist + w < dist[v]):
        //    - This means we have found a **cheaper path to node `v`** than any previous one.
        //    - Although this new path may involve **more stops** than before,
        //      the **lower cost may allow us to reach the destination `dst` more cheaply overall**.
        //    - So, we should explore this path further, as it may lead to a cheaper route to the destination.

        // 2. If (currDist + w >= dist[v]):
        //    - This means we're reaching node `v` again, possibly with **more stops** and at a **higher cost** than before.
        //    - Since we already found a cheaper way to reach `v`, exploring this path further is unlikely to improve our result.
        //    - Therefore, we **skip** this path to avoid unnecessary work and potential cycles.

        // Summary:
        // -> We only continue exploring a neighbor `v` if we've found a cheaper way to get there (`currDist + w < dist[v]`).
        // -> This approach balances between exploring all possible paths and pruning inefficient ones,
        //    helping us find the minimum-cost path to the destination within the allowed number of stops.

        while (!que.empty()) {
            auto [currCost, currNode, stops] = que.front();
            que.pop();

            // if we’ve used atleast k + 2 nodes, this path is not allowed
            if (stops >= k + 2)
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
*Documentation generated on 2025-08-03 11:37:09*
