#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define int long long

const int INF = 1e9;
vector<vector<pair<int, int>>> adj;
vector<int> tin, low;
vector<bool> is_bridge;
int timer;
vector<int> component;
int comp_cnt;

void find_bridges_dfs(int v, int p_edge_idx) {
    tin[v] = low[v] = timer++;
    for (auto &edge : adj[v]) {
        int to = edge.first;
        int edge_idx = edge.second;
        if (edge_idx == p_edge_idx)
            continue;
        if (tin[to] != -1) {
            low[v] = min(low[v], tin[to]);
        } else {
            find_bridges_dfs(to, edge_idx);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v]) {
                is_bridge[edge_idx] = true;
            }
        }
    }
}

void find_components_dfs(int v, int c_id) {
    component[v] = c_id;
    for (auto &edge : adj[v]) {
        int to = edge.first;
        int edge_idx = edge.second;
        if (component[to] == -1 && !is_bridge[edge_idx]) {
            find_components_dfs(to, c_id);
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    adj.assign(n + 1, vector<pair<int, int>>());
    vector<pair<int, int>> edges;
    edges.push_back({0, 0});
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        edges.push_back({u, v});
    }

    tin.assign(n + 1, -1);
    low.assign(n + 1, -1);
    is_bridge.assign(m + 1, false);
    timer = 0;
    find_bridges_dfs(1, -1);

    component.assign(n + 1, -1);
    comp_cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (component[i] == -1) {
            find_components_dfs(i, comp_cnt++);
        }
    }

    int start_comp = component[1];
    int end_comp = component[n];

    // no bridge yet ig
    if (start_comp == end_comp) {
        int q;
        cin >> q;
        for (int i = 0; i < q; ++i) {
            int c;
            cin >> c;
            cout << -1 << " ";
        }
        cout << "\n";
        return;
    }

    vector<vector<pair<int, int>>> adj_tree(comp_cnt);
    for (int i = 1; i <= m; ++i) {
        if (is_bridge[i]) {
            int u = edges[i].first;
            int v = edges[i].second;
            int c1 = component[u];
            int c2 = component[v];
            if (c1 != c2) {
                adj_tree[c1].push_back({c2, i});
                adj_tree[c2].push_back({c1, i});
            }
        }
    }

    vector<int> parent_comp(comp_cnt, -1);
    queue<int> tree_q;
    tree_q.push(start_comp);
    vector<bool> visited_comp(comp_cnt, false);
    visited_comp[start_comp] = true;

    while (!tree_q.empty()) {
        int u_comp = tree_q.front();
        tree_q.pop();
        if (u_comp == end_comp)
            break;
        for (auto &edge : adj_tree[u_comp]) {
            int v_comp = edge.first;
            if (!visited_comp[v_comp]) {
                visited_comp[v_comp] = true;
                parent_comp[v_comp] = u_comp;
                tree_q.push(v_comp);
            }
        }
    }

    vector<int> main_path_bridge_indices;
    int curr_comp = end_comp;
    while (curr_comp != start_comp && curr_comp != -1) {
        int p_comp = parent_comp[curr_comp];
        for (auto &edge : adj_tree[curr_comp]) {
            if (edge.first == p_comp) {
                main_path_bridge_indices.push_back(edge.second);
                break;
            }
        }
        curr_comp = p_comp;
    }

    vector<pair<int, int>> ans(n + 1, {INF, INF});
    queue<int> bfs_q;

    for (int idx : main_path_bridge_indices) {
        int u = edges[idx].first;
        int v = edges[idx].second;

        if (ans[u].first > 0)
            ans[u] = {0, idx};
        else
            ans[u].second = min(ans[u].second, idx);

        if (ans[v].first > 0)
            ans[v] = {0, idx};
        else
            ans[v].second = min(ans[v].second, idx);
    }

    for (int i = 1; i <= n; ++i) {
        if (ans[i].first == 0) {
            bfs_q.push(i);
        }
    }

    while (!bfs_q.empty()) {
        int u = bfs_q.front();
        bfs_q.pop();

        for (auto &edge : adj[u]) {
            int v = edge.first;
            pair<int, int> new_ans = {ans[u].first + 1, ans[u].second};

            if (new_ans < ans[v]) { // Lexicographical comparison
                ans[v] = new_ans;
                bfs_q.push(v);
            }
        }
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int c;
        cin >> c;
        cout << ans[c].second << " ";
    }
    cout << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}