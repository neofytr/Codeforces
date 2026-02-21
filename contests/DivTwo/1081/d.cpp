#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

const int INF = 1e18;

struct Line {
    int m, c;
    int eval(int x) { return m * x + c; }
};

// Structure for Convex Hull Trick on a node
struct Hull {
    vector<Line> lines;
    // Add lines in sorted order of slope
    void add_line(int m, int c) {
        Line new_line = {m, c};
        while (lines.size() >= 2) {
            const Line& l1 = lines[lines.size() - 2];
            const Line& l2 = lines.back();
            // Intersection of l1 and l3 is to the left of intersection of l1 and l2
            // (c2-c1)/(m1-m2) >= (c3-c1)/(m1-m3)
            // Using doubles to avoid overflow in cross product check for simplicity
            // or strict cross multiplication
            double x1 = (double)(l2.c - l1.c) / (l1.m - l2.m);
            double x2 = (double)(new_line.c - l1.c) / (l1.m - new_line.m);
            if (x1 >= x2) lines.pop_back();
            else break;
        }
        lines.pb(new_line);
    }
    int query(int x) {
        if (lines.empty()) return -INF;
        int l = 0, r = lines.size() - 1;
        int ans = lines[l].eval(x);
        while (l <= r) {
            int mid1 = l + (r - l) / 3;
            int mid2 = r - (r - l) / 3;
            int y1 = lines[mid1].eval(x);
            int y2 = lines[mid2].eval(x);
            ans = max({ans, y1, y2});
            if (y1 < y2) l = mid1 + 1;
            else r = mid2 - 1;
        }
        return ans;
    }
};

struct Node {
    Hull hull;
    int max_val;
    int lazy; // -1 if no lazy
} tree[800005];

void build(int node, int start, int end, const vector<pair<int,int>>& items) {
    tree[node].lazy = -1;
    tree[node].max_val = -INF;
    tree[node].hull.lines.clear();
    
    // items contains {W, C}
    // Sort items by slope (W) for Hull
    vector<pair<int,int>> range_items;
    for(int i=start; i<=end; ++i) range_items.pb(items[i]);
    sort(all(range_items)); // Sort by m

    for (auto p : range_items) {
        tree[node].hull.add_line(p.first, p.second);
    }

    if (start == end) return;
    int mid = (start + end) / 2;
    build(2 * node, start, mid, items);
    build(2 * node + 1, mid + 1, end, items);
}

void push(int node) {
    if (tree[node].lazy != -1) {
        int v = tree[node].lazy;
        if (tree[2*node].lazy == -1 || v > tree[2*node].lazy) {
             tree[2*node].lazy = v;
             tree[2*node].max_val = tree[2*node].hull.query(v);
        }
        if (tree[2*node+1].lazy == -1 || v > tree[2*node+1].lazy) {
             tree[2*node+1].lazy = v;
             tree[2*node+1].max_val = tree[2*node+1].hull.query(v);
        }
        tree[node].lazy = -1;
    }
}

// Range Set Update: set x = val for range [l, r]
// We assume we only update if val > current. 
// Since we process monotonic updates, we actually just overwrite.
void update(int node, int start, int end, int l, int r, int val) {
    if (start > end || start > r || end < l) return;
    if (start >= l && end <= r) {
        if (tree[node].lazy == -1 || val > tree[node].lazy) {
            tree[node].lazy = val;
            tree[node].max_val = tree[node].hull.query(val);
        }
        return;
    }
    push(node);
    int mid = (start + end) / 2;
    update(2 * node, start, mid, l, r, val);
    update(2 * node + 1, mid + 1, end, l, r, val);
    tree[node].max_val = max(tree[2 * node].max_val, tree[2 * node + 1].max_val);
}

int query(int node, int start, int end, int l, int r) {
    if (start > end || start > r || end < l) return -INF;
    if (start >= l && end <= r) return tree[node].max_val;
    push(node);
    int mid = (start + end) / 2;
    return max(query(2 * node, start, mid, l, r), query(2 * node + 1, mid + 1, end, l, r));
}

int n;
vector<int> a;
vector<vector<int>> adj;
vector<int> dep, W, sz, heavy, mx_dep, sec_dep, parent_node;
vector<int> ans;
int total_w;

void dfs_sz(int u, int p, int d) {
    dep[u] = d;
    sz[u] = 1;
    W[u] = a[u-1];
    parent_node[u] = p;
    mx_dep[u] = d;
    sec_dep[u] = d; // base case: no children
    
    int max_sz = -1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs_sz(v, u, d + 1);
            sz[u] += sz[v];
            W[u] += W[v];
            mx_dep[u] = max(mx_dep[u], mx_dep[v]);
            if (max_sz == -1 || mx_dep[v] > mx_dep[heavy[u]]) {
                heavy[u] = v;
                max_sz = sz[v]; // irrelevant, just flagging
            }
        }
    }
    
    // Calculate second max depth (excluding heavy child)
    for (int v : adj[u]) {
        if (v != p && v != heavy[u]) {
            sec_dep[u] = max(sec_dep[u], mx_dep[v]);
        }
    }
}

vector<int> base_cost;
void dfs_cost(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            // Rerooting formula
            // Cost(v) = Cost(u) - W[v] + (TotalW - W[v])
            base_cost[v] = base_cost[u] - W[v] + (total_w - W[v]);
            dfs_cost(v, u);
        }
    }
}

void solve_tc() {
    cin >> n;
    a.resize(n);
    total_w = 0;
    for(int i=0; i<n; ++i) { cin >> a[i]; total_w += a[i]; }
    adj.assign(n + 1, vector<int>());
    for(int i=0; i<n-1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    dep.assign(n + 1, 0);
    W.assign(n + 1, 0);
    sz.assign(n + 1, 0);
    heavy.assign(n + 1, 0);
    mx_dep.assign(n + 1, 0);
    sec_dep.assign(n + 1, 0);
    parent_node.assign(n + 1, 0);
    
    dfs_sz(1, 0, 0);

    // Calc base cost for root 1
    base_cost.assign(n + 1, 0);
    int c1 = 0;
    for(int i=1; i<=n; ++i) c1 += a[i-1] * dep[i];
    base_cost[1] = c1;
    dfs_cost(1, 0);
    
    ans.assign(n + 1, 0);

    vector<bool> visited(n + 1, false);

    for (int i = 1; i <= n; ++i) {
        if (!visited[i] && parent_node[i] == 0) {
        }
    }

    for (int head = 1; head <= n; ++head) {
        bool is_heavy_child = false;
        int p = parent_node[head];
        if (p && heavy[p] == head) is_heavy_child = true;
        
        if (is_heavy_child) continue;

        vector<int> path;
        int curr = head;
        while (curr) {
            path.pb(curr);
            visited[curr] = true;
            curr = heavy[curr];
        }

        int D_path = mx_dep[head];
        int max_gain_off = 0;
        
        for (int i = path.size() - 1; i >= 0; --i) {
            int u = path[i];
            
            for (int v : adj[u]) {
                if (v != parent_node[u] && v != heavy[u]) 
                     auto get_max = [&](auto&& self, int node) -> int {
                        int res = W[node] * (D_path - dep[node] + 1);
                        for (int child : adj[node]) {
                            if (child != parent_node[node]) {
                                res = max(res, self(self, child));
                            }
                        }
                        return res;
                    };
                    max_gain_off = max(max_gain_off, get_max(get_max, v));
                }
            }
            
            ans[u] = max(ans[u], max_gain_off);
        }

        int L = path.size();
        if (L > 1) {
            vector<pair<int, int>> items(L);
            for(int k=0; k<L; ++k) {
                int u = path[k];
                items[k] = {W[u], W[u] * (1 - dep[u])};
            }
            
            build(1, 0, L-1, items);
            
            for (int i = L - 2; i >= 0; --i) {
                int M = sec_dep[path[i]];
                update(1, 0, L-1, i + 1, L - 1, M);
                int res = query(1, 0, L-1, i + 1, L - 1);
                if (res != -INF) ans[path[i]] = max(ans[path[i]], res);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << base_cost[i] + ans[i] << (i == n ? "" : " ");
    }
    cout << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--) {
        solve_tc();
    }
    return 0;
}