# Tree Algorithms

---

## 1. Traversals

### 1.1 DFS with Subtree Size Computation

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> sz(n, 1), depth(n, 0), parent(n, -1);

    function<void(int, int)> dfs = [&](int v, int par) {
        parent[v] = par;
        for (int u : adj[v]) {
            if (u == par) continue;
            depth[u] = depth[v] + 1;
            dfs(u, v);
            sz[v] += sz[u];
        }
    };

    dfs(0, -1);
    return 0;
}
```

### 1.2 Iterative Tree DP (for large trees where recursion depth may exceed the stack limit)

```cpp
// Iterative tree DP using topological order (leaves first)
vector<int> order;  // BFS order
order.reserve(n);
vector<int> par(n, -1);
{
    queue<int> q;
    q.push(root);
    vector<bool> vis(n, false);
    vis[root] = true;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        order.push_back(v);
        for (int u : adj[v]) {
            if (!vis[u]) {
                vis[u] = true;
                par[u] = v;
                q.push(u);
            }
        }
    }
}

// Process in reverse BFS order (children before parents)
vector<long long> dp(n, 0);
for (int i = (int)order.size() - 1; i >= 0; i--) {
    int v = order[i];
    // dp[v] = base value
    for (int u : adj[v]) {
        if (u == par[v]) continue;
        // dp[v] = combine(dp[v], dp[u])
    }
}
```

---

## 2. Lowest Common Ancestor (LCA)

### 2.1 Definition and Basic Properties

**Definition.** Given a rooted tree T with root r, the *lowest common ancestor*
(LCA) of vertices u and v is the deepest vertex that is an ancestor of both u and v:

    LCA(u, v) = argmax_{w : w is ancestor of both u and v} depth(w)

This is well-defined since r is a common ancestor of all vertices, and the set of
common ancestors forms a path from r to LCA(u, v).

### Existence and uniqueness

**Existence:** r is a common ancestor of every pair (r lies on every
root-to-vertex path). So the set of common ancestors is non-empty.

**Uniqueness of the deepest:** Let S = set of common ancestors of u and v.
S is a subset of the vertices on the path from r to u, and also a
subset of the vertices on the path from r to v. These two paths share a
common prefix starting at r (they agree until they diverge). S is exactly
this common prefix. A path-prefix has a unique deepest element (the last
vertex in the prefix). That vertex is LCA(u, v).

### LCA lies on the path from u to v

**Theorem.** LCA(u, v) lies on the unique simple path from u to v.

**Proof.** The path from u to v in the tree is:
```
u -> ... -> LCA(u,v) -> ... -> v
```
More precisely, the unique path from u to v is the concatenation of:
- the path from u up to LCA(u,v) (reversing part of the root-to-u path)
- the path from LCA(u,v) down to v (part of the root-to-v path)

This is because the unique path from u to v must pass through some
common ancestor (the paths from r to u and r to v must merge somewhere).
The deepest such merge point is LCA(u,v).

### The path does not go above LCA

**Claim:** The path from u to v does not pass through any proper ancestor
of LCA(u,v).

**Proof by contradiction:** Suppose the path passes through w, a proper
ancestor of LCA(u,v). Then w is a common ancestor of u and v (it lies on
paths from r to both). But depth(w) < depth(LCA(u,v)), contradicting the
definition of LCA as the deepest common ancestor. (The path from u to v
passes through w which is above LCA, meaning the path goes up past LCA
and comes back down, but that would mean u and v have a common ancestor
deeper than LCA on a different branch -- impossible by the unique-path
property.)

### Distance formula

**Theorem.**

    dist(u, v) = depth(u) + depth(v) - 2 * depth(LCA(u, v))

**Proof.** The path from u to v goes from u up to LCA(u,v) and then
down to v.
- Ascending portion: depth(u) - depth(LCA(u,v)) edges.
- Descending portion: depth(v) - depth(LCA(u,v)) edges.
- Total = depth(u) - depth(LCA) + depth(v) - depth(LCA)
        = depth(u) + depth(v) - 2 * depth(LCA). QED.

### 2.2 Method 1: Binary Lifting

**Idea.** Precompute, for each vertex v and each power of two k, the 2^k-th ancestor of v. This allows jumping up the tree in O(log n) steps.

**Preprocessing.** Define:

    up[v][0] = par(v)            (the parent of v; up[r][0] = r or sentinel)
    up[v][k] = up[up[v][k-1]][k-1]   for k >= 1

**Correctness of recurrence.** The 2^k-th ancestor of v is the 2^{k-1}-th ancestor of the 2^{k-1}-th ancestor of v. This follows from the fact that 2^k = 2^{k-1} + 2^{k-1}: climbing 2^{k-1} steps twice is the same as climbing 2^k steps.

**Space:** O(n log n). **Time for preprocessing:** O(n log n).

**LCA Query Algorithm:**

```
LCA(u, v):
    1. Ensure depth(u) >= depth(v) (swap if needed).
    2. Lift u to the same depth as v:
       Let diff = depth(u) - depth(v).
       For each bit k set in diff: u <- up[u][k].
    3. If u == v, return u.
    4. For k = floor(log n) down to 0:
       If up[u][k] != up[v][k]:
           u <- up[u][k]
           v <- up[v][k]
    5. Return up[u][0] = par(u).
```

**Proof of correctness (Step 4).** After Step 2, u and v are at the same depth. We want the deepest vertex that is a common ancestor. Step 4 maintains the invariant:

    *Invariant:* LCA(u, v) is a proper ancestor of the current u and v (i.e., u != v and par(u) is a common ancestor).

At each iteration, we check whether jumping 2^k steps lands both u and v on the same vertex. If up[u][k] == up[v][k], the LCA is at or below that point, so we do NOT jump (that would overshoot). If up[u][k] != up[v][k], the LCA is strictly above 2^k steps from the current position, so we jump both to get closer.

After processing all k from high to low, u and v are the deepest pair of distinct vertices sharing a parent. That parent is the LCA.

**Why top-down bit processing works.** The jump distances 2^{floor(log n)}, ..., 2^1, 2^0 form a complete system: any distance d < n can be expressed as a sum of distinct powers of two. By greedily trying the largest jump first, we efficiently find the correct total jump distance.

**Query time:** O(log n).

```cpp
const int LOG = 20;  // sufficient for n <= 10^6
int up[200005][LOG];
int dep[200005];

void build_lca(int root, const vector<vector<int>>& adj, int n) {
    // BFS-based preprocessing (iterative, avoids stack overflow)
    vector<int> order;
    order.reserve(n);
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(root);
    visited[root] = true;
    dep[root] = 0;
    up[root][0] = root;

    while (!q.empty()) {
        int v = q.front(); q.pop();
        order.push_back(v);
        for (int u : adj[v]) {
            if (!visited[u]) {
                visited[u] = true;
                dep[u] = dep[v] + 1;
                up[u][0] = v;
                q.push(u);
            }
        }
    }

    // Fill binary lifting table
    for (int k = 1; k < LOG; k++)
        for (int v : order)
            up[v][k] = up[up[v][k-1]][k-1];
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int diff = dep[u] - dep[v];
    for (int k = 0; k < LOG; k++)
        if ((diff >> k) & 1)
            u = up[u][k];
    if (u == v) return u;
    for (int k = LOG - 1; k >= 0; k--)
        if (up[u][k] != up[v][k]) {
            u = up[u][k];
            v = up[v][k];
        }
    return up[u][0];
}

int dist(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}
```

### 2.3 Method 2: Euler Tour + Sparse Table (RMQ)

**Construction.** Perform a DFS on the rooted tree, recording the current vertex each time it is visited (both on entry and when returning from each child). This produces an Euler tour of length 2n - 1.

**Key observation.** Let first[v] be the index of the first occurrence of v in the Euler tour. Then:

    LCA(u, v) = the vertex with minimum depth among all vertices in the
                Euler tour between positions first[u] and first[v].

**Proof.** Between the first occurrence of u and the first occurrence of v in the Euler tour, the DFS visits exactly the vertices on the path from u to v via their LCA (plus possibly some detours into subtrees, which are deeper). The shallowest vertex in this segment is precisely the LCA, since:
1. The LCA must appear in this segment (the DFS must pass through it when moving between the subtrees containing u and v).
2. No ancestor of the LCA appears in this segment (the DFS is entirely within the subtree rooted at the LCA during this interval).

**Reduction to RMQ.** The LCA query reduces to a range minimum query on the depth array indexed by the Euler tour. Using a sparse table (precomputed in O(n log n)), each RMQ is answered in O(1).

**Total complexity.** O(n log n) preprocessing, O(1) per LCA query.

---

## 3. Euler Tour Linearization

### 3.1 Motivation

**The key idea.** Flatten a rooted tree into a one-dimensional array so that subtree operations become range operations. This allows us to use powerful 1D data structures (segment trees, BITs, etc.) on tree problems.

### 3.2 Type 1: Entry + Exit Times

Perform a DFS from the root, maintaining a global timer. Record:
- tin[v] = timer value when DFS enters v.
- tout[v] = timer value when DFS exits v (after exploring all descendants).

**Theorem.** Vertex u is a descendant of v (i.e., u in T(v)) if and only if tin[v] <= tin[u] and tout[u] <= tout[v].

**Proof.** (=>) If u is a descendant of v, DFS enters v before u (so tin[v] <= tin[u]) and exits u before v (so tout[u] <= tout[v]).

(<=) If tin[v] <= tin[u] and tout[u] <= tout[v], then the DFS interval of u is contained within that of v. Since DFS intervals are either disjoint or nested (a consequence of the DFS structure), u must be in the subtree of v. QED.

**Corollary.** The subtree of v corresponds to the range [tin[v], tout[v]] in the timer array.

**Application.** Place vertex values at position tin[v] in an array A. A subtree sum query for v becomes a range sum query on A[tin[v]..tout[v]]. With a BIT or segment tree, both point updates and subtree queries run in O(log n).

### 3.3 Type 2: Entry-Only (Compact) Euler Tour

Record only tin[v] and compute subtree_size[v] (via DFS). The subtree of v occupies positions:

    [tin[v], tin[v] + subtree_size[v] - 1]

**Proof.** By the DFS property, all descendants of v are visited consecutively starting from tin[v]. There are subtree_size[v] vertices in total (including v), so they occupy exactly subtree_size[v] consecutive positions. QED.

This is more space-efficient (array length n vs. 2n) and is sufficient for most subtree query problems.

### 3.4 Type 3: Full Euler Tour for LCA

Record the current vertex at every step of the DFS (on entry and on each return from a child). The resulting sequence has length 2n - 1.

As described in Section 2.3, LCA(u, v) reduces to finding the minimum-depth vertex in a range, which is a Range Minimum Query. Solved in O(1) per query after O(n log n) preprocessing with a sparse table.

### 3.5 Proof That Subtrees Map to Contiguous Ranges

**Theorem.** In a DFS of a rooted tree, the entry times of the vertices in any subtree T(v) form a contiguous range of integers.

**Proof.** We prove that during the DFS, between entering v and leaving v, exactly the vertices in T(v) are entered (and no others).

By the DFS algorithm, after entering v, we recursively visit each child of v in sequence. The recursion for a child c fully explores T(c) before moving to the next child. All vertices entered during this process are descendants of v (since DFS does not jump to non-adjacent vertices). Conversely, every descendant of v is visited during this interval (since DFS explores all children). Therefore, the set of entry times {tin[u] : u in T(v)} equals {tin[v], tin[v]+1, ..., tin[v]+|T(v)|-1}. QED.

```cpp
int timer = 0;
vector<int> tin(n), tout(n), sz(n);

function<void(int, int)> euler_tour = [&](int v, int par) {
    tin[v] = timer++;
    sz[v] = 1;
    for (int u : adj[v]) {
        if (u == par) continue;
        euler_tour(u, v);
        sz[v] += sz[u];
    }
    tout[v] = timer - 1;  // tout[v] = tin[v] + sz[v] - 1
};

euler_tour(root, -1);
```

---

## 4. Binary Lifting Beyond LCA

### 4.1 The General Technique

Binary lifting exploits the binary representation of integers to decompose a "walk k steps" query into O(log k) precomputed jumps.

**Requirement.** A structure where each element has a well-defined "next" element (a function f: S -> S). Precompute:

    jump[x][0] = f(x)
    jump[x][k] = jump[jump[x][k-1]][k-1]

Then, applying f exactly k times from x:

    f^k(x) = apply jumps for each set bit in the binary representation of k.

### 4.2 k-th Ancestor Queries

**Problem.** Given a rooted tree and queries (v, k), find the k-th ancestor of v.

**Solution.** Use the binary lifting table up[v][k] from Section 2.2. To find the k-th ancestor:

```cpp
int kth_ancestor(int v, int k) {
    for (int i = 0; i < LOG; i++)
        if ((k >> i) & 1)
            v = up[v][i];
    return v;  // returns -1 or sentinel if k > depth(v)
}
```

**Time:** O(log n) per query.

### 4.3 Weighted Path Queries via Binary Lifting

**Problem.** Given a weighted tree, answer queries of the form: "What is the maximum (or minimum, or sum) edge weight on the path from u to v?"

**Solution.** Alongside the ancestor table, maintain:

    max_edge[v][k] = maximum edge weight on the path from v to its 2^k-th ancestor.

Recurrence:

    max_edge[v][0] = weight(v, par(v))
    max_edge[v][k] = max(max_edge[v][k-1], max_edge[up[v][k-1]][k-1])

To answer a query (u, v): find LCA(u, v) using binary lifting, accumulating the max edge weight along both upward paths.

### 4.4 Functional Graphs

**Definition.** A *functional graph* is a directed graph where every vertex has out-degree exactly 1. Equivalently, it is defined by a function f: {0,...,n-1} -> {0,...,n-1}.

**Structure.** A functional graph consists of several connected components, each containing exactly one cycle, with trees hanging off the cycle vertices (like a "rho" shape).

**Binary lifting on functional graphs.** The table jump[v][k] = f^{2^k}(v) allows computing f^m(v) in O(log m) for any m. This is useful for problems like "where does a particle end up after m steps?"

---

## 5. Path Decomposition in Rooted Trees

Given vertices u and v with LCA(u,v) = w:

### Case 1: w = v (equivalently, v is an ancestor of u)

The entire path from u to v lies within the subtree rooted at v.
The path is simply u ascending to v. No "turning point" branching into
two subtrees is needed.

### Case 2: w != u and w != v

Let c_u = the child of w on the path from w to u (i.e., the child of w
whose subtree contains u). Let c_v = the child of w on the path from w
to v (i.e., the child of w whose subtree contains v).

Since w = LCA and w != u, w != v, c_u and c_v are distinct children of w.

The path from u to v decomposes as:
```
(ascend from u through T(c_u) up to w) + (descend from w through T(c_v) down to v)
```

The ascending and descending portions pass through two distinct subtrees
of w: T(c_u) and T(c_v).

### Summary

> "Every simple path in a rooted tree either lies entirely within one
> subtree (when one endpoint is an ancestor of the other), or has a
> unique turning point at the LCA, passing through exactly two distinct
> child-subtrees of the LCA."

---

## 6. Code Templates

### 6.1 Double BFS for Diameter

```cpp
pair<int, int> bfs_farthest(int src, const vector<vector<int>>& adj, int n) {
    vector<int> dist(n, -1);
    queue<int> q;
    dist[src] = 0;
    q.push(src);
    int farthest = src;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int u : adj[v]) {
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                q.push(u);
                if (dist[u] > dist[farthest])
                    farthest = u;
            }
        }
    }
    return {farthest, dist[farthest]};
}

int tree_diameter(const vector<vector<int>>& adj, int n) {
    auto [u, _1] = bfs_farthest(0, adj, n);
    auto [v, diam] = bfs_farthest(u, adj, n);
    return diam;
}
```

### 6.2 Euler Tour Computation

```cpp
int timer = 0;
vector<int> tin, tout, euler_order, sz;

void euler_tour(int v, int par, const vector<vector<int>>& adj) {
    tin[v] = timer++;
    euler_order.push_back(v);
    sz[v] = 1;
    for (int u : adj[v]) {
        if (u == par) continue;
        euler_tour(u, v, adj);
        sz[v] += sz[u];
    }
    tout[v] = timer - 1;
}

// Usage:
// tin.resize(n); tout.resize(n); sz.resize(n);
// euler_order.reserve(n);
// euler_tour(root, -1, adj);
//
// Subtree of v: positions [tin[v], tout[v]] = [tin[v], tin[v] + sz[v] - 1]
// Ancestor check: u is ancestor of v iff tin[u] <= tin[v] && tout[v] <= tout[u]
```

---

## Summary of Complexities

| Algorithm                        | Preprocessing | Per Query |
|----------------------------------|---------------|-----------|
| Diameter (DP)                    | O(n)          | --        |
| Diameter (Double BFS)            | O(n)          | --        |
| Tree Center (Peeling)            | O(n)          | --        |
| LCA (Binary Lifting)            | O(n log n)    | O(log n)  |
| LCA (Euler Tour + Sparse Table) | O(n log n)    | O(1)      |
| k-th Ancestor (Binary Lifting)  | O(n log n)    | O(log n)  |
| Subtree Query (Euler Tour + BIT)| O(n)          | O(log n)  |
| Rerooting DP                    | O(n)          | --        |
