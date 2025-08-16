#include <algorithm>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>

using namespace std;

const int MAXN = 200005;
const int LOGN = 18;

// Adjacency list for the graph
vector<pair<int, int>> adj[MAXN];
int N, M;

// Data structures for the spanning tree and LCA
int parent[MAXN];
int depth[MAXN];
int up[MAXN][LOGN];
bool visited[MAXN];

vector<tuple<int, int, int>> extra_edges;
vector<int> special_nodes;
map<int, int> node_to_idx;

// Build a spanning tree using BFS from node 1. This version is corrected and safe.
void bfs_spanning_tree(int start_node) {
    fill(visited + 1, visited + N + 1, false);
    vector<int> q;
    q.push_back(start_node);
    visited[start_node] = true;
    depth[start_node] = 0;
    parent[start_node] = 0;

    int head = 0;
    while (head < (int)q.size()) {
        int u = q[head++];
        for (auto &edge : adj[u]) {
            int v = edge.first;
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                depth[v] = depth[u] + 1;
                q.push_back(v);
            }
        }
    }
}

// Precompute for LCA queries using binary lifting
void build_lca() {
    for (int i = 1; i <= N; ++i) {
        up[i][0] = parent[i];
    }
    for (int j = 1; j < LOGN; ++j) {
        for (int i = 1; i <= N; ++i) {
            if (up[i][j - 1] != 0) {
                up[i][j] = up[up[i][j - 1]][j - 1];
            } else {
                up[i][j] = 0;
            }
        }
    }
}

// Find LCA of two nodes
int get_lca(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);
    for (int j = LOGN - 1; j >= 0; --j) {
        if (up[u][j] != 0 && depth[u] - (1 << j) >= depth[v]) {
            u = up[u][j];
        }
    }
    if (u == v)
        return u;
    for (int j = LOGN - 1; j >= 0; --j) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }
    return parent[u];
}

// Get distance between two nodes in the spanning tree
int get_dist(int u, int v) {
    if (u == 0 || v == 0)
        return 1e9; // Should not happen with 1-based indexing
    int lca = get_lca(u, v);
    return depth[u] + depth[v] - 2 * depth[lca];
}

// DP function to compute walks from a start node using a given set of edges
void solve_dp(int start_node, const vector<tuple<int, int, int>> &edges, map<int, long long> dp[1 << 11][44]) {
    int E_half = edges.size();

    dp[0][node_to_idx[start_node]][0] = 1;

    for (int mask = 0; mask < (1 << E_half); ++mask) {
        for (size_t u_idx = 0; u_idx < special_nodes.size(); ++u_idx) {
            if (dp[mask][u_idx].empty())
                continue;

            int u = special_nodes[u_idx];
            for (int i = 0; i < E_half; ++i) {
                if (!((mask >> i) & 1)) {
                    int v1 = get<0>(edges[i]);
                    int v2 = get<1>(edges[i]);
                    int v1_idx = node_to_idx.at(v1);
                    int v2_idx = node_to_idx.at(v2);

                    for (auto const &[len, count] : dp[mask][u_idx]) {
                        int new_len1 = len + get_dist(u, v1) + 1;
                        if (new_len1 < N)
                            dp[mask | (1 << i)][v2_idx][new_len1] += count;

                        int new_len2 = len + get_dist(u, v2) + 1;
                        if (new_len2 < N)
                            dp[mask | (1 << i)][v1_idx][new_len2] += count;
                    }
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    vector<pair<int, int>> all_edges;
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, 0});
        adj[v].push_back({u, 0});
        all_edges.push_back({u, v});
    }

    bfs_spanning_tree(1);

    for (const auto &edge : all_edges) {
        int u = edge.first;
        int v = edge.second;
        if (parent[v] != u && parent[u] != v) {
            extra_edges.emplace_back(u, v, extra_edges.size());
        }
    }

    build_lca();

    vector<int> temp_special_nodes;
    temp_special_nodes.push_back(1);
    temp_special_nodes.push_back(N);
    for (const auto &edge : extra_edges) {
        temp_special_nodes.push_back(get<0>(edge));
        temp_special_nodes.push_back(get<1>(edge));
    }
    sort(temp_special_nodes.begin(), temp_special_nodes.end());
    temp_special_nodes.erase(unique(temp_special_nodes.begin(), temp_special_nodes.end()), temp_special_nodes.end());
    special_nodes = temp_special_nodes;

    for (size_t i = 0; i < special_nodes.size(); ++i) {
        node_to_idx[special_nodes[i]] = i;
    }

    int E = extra_edges.size();
    int E1 = E / 2;
    int E2 = E - E1;

    vector<tuple<int, int, int>> edgesA, edgesB;
    for (int i = 0; i < E1; ++i)
        edgesA.push_back(extra_edges[i]);
    for (int i = 0; i < E2; ++i)
        edgesB.push_back(extra_edges[E1 + i]);

    map<int, long long> dpA[1 << 11][44];
    map<int, long long> dpB[1 << 11][44];

    solve_dp(1, edgesA, dpA);
    solve_dp(N, edgesB, dpB);

    vector<long long> ans(N, 0);

    int tree_path_dist = get_dist(1, N);
    if (tree_path_dist < N)
        ans[tree_path_dist] = 1;

    for (int maskA = 0; maskA < (1 << E1); ++maskA) {
        for (int maskB = 0; maskB < (1 << E2); ++maskB) {
            for (size_t i = 0; i < special_nodes.size(); ++i) {
                if (dpA[maskA][i].empty() || dpB[maskB][i].empty())
                    continue;
                for (auto const &[lenA, countA] : dpA[maskA][i]) {
                    for (auto const &[lenB, countB] : dpB[maskB][i]) {
                        int total_len = lenA + lenB;
                        if (total_len > 0 && total_len < N) {
                            ans[total_len] += countA * countB;
                        }
                    }
                }
            }
        }
    }

    for (int k = 1; k < N; ++k) {
        cout << ans[k] << (k == N - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}