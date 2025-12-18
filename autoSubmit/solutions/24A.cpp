#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    // `neighbors[u]` stores the two cities physically connected to `u`.
    // It is effectively an adjacency list for the undirected graph of the ring.
    std::vector<std::vector<int>> neighbors(n + 1);

    // `redirect_costs[{u, v}]` stores the cost to travel directly from `u` to `v`.
    // If the original road was `u -> v`, then `redirect_costs[{u, v}]` is 0.
    // If the original road was `v -> u`, then `redirect_costs[{u, v}]` is `c` (the redirection cost).
    std::map<std::pair<int, int>, int> redirect_costs;

    for (int i = 0; i < n; ++i) {
        int u, v, c;
        std::cin >> u >> v >> c;
        
        // Add physical connections to the undirected graph
        neighbors[u].push_back(v);
        neighbors[v].push_back(u);

        // Store costs for both possible directions for this road segment:
        // 1. If we want traffic `u -> v`: it's already in this direction, so cost is 0.
        redirect_costs[{u, v}] = 0;
        // 2. If we want traffic `v -> u`: we need to redirect the `u -> v` road, costing `c`.
        redirect_costs[{v, u}] = c;
    }

    long long cost1 = 0; // Cost for one traversal direction (e.g., "clockwise")
    long long cost2 = 0; // Cost for the other traversal direction (e.g., "counter-clockwise")

    // --- Calculate Cost 1 ---
    // Start at city 1. Take the first available neighbor (neighbors[1][0]) as the initial step.
    int current_node_1 = 1;
    int previous_node_1 = 0; // Use 0 as a dummy value for the node we came from initially
    int count_1 = 0; // Counts the number of edges traversed

    // Handle the first step explicitly to set up `previous_node_1` correctly.
    int next_node_to_visit_1 = neighbors[1][0];
    cost1 += redirect_costs[{current_node_1, next_node_to_visit_1}];
    previous_node_1 = current_node_1;
    current_node_1 = next_node_to_visit_1;
    count_1 = 1;

    // Continue traversing the ring for `n-1` more steps (total `n` edges to complete the cycle)
    while (count_1 < n) {
        for (int neighbor : neighbors[current_node_1]) {
            if (neighbor != previous_node_1) {
                // This `neighbor` is the next node in the chosen traversal direction
                cost1 += redirect_costs[{current_node_1, neighbor}];
                previous_node_1 = current_node_1;
                current_node_1 = neighbor;
                count_1++;
                break; // Move to the next node, break from inner loop
            }
        }
    }

    // --- Calculate Cost 2 ---
    // Start at city 1 again. Take the *other* available neighbor (neighbors[1][1]) as the initial step.
    int current_node_2 = 1;
    int previous_node_2 = 0; // Use 0 as a dummy value for the node we came from initially
    int count_2 = 0; // Counts the number of edges traversed

    // Handle the first step explicitly.
    int next_node_to_visit_2 = neighbors[1][1];
    cost2 += redirect_costs[{current_node_2, next_node_to_visit_2}];
    previous_node_2 = current_node_2;
    current_node_2 = next_node_to_visit_2;
    count_2 = 1;

    // Continue traversing the ring for `n-1` more steps
    while (count_2 < n) {
        for (int neighbor : neighbors[current_node_2]) {
            if (neighbor != previous_node_2) {
                // This `neighbor` is the next node in this traversal direction
                cost2 += redirect_costs[{current_node_2, neighbor}];
                previous_node_2 = current_node_2;
                current_node_2 = neighbor;
                count_2++;
                break; // Move to the next node, break from inner loop
            }
        }
    }

    // The minimum cost is the smaller of the two calculated costs.
    std::cout << std::min(cost1, cost2) << std::endl;
}

int main() {
    // Enable fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();

    return 0;
}