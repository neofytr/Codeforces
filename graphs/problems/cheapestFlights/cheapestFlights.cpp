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
