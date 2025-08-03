# cheapestFlights

```markdown
# Cheapest Flights Within K Stops

## 1. Problem Description

The problem, found on LeetCode as "[Cheapest Flights Within K Stops](https://leetcode.com/problems/cheapest-flights-within-k-stops/description/)", asks to find the cheapest price from a source city (`src`) to a destination city (`dst`) with at most `k` stops.  You are given `n` cities labeled from `0` to `n - 1`, and a list of flights where `flights[i] = [from_i, to_i, price_i]` indicates a flight from city `from_i` to city `to_i` with a price of `price_i`. If there's no such route, return `-1`.

## 2. Approach Explanation

The code provides two solutions to this problem, `Solution` and `SolutionTwo`, both leveraging graph traversal to find the cheapest flight.  They use slightly different approaches to accomplish the same goal:

**Solution (Dijkstra-like with visited array):**

1.  **Graph Representation:** Builds an adjacency list (`graph`) to represent the flights, where `graph[u]` stores a list of pairs `(v, price)` representing flights from city `u` to city `v` with the associated price.

2.  **Priority Queue (Min-Heap):** Uses a `set` as a min-heap (`pq`) to store tuples of the form `(cost_so_far, current_node, stops_used)`.  The heap is prioritized by the cost, ensuring that nodes with lower costs are explored first.

3.  **Visited Array:** Utilizes a `visited` 2D vector to track the minimum cost to reach each node (`node`) with a certain number of stops (`stops`). `visited[node][stops]` stores the minimum cost to reach `node` using `stops` stops.

4.  **Traversal:**
    *   Starts by adding the source node (`src`) to the priority queue with a cost of `0` and `0` stops.
    *   While the priority queue is not empty:
        *   Extracts the node with the minimum cost from the queue.
        *   If the current node is the destination (`dst`), it returns the current cost.
        *   If the number of stops used exceeds `k`, it skips the current path (because we can only have up to `k` stops).
        *   Iterates through the neighbors of the current node.
        *   For each neighbor, calculates the new cost to reach it.
        *   If the new cost is less than the current minimum cost to reach the neighbor with `stops + 1` stops (i.e., `newCost < visited[v][stops + 1]`), updates `visited[v][stops + 1]` and adds the neighbor to the priority queue.

5.  **Return -1:** If the destination is not reached after exploring all possible paths, it returns `-1`.

**SolutionTwo (BFS with Cost Optimization):**

1.  **Graph Representation:** Same as in Solution.

2.  **Queue (BFS):** Uses a queue (`que`) to perform a Breadth-First Search (BFS). The queue stores tuples of the form `(current total cost, current node, number of nodes seen so far)`.

3.  **`minCost` Array:** An array `minCost` is maintained to keep track of the minimum cost to reach each city.  `minCost[i]` stores the minimum cost to reach city `i`.

4.  **Traversal:**

    * Starts by adding the source node (`src`) to the queue with cost 0 and number of nodes seen as 1.
    * While the queue is not empty:
        * Dequeue the element from the front of the queue.
        * If the number of nodes visited (`stops`) so far is more than `k + 1` (meaning `k` stops), then the path is discarded.
        * Iterate through the neighbors of the current node.
        *  Calculate the new cost to reach the neighboring city.
        *  If the `newCost` is less than the current minimum cost to reach that neighbor city, then update `minCost[next]` to `newCost` and enqueue the neighbor city with an updated stop count of `stops + 1`.

5.  **Return -1:** If the destination is not reached or `minCost[dst]` is still INT\_MAX, returns -1. Otherwise, returns `minCost[dst]`.

## 3. Key Insights and Algorithmic Techniques

*   **Graph Traversal:** Both solutions use graph traversal to explore the possible flight routes. `Solution` uses a variant of Dijkstra's algorithm (although it doesn't guarantee optimality if there are negative edge weights or cycles, which are not present in this problem definition).  `SolutionTwo` leverages BFS.
*   **Dynamic Programming (implicit):**  The `visited` array in `Solution` and the `minCost` array in `SolutionTwo` are forms of dynamic programming. They store intermediate results (minimum cost to reach a node with a certain number of stops) to avoid recomputation.
*   **Optimization:** Both solutions optimize their search by pruning paths that are unlikely to lead to a cheaper solution. In `Solution`, this is done by checking if `newCost < visited[v][stops + 1]`. In `SolutionTwo`, it's done by checking if `newCost < minCost[next]`.

## 4. Time and Space Complexity Analysis

**Solution:**

*   **Time Complexity:** O(E * K * log(N * K)), where E is the number of flights, N is the number of cities, and K is the maximum number of stops. The `set` operations (insert, erase) take log(N*K) time. The outer loop runs at most E * K times.
*   **Space Complexity:** O(N * K), due to the `graph` adjacency list, the priority queue (set), and the `visited` array.

**SolutionTwo:**

*   **Time Complexity:** O(V + E), in the worst case if we traverse every edge once and enqueue every vertex once. The queue can hold at most V vertices at any given time. In this specific case the complexity is actually higher. Every node `v` can enter the queue K times so the complexity is O(V*K + E) where K is the number of stops.
*   **Space Complexity:** O(V + E + V*K), for the adjacency list, the queue, and the `minCost` array.

## 5. Important Code Patterns or Tricks Used

*   **Adjacency List:** The use of an adjacency list is a standard way to represent graphs efficiently.
*   **Priority Queue/Queue**: Selection of the right data structure allows for efficient sorting and exploration of the possible options.
*   **2D Visited Array:** Using a 2D array `visited[node][stops]` to store the minimum cost to reach a node with a specific number of stops is a useful technique in problems that involve limiting the number of steps or hops.  It is very efficient to keep track of the minimum cost to reach the node.
*   **Tuples**: Using `std::tuple` to group related data together is a clear and concise way to manage the cost, node, and stop information.
*   **Early Exit (Pruning):** The `if (stops > k)` or `if (stops >= k+2)` check allows to exit early from paths that are invalid, improving efficiency.
*   **`emplace_back`:** Instead of using `push_back`, `emplace_back` can avoid creating a temporary object, which can improve performance in some cases.

## 6. Edge Cases Handled

*   **No Path:** The code returns `-1` if no path exists from the source to the destination within the allowed number of stops.
*   **Source == Destination:** Although not explicitly handled, if the source and destination are the same, the algorithms should return 0, assuming that the graph doesn't have negative edge weights (which is true for this problem).
*   **`k = 0`:** The code works correctly even when `k = 0` (meaning no stops allowed).
*   **INT_MAX Initialization:** Using `INT_MAX` to initialize the `visited` and `minCost` arrays is a common practice to represent "infinity" or "unvisited" states.  It's important to ensure that adding costs doesn't cause overflow issues (which are avoided in the comparisons).
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
*Documentation generated on 2025-08-03 10:26:57*
