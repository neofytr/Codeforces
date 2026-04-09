# cheapestFlights

```markdown
# Cheapest Flights Within K Stops

## 1. Problem Description

The problem, "Cheapest Flights Within K Stops" (available on [LeetCode](https://leetcode.com/problems/cheapest-flights-within-k-stops/description/)), asks us to find the cheapest price from a source city `src` to a destination city `dst` with at most `k` stops. We are given `n` cities, a list of flights represented as `flights`, where `flights[i] = [from_i, to_i, price_i]`, a source city `src`, a destination city `dst`, and the maximum number of stops `k`. If there is no such route, return `-1`.

## 2. Approach Explanation

The code provides several solutions, each employing a slightly different approach to solve the problem.  All approaches leverage graph representations to model the cities and flights.  Here's a breakdown of each:

*   **`SolutionTwo` (Dijkstra-like with stops constraint):** This solution uses a priority queue (implemented with a `set`) to implement a modified Dijkstra's algorithm. It keeps track of the cost, the current node, and the number of stops used. A `visited` array stores the minimum cost to reach a node with a specific number of stops. The algorithm explores nodes in increasing order of cost, stopping if the number of stops exceeds `k`.

*   **`SolutionThree` (DFS with Memoization):** This solution utilizes Depth-First Search (DFS) combined with memoization (dynamic programming). It explores all possible paths recursively, keeping track of the remaining number of flights (`k+1`, as `k` stops mean `k+1` flights). The `dp[node][flights_left]` array stores the minimum cost to reach `dst` from `node` with `flights_left` flights remaining. Memoization prevents redundant calculations.

*   **`SolutionFour` (Dijkstra with Path Length Prioritization):** This solution is another Dijkstra's based approach using a set as a priority queue. Critically, it prioritizes exploration based on the *number of hops* or 'path length' first, *then* the distance. This ensures we explore paths with fewer hops earlier, increasing the likelihood of finding the optimal solution within `k` stops.

*   **`Solution` (BFS with Cost Optimization):**  This solution uses Breadth-First Search (BFS) to explore the graph level by level. It uses a queue to store the current cost, node, and the number of stops. A `minCost` array keeps track of the minimum cost to reach each node. It's crucial that `minCost[next]` is updated only if a *cheaper* path is found. This pruning avoids revisits with more hops *and* a greater cost, improving efficiency.

## 3. Key Insights and Algorithmic Techniques

*   **Graph Representation:**  The problem naturally maps to a graph where cities are nodes and flights are edges with associated prices. An adjacency list `vector<vector<pair<int, int>>> graph(n)` is used to efficiently store the graph, where `graph[u]` contains a list of pairs `(v, price)` representing flights from city `u` to city `v` with a given price.

*   **Dijkstra's Algorithm Adaptation:**  `SolutionTwo` and `SolutionFour` demonstrate the application of Dijkstra's algorithm to find the shortest path, but with an added constraint of the maximum number of stops (`k`). The priority queue ensures that nodes are explored in increasing order of cost, leading to the optimal solution. The `visited` array (in `SolutionTwo`) and the `pathLen` prioritization (in `SolutionFour`) effectively address the stops constraint.

*   **DFS with Memoization (Dynamic Programming):** `SolutionThree` showcases the effectiveness of DFS with memoization to solve pathfinding problems with constraints.  The `dp` array stores intermediate results, avoiding recomputation of overlapping subproblems and significantly improving performance.  The base cases in the `dfs` function handle the termination conditions for reaching the destination or running out of flights.

*   **BFS (Breadth-First Search):** `Solution` utilizes BFS, an ideal choice for finding the shortest path in an unweighted graph.  In this case, we need the cheapest path considering the stop constraint. The key optimization is the pruning step where the algorithm only explores neighbors if a cheaper path is found (`newCost < minCost[next]`). This pruning is critical for efficiency.

*   **Pruning:** The BFS solution (`Solution`) exemplifies a critical optimization technique known as *pruning*. By only exploring paths that are cheaper than previously seen paths to a given node, the algorithm avoids redundant exploration and reduces the search space. This significantly improves efficiency.

*   **Priority Queue Choice:**  `SolutionTwo` and `SolutionFour` use a `std::set` as a priority queue.  While `std::priority_queue` is more commonly used, `std::set` offers the ability to remove specific elements if a better path is found to a node that's already in the queue (though this functionality is not strictly used in `SolutionTwo` or `SolutionFour` as presented.)  However, the path length prioritization aspect in `SolutionFour` makes `set` a very efficient choice due to its logarithmic insertion/deletion.

## 4. Time and Space Complexity Analysis

Here's an approximate analysis:

*   **`SolutionTwo` (Dijkstra-like):**
    *   **Time Complexity:** O(E * k * log(N*k)) where E is the number of flights and N is the number of cities. The `set` operations dominate the time complexity. `k` accounts for the stops condition check.
    *   **Space Complexity:** O(N * k) for the `visited` array and O(N*k) for the `set` in the worst case.

*   **`SolutionThree` (DFS with Memoization):**
    *   **Time Complexity:** O(N * k * E) where E is the number of flights. Each state `(node, remainingFlights)` is visited at most once, and for each state, we iterate through the neighbors in the graph.
    *   **Space Complexity:** O(N * k) for the `dp` array and the recursion stack (which can be at most O(N) in the worst case).

*   **`SolutionFour` (Dijkstra with Path Length):**
     *   **Time Complexity:** O(E * k * log(N*k)), similar to SolutionTwo.
     *   **Space Complexity:** O(N * k) for the `dist` vector and the `set`.

*   **`Solution` (BFS):**
    *   **Time Complexity:** O(N * E * k) in the worst case, where we might visit each edge up to `k` times.  E is the number of flights, and N is the number of cities.
    *   **Space Complexity:** O(N + Q), where Q is the maximum size of the queue, which can be O(N * k) in the worst case.  The `minCost` vector takes O(N) space.

## 5. Important Code Patterns or Tricks Used

*   **Adjacency List Construction:** Building the adjacency list from the `flights` vector is a standard pattern for representing graphs.

*   **Tuple Usage:** Using `tuple<int, int, int>` to store cost, node, and stops in the priority queue and queue makes the code more readable and organized.

*   **INT_MAX Initialization:** Initializing `minCost` or `visited` arrays with `INT_MAX` is a common practice for finding minimum values. It allows the algorithm to easily identify unvisited nodes.

*   **Stopping Condition (`stops >= k + 2`):** Correctly handling the stopping condition based on the number of stops is crucial. The condition `stops >= k + 2` is used because `k` represents the *maximum* number of *stops*, which means that you can traverse a maximum of `k + 1` flights (or edges) from the `src` to `dst`.

*   **Memoization Technique (in `SolutionThree`):** The technique of using a `dp` array to store intermediate results and checking for `-1` to indicate uncomputed states is a classic memoization approach.

*   **Pruning (in `Solution`):** The conditional exploration (`newCost < minCost[next]`) to only explore neighbors if a cheaper path is found greatly optimizes the BFS.

## 6. Edge Cases Handled

*   **No Path Found:** All solutions return `-1` if no path is found from `src` to `dst` within `k` stops. This is typically handled by returning `-1` if the destination node's cost remains `INT_MAX` after the algorithm completes.

*   **Source Equals Destination:** While not explicitly handled, if `src == dst`, the initial cost `minCost[src] = 0` ensures that 0 is returned (or the DFS base case will return 0), which is the correct behavior since no flights are needed.

*   **Validating Inputs (not explicit):** The code assumes valid input (e.g., `src` and `dst` are valid node indices). In a real-world application, you would want to validate the input to avoid out-of-bounds errors.


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

class SolutionFour {
  public:
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k) {
        vector<vector<pair<int, int>>> graph(n);
        for (auto &f : flights) {
            int from = f[0], to = f[1], price = f[2];
            graph[from].emplace_back(to, price);
        }

        // we do dijkstra in increasing order of pathLen
        set<tuple<int, int, int>> heap; // pathLen, currNode, pathDist
        vector<int> dist(n, INT_MAX);

        dist[src] = 0;
        heap.insert({1, src, dist[src]});
        while (!heap.empty()) {
            auto [pathLen, currNode, pathDist] = *(heap.begin());
            heap.erase(heap.begin());

            if (pathLen >= k + 2)
                continue;

            for (auto &[v, w] : graph[currNode]) {
                if (pathDist + w < dist[v]) {
                    // we have visited v probably with a greater number of stops, but with a shorter distance
                    // we need to consider this path
                    dist[v] = pathDist + w;
                    heap.insert({pathLen + 1, v, dist[v]});
                }
            }
        }

        return dist[dst] == INT_MAX ? -1 : dist[dst];
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
*Documentation generated on 2025-08-03 12:46:52*
