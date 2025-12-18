#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // For iota
#include <set> // For multiset

// Using fast I/O
void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

// A large enough value for infinity.
// Max cost = 10^9 (gold price) * 10^9 (max gold) + 10^9 (silver price) * 10^9 (max silver)
// = 10^18 + 10^18 = 2 * 10^18.
// `long long` max is about 9 * 10^18. So 4 * 10^18 is a safe infinity.
const long long INF = 4e18;

// Structure to represent an edge
struct Edge {
    int u, v;
    long long g, s;

    // Custom comparison for sorting edges by 'g' value
    bool operator<(const Edge& other) const {
        return g < other.g;
    }
};

// Custom comparison for sorting edges by 's' value (for multiset/Kruskal's)
struct CompareS {
    bool operator()(const Edge& e1, const Edge& e2) const {
        return e1.s < e2.s;
    }
};

// Disjoint Set Union (DSU) structure
struct DSU {
    std::vector<int> parent;
    int components;

    DSU(int n) : components(n) {
        parent.resize(n + 1); // Cities are 1-indexed
        std::iota(parent.begin(), parent.end(), 0); // Initialize parent[i] = i
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // Path compression
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j; // Union by rank/size could be added, but simple union is fine for N=200
            components--;
            return true;
        }
        return false;
    }
};

int main() {
    fast_io();

    int n, m;
    std::cin >> n >> m;

    long long G_cost, S_cost;
    std::cin >> G_cost >> S_cost;

    std::vector<Edge> all_roads(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> all_roads[i].u >> all_roads[i].v >> all_roads[i].g >> all_roads[i].s;
    }

    // Sort all roads by their 'g' value in ascending order.
    // This allows us to iterate through candidate 'a' values in increasing order.
    std::sort(all_roads.begin(), all_roads.end());

    long long min_total_cost = INF;

    // `kruskal_candidate_edges_multiset` will store edges that are eligible based on `g <= current_a`,
    // and will keep them sorted by their `s` values.
    // Using `std::multiset` provides O(log K) insertion and sorted iteration for Kruskal's,
    // where K is the current number of edges in the set.
    std::multiset<Edge, CompareS> kruskal_candidate_edges_multiset;

    // Iterate through each road as a potential "bottleneck" for gold coins (`g`).
    // `all_roads[i].g` becomes our `a` value.
    for (int i = 0; i < m; ++i) {
        long long current_a = all_roads[i].g;
        
        // Add the current road to the set of edges considered for Kruskal's.
        // All roads up to index `i` (inclusive) have `g` values less than or equal to `current_a`.
        kruskal_candidate_edges_multiset.insert(all_roads[i]);

        // Run Kruskal's algorithm on the currently available edges (sorted by 's' value)
        // to find the minimum 'b' (maximum 's' in MST) required to connect the graph.
        DSU dsu(n);
        long long current_b = 0; // This will store the max 's' value in the MST
        int edges_taken = 0;    // Count of edges taken into the MST

        for (const auto& edge : kruskal_candidate_edges_multiset) {
            if (dsu.unite(edge.u, edge.v)) {
                // If this edge connects two previously disconnected components, add it to MST
                current_b = std::max(current_b, edge.s);
                edges_taken++;
            }
            // If we have selected N-1 edges, the graph is connected (for N > 1 cities).
            if (edges_taken == n - 1) {
                break; 
            }
        }

        // If the graph is connected with `n-1` edges (meaning all cities are connected)
        if (edges_taken == n - 1) {
            long long current_total_cost = current_a * G_cost + current_b * S_cost;
            if (current_total_cost < min_total_cost) {
                min_total_cost = current_total_cost;
            }
        }
    }

    if (min_total_cost == INF) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << min_total_cost << std::endl;
    }

    return 0;
}