# Tree Algorithms: A Rigorous Guide

---

## Section 1: Tree Theory -- Formal Foundations

### 1.1 Definition

**Definition 1.1.** A *tree* is a connected, acyclic, undirected graph. Equivalently, a tree on n vertices is a graph in which every pair of vertices is connected by exactly one simple path.

### 1.2 The Fundamental Characterization Theorem

**Theorem 1.2 (Three-Property Characterization).** Let G = (V, E) be a graph with |V| = n >= 1. Consider the following three properties:

    (a) G is connected.
    (b) G is acyclic.
    (c) |E| = n - 1.

Any two of these properties imply the third.

**Proof.** We prove all three implications.

**(a) + (b) => (c):** Assume G is a connected acyclic graph (i.e., a tree). We proceed by induction on n.

- Base case: n = 1. The graph has 0 edges, and n - 1 = 0. Holds.
- Inductive step: Assume the result holds for all trees on fewer than n vertices. Since G is a finite tree with n >= 2 vertices, G has a leaf v (a vertex of degree 1). To see why a leaf must exist: start at any vertex and walk along edges without repeating; since G is acyclic, the walk must terminate, and it terminates at a leaf.

  Remove v and its incident edge to obtain G' on n - 1 vertices. G' is still connected (v was a leaf, so removing it disconnects nothing) and still acyclic (removing edges cannot create cycles). By the inductive hypothesis, |E(G')| = (n-1) - 1 = n - 2. Therefore |E(G)| = n - 2 + 1 = n - 1.

**(a) + (c) => (b):** Assume G is connected with |E| = n - 1. Suppose for contradiction that G contains a cycle C. Removing any edge e from C yields a graph G' that is still connected (since the endpoints of e remain connected via the rest of C) with n vertices and n - 2 edges. But a connected graph on n vertices requires at least n - 1 edges (since a spanning tree has exactly n - 1 edges, and any connected graph contains a spanning tree). This gives n - 2 >= n - 1, a contradiction. Therefore G is acyclic.

**(b) + (c) => (a):** Assume G is acyclic with |E| = n - 1. Let G have k connected components, with component i having n_i vertices. Each component is a connected acyclic graph (a tree), so by (a)+(b)=>(c), component i has n_i - 1 edges. The total number of edges is:

    |E| = sum_{i=1}^{k} (n_i - 1) = n - k

Since |E| = n - 1, we get n - k = n - 1, hence k = 1. G is connected. QED.

### 1.3 Rooted Trees

**Definition 1.3.** A *rooted tree* is a tree T = (V, E) with a distinguished vertex r in V called the root. Choosing r induces a hierarchical structure:

- For every vertex v != r, the *parent* of v, denoted par(v), is the next vertex on the unique path from v to r.
- The *children* of v are children(v) = {u in V : par(u) = v}.
- The *depth* of v is depth(v) = dist(r, v), the length of the unique path from r to v.
- An *ancestor* of v is any vertex on the path from v to r (inclusive of both v and r).

**Observation.** Rooting transforms an undirected tree into a directed tree where every edge is implicitly directed from child to parent (or equivalently, from parent to child). The choice of root is arbitrary but completely determines the parent-child structure.

### 1.4 Subtrees

**Definition 1.4.** The *subtree rooted at v*, denoted T(v), is the subgraph of T induced by v and all descendants of v. Formally, T(v) = T[{u in V : v lies on the path from u to r}].

The *subtree size* of v is |T(v)|, the number of vertices in the subtree rooted at v.

### 1.5 Leaf Detection

**Definition 1.5.** In an unrooted tree, a vertex v is a *leaf* if deg(v) = 1.

In a rooted tree, v is a leaf if children(v) = {}, i.e., v has no children.

**Implementation note.** In adjacency-list representation of a rooted tree, after removing the parent edge, v is a leaf iff it has no children. In practice, during DFS from the root, v is a leaf if adj[v] contains only the parent of v (or adj[v] is empty, which only happens if v = root and n = 1). A common guard:

```cpp
// v is a leaf if its only neighbor is its parent
if (adj[v].size() == 1 && v != root) {
    // v is a leaf
}
```

When the root has degree 0 (n = 1), it is both root and leaf. When par is stored as -1 for the root, ensure the parent-check guard handles this.

---

## Section 2: Tree Diameter -- Theory and Algorithms

### 2.1 Definition

**Definition 2.1.** The *diameter* of a tree T is

    diam(T) = max_{u,v in V} dist(u, v)

where dist(u, v) is the number of edges on the unique path from u to v (unweighted case), or the sum of edge weights (weighted case).

A path achieving this maximum is called a *diametral path*, and its endpoints are *diametral endpoints*.

### 2.2 Algorithm 1: DP on the Tree

**Idea.** Root the tree at an arbitrary vertex. For each vertex v, the longest path passing through v consists of descending into two different subtrees of v. The diameter is the maximum such value over all v.

**Formal recurrence.** Let the tree be rooted at vertex r. For each vertex v, define:

    h(v) = height of subtree rooted at v = max distance from v to any descendant of v.

Base case: h(v) = 0 if v is a leaf.

Recurrence: h(v) = 1 + max_{c in children(v)} h(c).

For each vertex v, let max_1(v) and max_2(v) be the two largest values in the multiset {h(c) + 1 : c in children(v)}, with max_2(v) = 0 if v has fewer than 2 children.

The longest path passing through v as the highest point is:

    through(v) = max_1(v) + max_2(v)

The diameter is:

    diam(T) = max_{v in V} through(v)

**Correctness proof.** Every path in the tree has a unique highest vertex (the vertex closest to the root). If the highest vertex is v, the path descends into at most two children of v (it cannot enter the same child twice, as that would create a cycle in the path). The longest such path uses the two deepest subtrees. Since we maximize over all v, we find the global diameter.

**Complexity.** O(n) time and space.

```cpp
int diameter = 0;
vector<int> height(n, 0);

function<void(int, int)> dfs = [&](int v, int par) {
    int max1 = 0, max2 = 0;  // two largest child heights + 1
    for (int u : adj[v]) {
        if (u == par) continue;
        dfs(u, v);
        int val = height[u] + 1;
        if (val >= max1) { max2 = max1; max1 = val; }
        else if (val > max2) { max2 = val; }
    }
    height[v] = max1;
    diameter = max(diameter, max1 + max2);
};

dfs(0, -1);
```

### 2.3 Algorithm 2: Double BFS/DFS

**Algorithm.**
1. Run BFS (or DFS) from an arbitrary vertex s. Let u be the vertex at maximum distance from s.
2. Run BFS (or DFS) from u. Let v be the vertex at maximum distance from u.
3. Return dist(u, v) as the diameter.

**Theorem 2.3.** The double-BFS algorithm correctly computes the diameter of a tree.

**Proof.** Let P = (a, ..., b) be a diametral path with dist(a, b) = diam(T) = D.

**Claim:** u (the farthest vertex from s) is a diametral endpoint.

*Case 1: s lies on P.* Then dist(s, a) + dist(s, b) = D. WLOG dist(s, a) >= dist(s, b), so dist(s, a) >= D/2. Since u is farthest from s, dist(s, u) >= dist(s, a) >= D/2. Now consider the path from u to b. The paths s -> u and s -> b diverge at some vertex w on the s -> a portion or the s -> b portion of P. In either case:

    dist(u, b) = dist(u, w) + dist(w, b)

Since s -> w is common to both paths s -> u and s -> b:

    dist(s, u) = dist(s, w) + dist(w, u)
    dist(s, b) = dist(s, w) + dist(w, b)

From dist(s, u) >= dist(s, a):

    dist(w, u) >= dist(w, a)  [since dist(s,w) cancels if w is on P between s and a]

Therefore:

    dist(u, b) = dist(u, w) + dist(w, b) >= dist(a, w) + dist(w, b) = dist(a, b) = D

Since no path can exceed the diameter, dist(u, b) = D. So u is a diametral endpoint.

*Case 2: s does not lie on P.* Let x be the vertex on P closest to s (this is well-defined since the tree has unique paths). Then:

    dist(s, a) = dist(s, x) + dist(x, a)
    dist(s, b) = dist(s, x) + dist(x, b)

WLOG dist(x, a) >= dist(x, b). Since u is farthest from s:

    dist(s, u) >= dist(s, a) = dist(s, x) + dist(x, a)

Let the path from s to u meet the path from s to x at some vertex y (possibly y = s). Since the tree is acyclic, the path s -> x first goes s -> y -> ... -> x and the path s -> u goes s -> y -> ... -> u, with the portions after y being disjoint.

Now:

    dist(u, b) >= dist(u, y) + dist(y, x) + dist(x, b)
              = (dist(s, u) - dist(s, y)) + dist(y, x) + dist(x, b)

And:

    dist(s, a) = dist(s, y) + dist(y, x) + dist(x, a)

Since dist(s, u) >= dist(s, a):

    dist(u, y) = dist(s, u) - dist(s, y) >= dist(s, a) - dist(s, y) = dist(y, x) + dist(x, a)

Therefore:

    dist(u, b) >= dist(y, x) + dist(x, a) + dist(y, x) + dist(x, b)
              >= dist(x, a) + dist(x, b)    [since dist(y,x) >= 0]
              = D

Again, dist(u, b) = D, so u is a diametral endpoint.

In the second BFS from u, we find v = argmax dist(u, .), so dist(u, v) >= dist(u, b) = D. Since D is the diameter, dist(u, v) = D. QED.

**Complexity.** O(n) (two BFS/DFS traversals).

### 2.4 Diameter Center

**Definition 2.4.** The *center* of a tree is the set of vertices that minimize the eccentricity, where ecc(v) = max_{u in V} dist(v, u).

**Theorem 2.5 (Jordan, 1869).** The center of a tree consists of either one vertex or two adjacent vertices, and it lies at the midpoint of every diametral path.

**Proof sketch.** Let P = (v_0, v_1, ..., v_D) be a diametral path. Consider the vertex v_i on P that minimizes max(i, D-i), i.e., i = floor(D/2). This vertex has eccentricity ceil(D/2).

Any vertex w not on P has ecc(w) >= max(dist(w, v_0), dist(w, v_D)). Let x be the point where the path from w to v_0 meets P. Then dist(w, v_0) = dist(w, x) + dist(x, v_0) and dist(w, v_D) = dist(w, x) + dist(x, v_D). Since dist(x, v_0) + dist(x, v_D) = D, we have max(dist(w, v_0), dist(w, v_D)) >= dist(w, x) + D/2 > D/2 unless w is on P. So the center must lie on P, and specifically at the midpoint.

If D is even, there is one center vertex: v_{D/2}, with eccentricity D/2.
If D is odd, there are two center vertices: v_{(D-1)/2} and v_{(D+1)/2}, each with eccentricity (D+1)/2.

**Corollary.** All diametral paths share the same center. If two diameters had different midpoints, we could splice paths to create a path longer than D, contradicting the definition.

### 2.5 Topological Peeling Algorithm for the Center

**Algorithm.** Repeatedly remove all current leaves from the tree until 1 or 2 vertices remain.

**Proof of correctness.** Let L_0 be the set of leaves in the original tree. Every diametral endpoint is a leaf (otherwise, we could extend the path). After removing all leaves, the diameter decreases by exactly 2: one layer is peeled from each end of every diametral path. By induction, after k rounds of peeling, the diameter of the remaining tree is D - 2k. When D - 2k <= 1, the remaining 1 or 2 vertices form the center.

**Implementation.** This is equivalent to topological sort with initial degree-1 vertices:

```cpp
// Find tree center(s) via iterative leaf removal
vector<int> degree(n);
queue<int> leaves;
for (int i = 0; i < n; i++) {
    degree[i] = adj[i].size();
    if (degree[i] <= 1) leaves.push(i);
}
int remaining = n;
while (remaining > 2) {
    int sz = leaves.size();
    remaining -= sz;
    while (sz--) {
        int v = leaves.front(); leaves.pop();
        for (int u : adj[v]) {
            if (--degree[u] == 1) leaves.push(u);
        }
    }
}
// Remaining vertices are the center(s)
```

---

## Section 3: Lowest Common Ancestor (LCA)

### 3.1 Definition and Basic Properties

**Definition 3.1.** Given a rooted tree T with root r, the *lowest common ancestor* (LCA) of vertices u and v is the deepest vertex that is an ancestor of both u and v:

    LCA(u, v) = argmax_{w : w is ancestor of both u and v} depth(w)

This is well-defined since r is a common ancestor of all vertices, and the set of common ancestors forms a path from r to LCA(u, v).

**Theorem 3.2 (Distance via LCA).**

    dist(u, v) = depth(u) + depth(v) - 2 * depth(LCA(u, v))

**Proof.** The unique path from u to v in a tree goes up from u to LCA(u,v), then down to v. The upward portion has length depth(u) - depth(LCA(u,v)), and the downward portion has length depth(v) - depth(LCA(u,v)). Their sum gives the formula. QED.

### 3.2 Method 1: Binary Lifting

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
int up[MAXN][LOG], depth_arr[MAXN];

void dfs(int v, int p, int d) {
    up[v][0] = p;
    depth_arr[v] = d;
    for (int k = 1; k < LOG; k++)
        up[v][k] = up[up[v][k-1]][k-1];
    for (int u : adj[v])
        if (u != p) dfs(u, v, d + 1);
}

int lca(int u, int v) {
    if (depth_arr[u] < depth_arr[v]) swap(u, v);
    int diff = depth_arr[u] - depth_arr[v];
    for (int k = 0; k < LOG; k++)
        if ((diff >> k) & 1) u = up[u][k];
    if (u == v) return u;
    for (int k = LOG - 1; k >= 0; k--)
        if (up[u][k] != up[v][k]) {
            u = up[u][k];
            v = up[v][k];
        }
    return up[u][0];
}
```

### 3.3 Method 2: Euler Tour + Sparse Table (RMQ)

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

## Section 4: Tree DP -- The General Framework

### 4.1 The Principle

**Observation.** A rooted tree is a recursively defined structure: the tree rooted at v consists of v together with the subtrees rooted at each child of v. This recursive structure makes dynamic programming a natural fit.

**Principle.** For tree DP, the natural computation order is *post-order* (bottom-up): process all children of v before processing v itself. This is guaranteed by a DFS where the DP computation for v occurs after the recursive calls to all children.

**General form:**

    dp[v] = combine({dp[c] : c in children(v)}, info(v))

where `combine` is problem-specific and `info(v)` encodes local vertex/edge information.

### 4.2 Common Patterns

**Pattern 1: Subtree Aggregation.**

    dp[v] = f(v) + sum_{c in children(v)} dp[c]

Example: counting the number of vertices, sum of values, or number of leaves in a subtree. The function f(v) contributes the local information at v.

**Pattern 2: Subtree Optimization.**

    dp[v] = optimize_{valid configurations} g(dp[c_1], ..., dp[c_k], info(v))

Example: maximum independent set on a tree. Define dp[v][0] = max independent set in T(v) not including v, dp[v][1] = ... including v. Then:

    dp[v][0] = sum_{c} max(dp[c][0], dp[c][1])
    dp[v][1] = val(v) + sum_{c} dp[c][0]

**Pattern 3: Diameter-like (tracking two best values).**

The DP returns one value (e.g., height), but a global answer is updated using two best values from children. The diameter algorithm (Section 2.2) is the archetype. This pattern appears whenever the answer is a "path through some vertex" and requires combining two descending paths.

**Pattern 4: Balance / comparison of subtrees.**

    dp[v] = some balance measure, parent aggregates and compares children's values.

Example: checking if a tree is balanced (|h(left) - h(right)| <= 1 at every node).

### 4.3 General Skeleton

```cpp
vector<long long> dp(n, 0);

function<void(int, int)> dfs = [&](int v, int par) {
    // Initialize dp[v] with base case / local info
    dp[v] = /* base value */;
    for (int u : adj[v]) {
        if (u == par) continue;
        dfs(u, v);
        // Combine dp[u] into dp[v]
        dp[v] = combine(dp[v], dp[u]);
    }
    // Possibly update a global answer using dp[v]
};

dfs(root, -1);
```

---

## Section 5: Rerooting DP

### 5.1 The Problem

**Problem.** For each vertex v in V, compute f(v) = the answer to some query assuming v is the root.

**Naive approach.** For each v, re-root the tree and run tree DP. Time: O(n^2).

**Efficient approach.** Two-pass rerooting in O(n).

### 5.2 The Two-Pass Algorithm

**Key insight.** When we move the root from v to a child c, the only structural change is:
- c's subtree loses c (it becomes the new root), and gains everything outside the old subtree of c.
- v's contribution to c changes from "parent" to "child in c's subtree."

We can precompute enough information to handle this transition in O(1) per vertex.

**Pass 1 (Down pass).** Root the tree at vertex 1. Compute dp_down[v] for each v via standard tree DP.

    dp_down[v] = combine({dp_down[c] + edge(v,c) : c in children(v)})

This captures information from the subtree below v.

**Pass 2 (Up/Reroot pass).** For each vertex v with parent p, compute dp_up[v] = the contribution from everything outside T(v). When v is the root, its answer uses both dp_down[v] (its subtree) and nothing else. When a child c of v becomes the root, c's answer combines:
- dp_down[c] (its original subtree, unchanged), and
- the rest of the tree = dp_up[v] combined with contributions from all siblings of c.

Formally:

    dp_up[c] = combine(dp_up[v], {dp_down[s] + edge(v,s) : s in children(v), s != c}) + edge(v,c)

The final answer for each vertex v is:

    f(v) = combine(dp_down[v], dp_up[v])

### 5.3 The Subtraction Requirement

**Critical requirement.** To compute the sibling contributions efficiently (excluding one child), we need the combine operation to be "invertible" or "subtractable."

**Case 1: combine = sum.** To get the sum of all children's values except c, compute total_sum - dp_down[c]. O(1).

**Case 2: combine = max.** We cannot simply subtract the max. Instead, store the top two maximum values among children. If c contributed the maximum, use the second maximum. O(1) with O(k) preprocessing per vertex (where k is the number of children).

**Case 3: combine = product.** If dp_down[c] != 0, divide. If dp_down[c] = 0, count zeros: if more than one zero, the product-excluding-c is 0; if exactly one zero (which is c), the product-excluding-c is the product of nonzero terms.

**General solution with prefix/suffix arrays.** For any associative combine operation, precompute prefix[i] = combine(dp_down[c_1], ..., dp_down[c_i]) and suffix[i] = combine(dp_down[c_i], ..., dp_down[c_k]). Then:

    combine_excluding_c_i = combine(prefix[i-1], suffix[i+1])

This works in O(k) per vertex (total O(n) over the whole tree), regardless of whether the operation is invertible.

### 5.4 Complexity

Both passes visit each vertex once, and the work per vertex is proportional to its degree. Total: O(n).

---

## Section 6: Euler Tour Linearization

### 6.1 Motivation

**The key idea.** Flatten a rooted tree into a one-dimensional array so that subtree operations become range operations. This allows us to use powerful 1D data structures (segment trees, BITs, etc.) on tree problems.

### 6.2 Type 1: Entry + Exit Times

Perform a DFS from the root, maintaining a global timer. Record:
- tin[v] = timer value when DFS enters v.
- tout[v] = timer value when DFS exits v (after exploring all descendants).

**Theorem 6.1.** Vertex u is a descendant of v (i.e., u in T(v)) if and only if tin[v] <= tin[u] and tout[u] <= tout[v].

**Proof.** (=>) If u is a descendant of v, DFS enters v before u (so tin[v] <= tin[u]) and exits u before v (so tout[u] <= tout[v]).

(<=) If tin[v] <= tin[u] and tout[u] <= tout[v], then the DFS interval of u is contained within that of v. Since DFS intervals are either disjoint or nested (a consequence of the DFS structure), u must be in the subtree of v. QED.

**Corollary.** The subtree of v corresponds to the range [tin[v], tout[v]] in the timer array.

**Application.** Place vertex values at position tin[v] in an array A. A subtree sum query for v becomes a range sum query on A[tin[v]..tout[v]]. With a BIT or segment tree, both point updates and subtree queries run in O(log n).

### 6.3 Type 2: Entry-Only (Compact) Euler Tour

Record only tin[v] and compute subtree_size[v] (via DFS). The subtree of v occupies positions:

    [tin[v], tin[v] + subtree_size[v] - 1]

**Proof.** By the DFS property, all descendants of v are visited consecutively starting from tin[v]. There are subtree_size[v] vertices in total (including v), so they occupy exactly subtree_size[v] consecutive positions. QED.

This is more space-efficient (array length n vs. 2n) and is sufficient for most subtree query problems.

### 6.4 Type 3: Full Euler Tour for LCA

Record the current vertex at every step of the DFS (on entry and on each return from a child). The resulting sequence has length 2n - 1.

As described in Section 3.3, LCA(u, v) reduces to finding the minimum-depth vertex in a range, which is a Range Minimum Query. Solved in O(1) per query after O(n log n) preprocessing with a sparse table.

### 6.5 Proof That Subtrees Map to Contiguous Ranges

**Theorem 6.2.** In a DFS of a rooted tree, the entry times of the vertices in any subtree T(v) form a contiguous range of integers.

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

## Section 7: Binary Lifting Beyond LCA

### 7.1 The General Technique

Binary lifting exploits the binary representation of integers to decompose a "walk k steps" query into O(log k) precomputed jumps.

**Requirement.** A structure where each element has a well-defined "next" element (a function f: S -> S). Precompute:

    jump[x][0] = f(x)
    jump[x][k] = jump[jump[x][k-1]][k-1]

Then, applying f exactly k times from x:

    f^k(x) = apply jumps for each set bit in the binary representation of k.

### 7.2 k-th Ancestor Queries

**Problem.** Given a rooted tree and queries (v, k), find the k-th ancestor of v.

**Solution.** Use the binary lifting table up[v][k] from Section 3.2. To find the k-th ancestor:

```cpp
int kth_ancestor(int v, int k) {
    for (int i = 0; i < LOG; i++)
        if ((k >> i) & 1)
            v = up[v][i];
    return v;  // returns -1 or sentinel if k > depth(v)
}
```

**Time:** O(log n) per query.

### 7.3 Weighted Path Queries via Binary Lifting

**Problem.** Given a weighted tree, answer queries of the form: "What is the maximum (or minimum, or sum) edge weight on the path from u to v?"

**Solution.** Alongside the ancestor table, maintain:

    max_edge[v][k] = maximum edge weight on the path from v to its 2^k-th ancestor.

Recurrence:

    max_edge[v][0] = weight(v, par(v))
    max_edge[v][k] = max(max_edge[v][k-1], max_edge[up[v][k-1]][k-1])

To answer a query (u, v): find LCA(u, v) using binary lifting, accumulating the max edge weight along both upward paths.

### 7.4 Functional Graphs

**Definition 7.1.** A *functional graph* is a directed graph where every vertex has out-degree exactly 1. Equivalently, it is defined by a function f: {0,...,n-1} -> {0,...,n-1}.

**Structure.** A functional graph consists of several connected components, each containing exactly one cycle, with trees hanging off the cycle vertices (like a "rho" shape).

**Binary lifting on functional graphs.** The table jump[v][k] = f^{2^k}(v) allows computing f^m(v) in O(log m) for any m. This is useful for problems like "where does a particle end up after m steps?"

---

## Section 8: Key Code Templates

### 8.1 DFS with Subtree Size Computation

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

### 8.2 Binary Lifting Preprocessing + LCA

```cpp
const int LOG = 20;
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

### 8.3 Euler Tour Computation

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

### 8.4 Tree DP Skeleton (Iterative)

For large trees where recursion depth may exceed the stack limit:

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

### 8.5 Double BFS for Diameter

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
