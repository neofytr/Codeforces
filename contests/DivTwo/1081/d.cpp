#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back

const int INF = 1e18;
const int N = 200005;

struct Line {
    int m, c;
    int eval(int x) { return m * x + c; }
};

struct Hull {
    vector<Line> lns;
    bool bad(Line l1, Line l2, Line l3) {
        return (double)(l2.c - l1.c) * (l1.m - l3.m) >= (double)(l3.c - l1.c) * (l1.m - l2.m);
    }
    void add(int m, int c) {
        Line l = {m, c};
        while (lns.size() >= 2 && bad(lns[lns.size()-2], lns.back(), l)) lns.pop_back();
        lns.pb(l);
    }
    int qry(int x) {
        if (lns.empty()) return -INF;
        int l = 0, r = lns.size() - 1;
        while (r - l >= 3) {
            int m1 = l + (r - l) / 3;
            int m2 = r - (r - l) / 3;
            if (lns[m1].eval(x) < lns[m2].eval(x)) l = m1;
            else r = m2;
        }
        int res = -INF;
        for (int i = l; i <= r; ++i) res = max(res, lns[i].eval(x));
        return res;
    }
} tr[4 * N];

int n, tot, a[N], d[N], w[N], hvy[N], p[N], m1[N], m2[N], bc[N], ans[N];
vector<int> g[N];
vector<pair<Line, int>> slns;
bool vis[N];

void dfs1(int u, int par, int dep) {
    d[u] = dep; w[u] = a[u]; p[u] = par;
    m1[u] = m2[u] = dep; hvy[u] = 0;
    for (int v : g[u]) {
        if (v == par) continue;
        dfs1(v, u, dep + 1);
        w[u] += w[v];
        if (m1[v] > m1[u]) {
            m2[u] = m1[u];
            m1[u] = m1[v];
            hvy[u] = v;
        } else if (m1[v] > m2[u]) {
            m2[u] = m1[v];
        }
    }
}

void dfs2(int u, int par) {
    for (int v : g[u]) {
        if (v == par) continue;
        bc[v] = bc[u] - w[v] + (tot - w[v]);
        dfs2(v, u);
    }
}

int get_mx(int u, int D) {
    int res = w[u] * (D + 1 - d[u]);
    for (int v : g[u]) {
        if (v != p[u]) res = max(res, get_mx(v, D));
    }
    return res;
}

void build(int node, int s, int e) {
    tr[node].lns.clear();
    for (auto& p : slns) {
        if (p.second >= s && p.second <= e) {
            Line l = p.first;
            if (!tr[node].lns.empty() && tr[node].lns.back().m == l.m) tr[node].lns.pop_back();
            tr[node].add(l.m, l.c);
        }
    }
    if (s == e) return;
    int mid = (s + e) / 2;
    build(2 * node, s, mid);
    build(2 * node + 1, mid + 1, e);
}

int qry(int node, int s, int e, int l, int r, int x) {
    if (s > r || e < l) return -INF;
    if (s >= l && e <= r) return tr[node].qry(x);
    int mid = (s + e) / 2;
    return max(qry(2 * node, s, mid, l, r, x), qry(2 * node + 1, mid + 1, e, l, r, x));
}

struct Node { int l, r, v, mx, bst; };

void slv() {
    cin >> n;
    tot = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        tot += a[i];
        g[i].clear();
        ans[i] = vis[i] = 0;
    }
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        g[u].pb(v); g[v].pb(u);
    }

    dfs1(1, 0, 0);
    bc[1] = 0;
    for (int i = 1; i <= n; ++i) bc[1] += a[i] * d[i];
    dfs2(1, 0);

    for (int i = 1; i <= n; ++i) {
        if (vis[i] || (p[i] && hvy[p[i]] == i)) continue;
        vector<int> path;
        int cur = i;
        while (cur) {
            path.pb(cur);
            vis[cur] = 1;
            cur = hvy[cur];
        }

        int L = path.size();
        int dpth = d[path[L - 1]];
        int bst_off = 0;

        for (int j = L - 1; j >= 0; --j) {
            int u = path[j], val = 0;
            for (int v : g[u]) {
                if (v != p[u] && v != hvy[u]) val = max(val, get_mx(v, dpth));
            }
            bst_off = max(bst_off, val);
            ans[u] = max(ans[u], bst_off);
        }

        if (L > 1) {
            slns.clear();
            for (int j = 0; j < L; ++j) {
                int u = path[j];
                slns.pb({{w[u], w[u] * (1 - d[u])}, j});
            }
            sort(slns.begin(), slns.end(), [](auto& x, auto& y) {
                if (x.first.m != y.first.m) return x.first.m < y.first.m;
                return x.first.c < y.first.c;
            });
            build(1, 0, L - 1);

            vector<Node> st;
            for (int j = L - 2; j >= 0; --j) {
                int V = m2[path[j]];
                int cl = j + 1, cr = j + 1;
                while (!st.empty() && st.back().v <= V) {
                    cr = st.back().r;
                    st.pop_back();
                }
                int mx = qry(1, 0, L - 1, cl, cr, V);
                int bst = mx;
                if (!st.empty()) bst = max(bst, st.back().bst);
                st.pb({cl, cr, V, mx, bst});
                ans[path[j]] = max(ans[path[j]], st.back().bst);
            }
        }
    }

    for (int i = 1; i <= n; ++i) cout << bc[i] + ans[i] << (i == n ? "" : " ");
    cout << "\n";
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) slv();
    return 0;
}