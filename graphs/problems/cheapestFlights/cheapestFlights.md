# cheapestFlights

```markdown
## Documentation for Cheapest Flights Within K Stops

This document describes a solution to the "Cheapest Flights Within K Stops" problem on LeetCode ([https://leetcode.com/problems/cheapest-flights-within-k-stops/description/](https://leetcode.com/problems/cheapest-flights-within-k-stops/description/)).

### 1. Problem Description

Given a set of flights represented by a list of edges `flights`, where each edge `flights[i] = [from, to, price]` indicates a flight from city `from` to city `to` with a cost of `price`. The goal is to find the cheapest price from a source city `src` to a destination city `dst` with at most `k` stops. If no such route exists, return -1.

### 2. Approach Explanation

The solution utilizes a Breadth-First Search (BFS) algorithm to explore possible routes from the source to the destination. The key idea is to keep track of the current cost, the current node (city), and the number of stops taken.  A queue is used to store these states, and the algorithm explores the graph level by level based on the number of stops. To optimize the search, the algorithm maintains a `minCost` vector to store the minimum cost to reach each city seen so far.  A crucial optimization is to only explore paths that lead to a lower cost than previously seen for a given city.

### 3. Key Insights and Algorithmic Techniques Used

*   **Breadth-First Search (BFS):** BFS is used to explore the graph level by level, ensuring that routes with fewer stops are considered first.  This is important because the problem specifies a maximum number of stops (`k`).
*   **Dynamic Programming (Optimization with `minCost`):** The `minCost` vector serves as a dynamic programming optimization. It allows the algorithm to avoid exploring paths that are guaranteed to be more expensive than previously discovered paths to a particular city. This significantly reduces the search space.
*   **Graph Representation (Adjacency List):**  The flights are represented as an adjacency list (`graph`), where `graph[u]` contains a list of pairs `(v, price)`, indicating that there is a flight from city `u` to city `v` with a price of `price`.
*   **Tuple for State Representation:**  The queue stores tuples `(currCost, currNode, stops)` representing the current state of the search. This allows efficient tracking of the current cost, node, and the number of stops.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:** O(E * K), where E is the number of edges (flights) and K is the maximum number of stops allowed. In the worst case, we might explore each flight up to K times because we can revisit a node if we reach it using fewer stops and a lower cost. The algorithm effectively processes each edge up to K times as nodes are added to the queue.
*   **Space Complexity:** O(N + E), where N is the number of cities and E is the number of flights.
    *   O(N) for the `minCost` vector.
    *   O(E) for the `graph` (adjacency list). In the worst-case scenario, the queue can contain a number of elements proportional to the number of edges.

### 5. Important Code Patterns or Tricks Used

*   **Adjacency List Construction:** Efficiently creating the adjacency list from the input `flights` vector.
*   **Queue Management:** Using a `queue` to implement BFS and storing the current cost, node, and number of stops in a `tuple`.
*   **`minCost` Optimization:** Updating the `minCost` vector only when a cheaper path is found and using `newCost < minCost[next]` as a crucial condition to avoid redundant explorations. This drastically improves performance.
*   **Early Termination (Stops Limit):** Checking `if (stops > k) continue;` to avoid exploring paths that exceed the allowed number of stops.
*   **Clear Handling of No Solution:**  Returning -1 if no path is found to the destination within the allowed number of stops, using `return minCost[dst] == INT_MAX ? -1 : minCost[dst];`.
*   **Correct Cost Tracking:** Tracking `currCost` within the BFS rather than relying on `minCost[currNode]` for calculating `newCost`. `minCost[currNode]` represents the minimum cost found so far *at the time* the `minCost` vector was updated. There might be cheaper paths found since then. Relying on the `currCost` ensures correct path cost calculations at each step of the BFS.

### 6. Edge Cases Handled

*   **No Path Found:**  If no path exists from `src` to `dst` within `k` stops, the algorithm returns -1. This is handled by checking if `minCost[dst]` remains `INT_MAX` after the BFS.
*   **`src` equals `dst`:** Although not explicitly tested in the provided code, this would be handled correctly because `minCost[src]` is initialized to 0. If `src` and `dst` are the same, the function would return 0.
*   **`k = 0`:** When `k=0`, the algorithm will only consider direct flights from `src` to `dst`.
*   **Negative Flight Prices (Hypothetically):** While the problem description doesn't specify whether negative prices are allowed, the algorithm should correctly handle the presence of negative prices. However, in cases of negative cycles in a graph, the queue might become unbounded, but within the constraint of `k` stops, the algorithm will terminate.


## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

// Problem: cheapestFlights
// URL: https://leetcode.com/problems/cheapest-flights-within-k-stops/description/
// Difficulty: hard
// Tags:
// Strategy:

class Solution {
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
*Documentation generated on 2025-08-03 08:35:58*
