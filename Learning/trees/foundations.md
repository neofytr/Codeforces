# Tree Theory: Foundations

---

## 1. Tree Equivalences

Let G = (V, E) be a graph with n = |V| vertices and m = |E| edges.
The following seven statements are equivalent. Any one of them can serve
as the definition of "tree".

```
(1) G is a tree.
(2) G is connected and acyclic.
(3) G is acyclic and m = n - 1.
(4) G is connected and m = n - 1.
(5) There is a unique simple path between every pair of vertices in G.
(6) G is connected and removing any single edge disconnects it.
(7) G is acyclic and adding any single edge creates exactly one cycle.
```

### Proof of the equivalence cycle

**(2) => (3):**
Connected + acyclic. Induction on n. Base: n = 1, m = 0 = n - 1. Step:
a tree with n >= 2 vertices has a leaf (degree-1 vertex; must exist because
a connected acyclic graph with all degrees >= 2 would contain a cycle).
Remove the leaf and its edge: remaining graph is still connected and acyclic,
so by induction has (n-1) - 1 = n - 2 edges. Add the leaf back: m = n - 1.

**(3) => (4):**
Acyclic + m = n - 1. Suppose G is not connected. Then G has k >= 2
connected components, each a tree (acyclic + connected within component).
Each component C_i has |E_i| = |V_i| - 1 edges. Summing: m = n - k.
But m = n - 1 forces k = 1, so G is connected.

**(4) => (5):**
Connected + m = n - 1. Suppose two distinct simple paths exist between
some pair u, v. Their union contains a cycle. Removing one edge of that
cycle keeps the graph connected (the alternative path survives), so we
get a connected graph with n vertices and n - 2 edges. But any connected
graph needs at least n - 1 edges (induction), contradiction. So paths
are unique.

**(5) => (6):**
Unique simple paths. Unique path => connected. If edge (u, v) is removed,
the unique path between u and v was that edge itself (since it was unique
and direct). No other path exists, so u and v are disconnected.

**(6) => (7):**
Connected + every edge is a bridge. Since every edge is a bridge, G is
acyclic (any edge in a cycle is not a bridge). Now add a new edge (u, v).
Since G was connected, a unique path P from u to v already exists.
P + (u, v) forms exactly one cycle. Exactly one, because if two distinct
cycles were created, removing the new edge would still leave a cycle in G,
contradicting acyclicity.

**(7) => (2):**
Acyclic + adding any edge creates exactly one cycle. The "adding any edge
creates a cycle" part means for every non-edge (u, v), a path from u to v
already exists in G (otherwise adding (u, v) would not create a cycle).
Combined with the edges themselves being paths, every pair of vertices is
connected. So G is connected. G is acyclic by assumption.

**(2) => (1):**
By definition.

---

## 2. Rooted Tree Definitions

Let T = (V, E) be a tree. Choose any vertex r in V as the **root**.
This is valid because T is connected, so r can reach all other vertices.

### Parent

For any vertex v != r, consider the unique simple path from r to v
(exists and is unique by equivalence (5)). The vertex immediately
preceding v on this path is the **parent** of v, written parent(v).

Well-defined: the path is unique, so the predecessor is unique.
Every non-root vertex has exactly one parent.

### Child

v is a **child** of u if parent(v) = u.

### Depth

depth(v) = length (number of edges) of the unique path from r to v.

Well-defined because the path is unique. depth(r) = 0.

### Ancestor

u is an **ancestor** of v if u lies on the unique path from r to v.

r is an ancestor of every vertex (the path from r to v starts at r).
Every vertex is an ancestor of itself.

### Descendant

v is a **descendant** of u if u is an ancestor of v.

This is the reverse of the ancestor relation.

### Subtree

The **subtree rooted at v**, written T(v), is the subgraph of T induced
by v and all its descendants.

**Claim:** T(v) is a tree.

**Proof:**

(1) *Acyclic:* T(v) is a subgraph of T. T is acyclic. Any subgraph of
an acyclic graph is acyclic.

(2) *Connected:* Take any two vertices a, b in T(v). Both are descendants
of v, so the unique path from r to a passes through v, and the unique
path from r to b passes through v. The unique path from a to b in T
is the concatenation of the path from a up to LCA(a,b) and down to b.
Since both a and b are descendants of v, their LCA is also a descendant
of v (or v itself), so the entire path from a to b stays within T(v).

Connected + acyclic => T(v) is a tree.

### Important meta-observation

> "Hierarchy is NOT part of the definition. It is a CONSEQUENCE of the
> unique path property."

The parent-child structure, the layers of depth, the subtree containment
-- none of these are axioms. They all follow from one fact: there is a
unique simple path between every pair of vertices. Choosing a root simply
orients these paths.

---

## 3. Leaf Detection

A vertex v is a **leaf** if it has no children. Equivalently, T(v) = {v}.

In an unrooted tree, a vertex v is a leaf if deg(v) = 1.

### In code (adjacency list)

The naive check `tree[node].size() == 1` is almost right but fails for
the root when the root has degree 1 (it would be classified as a leaf
even though it is the root, and in many algorithms we do not want to
treat the root as a leaf).

**Correct check:**

```cpp
bool is_leaf = (tree[node].size() == 1 && node != root);
// Equivalently, when using parent:
bool is_leaf = (tree[node].size() == 1 && parent != -1);
```

A node is a leaf if and only if degree = 1 AND it is not the root.

(When the root has degree 1, whether to treat it as a leaf depends on
the problem. The above is the standard convention.)

When the root has degree 0 (n = 1), it is both root and leaf. When par
is stored as -1 for the root, ensure the parent-check guard handles this.

---

## 4. Tree Diameter

### 4.1 Definition

The **diameter** of a tree T is the length of the longest path in T:

```
diam(T) = max_{u, v in V} dist(u, v)
```

A pair (A, B) achieving this maximum is called a **diameter pair**
(or *diametral pair*). The path between them is a *diametral path*.

### 4.2 Diameter endpoints are leaves

**Claim:** If (A, B) is a diameter pair, then A and B are both leaves.

**Proof:** Suppose A is not a leaf. Then A has a neighbor w such that
w is not on the path from A to B (since A has degree >= 2 and at most
one neighbor is on the path to B). Since the path from w to B goes
through A, dist(w, B) = 1 + dist(A, B) > diam(T), contradicting
maximality. So A is a leaf. Symmetrically, B is a leaf.

### 4.3 Algorithm 1: DP on the Tree

**Idea.** Root the tree at an arbitrary vertex. For each vertex v, the longest path passing through v consists of descending into two different subtrees of v. The diameter is the maximum such value over all v.

**Formal recurrence.** For each vertex v, define:

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

### 4.4 Algorithm 2: Double BFS/DFS

**Algorithm.**
1. Run BFS (or DFS) from an arbitrary vertex s. Let u be the vertex at maximum distance from s.
2. Run BFS (or DFS) from u. Let v be the vertex at maximum distance from u.
3. Return dist(u, v) as the diameter.

### 4.5 Key Theorem: Farthest node from ANY node is a diameter endpoint

**Theorem.** Let s be any vertex. Let u be a vertex maximizing dist(s, u).
Then u is an endpoint of some diameter.

**Proof.** Let (A, B) be a diameter pair with diameter D. We must show
dist(u, v) = D for some v (i.e., u is a diameter endpoint).

Consider the path P from A to B and the vertex s. There are two cases
based on whether the path from s to u intersects P.

**Case 1:** The path from s to u passes through some vertex t on P.

Let dist(A, t) = a, dist(t, B) = b, so a + b = D.
dist(s, u) >= dist(s, A) and dist(s, u) >= dist(s, B) (since u is
farthest from s).

dist(s, A) = dist(s, t) + a (path from s to t to A along P).
dist(s, B) = dist(s, t) + b.
dist(s, u) = dist(s, t) + dist(t, u).

From dist(s, u) >= dist(s, A): dist(t, u) >= a.
From dist(s, u) >= dist(s, B): dist(t, u) >= b.

Now consider dist(u, A) = dist(u, t) + a >= b + a = D (using dist(t,u) >= b).
And dist(u, A) <= D (cannot exceed diameter).
So dist(u, A) = D, and u is a diameter endpoint paired with A.

**Case 2:** The paths from s to u and from A to B do not share a vertex.

Let p be the point where the path from s meets P (the path from s to any
vertex on P must hit P at some point). Let q be the point where the path
from s branches toward u vs toward P.

dist(s, u) = dist(s, q) + dist(q, u).
dist(s, A) = dist(s, q) + dist(q, p) + dist(p, A).
dist(s, B) = dist(s, q) + dist(q, p) + dist(p, B).

From dist(s, u) >= dist(s, A):
  dist(q, u) >= dist(q, p) + dist(p, A).
From dist(s, u) >= dist(s, B):
  dist(q, u) >= dist(q, p) + dist(p, B).

dist(u, A) = dist(u, q) + dist(q, p) + dist(p, A).
Using the second inequality:
  dist(u, A) = dist(u, q) + dist(q, p) + dist(p, A)
             >= [dist(q, p) + dist(p, B)] + dist(q, p) + dist(p, A)
             >= dist(p, B) + dist(p, A)     (since dist(q,p) >= 0)
             = D.

So dist(u, A) >= D, which forces dist(u, A) = D. Hence u is a diameter
endpoint.

**Correctness of the double-BFS algorithm.** Step 1 gives a diameter endpoint u
(by the theorem). Step 2 finds the farthest vertex from a diameter
endpoint, which gives the full diameter distance.

**Complexity.** Two BFS calls, each O(V + E) = O(n) for a tree.

```cpp
pair<int,int> bfs_farthest(int src, vector<vector<int>>& adj, int n) {
    vector<int> dist(n, -1);
    queue<int> q;
    q.push(src);
    dist[src] = 0;
    int farthest = src;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                if (dist[v] > dist[farthest]) farthest = v;
            }
        }
    }
    return {farthest, dist[farthest]};
}

int diameter(vector<vector<int>>& adj, int n) {
    auto [u, d1] = bfs_farthest(0, adj, n);
    auto [v, d2] = bfs_farthest(u, adj, n);
    return d2;  // d2 = dist(u, v) = diameter
}
```

---

## 5. Tree Centre

### 5.1 Eccentricity

The **eccentricity** of a vertex u is:
```
e(u) = max_{v in V} dist(u, v)
```

### 5.2 Centre

The **centre** of a tree is the set of vertices with minimum eccentricity:
```
C(T) = argmin_u e(u)
```

### 5.3 Lemma 1: Eccentricity equals max distance to diameter endpoints

**Lemma.** Let (A, B) be a diameter pair. For any vertex x:
```
e(x) = max(dist(x, A), dist(x, B))
```

**Proof.** Clearly e(x) >= max(dist(x, A), dist(x, B)) since A and B are
particular vertices.

For the other direction, let y be any vertex achieving e(x) = dist(x, y).
We need dist(x, y) <= max(dist(x, A), dist(x, B)).

The formal argument uses the same case analysis as the diameter endpoint proof:
if there were a vertex y with dist(x, y) > max(dist(x, A), dist(x, B)),
we could construct a path longer than D, contradicting that D is the
diameter.

### 5.4 Lemma 2: The centre lies on the diameter path

**Lemma.** Every centre vertex lies on the path from A to B.

**Proof.** Suppose c is a centre vertex not on the diameter path P(A, B).
Let p be the point on P closest to c (the vertex where the path from c
to P meets P).

For any vertex x on P: e(x) = max(dist(x, A), dist(x, B)) by Lemma 1.

Now consider e(c):
  dist(c, A) = dist(c, p) + dist(p, A)
  dist(c, B) = dist(c, p) + dist(p, B)

So e(c) = max(dist(c, A), dist(c, B))
        = dist(c, p) + max(dist(p, A), dist(p, B))
        = dist(c, p) + e(p).

Since c is not on P, dist(c, p) >= 1, so e(c) > e(p).

But then p has strictly smaller eccentricity than c, contradicting c
being a centre vertex. Therefore, every centre vertex is on the diameter
path.

### 5.5 Finding the centre on the diameter path

Let the diameter have length D. Parameterise the diameter path by
distance t from A (so t ranges from 0 to D, and the vertex at distance
t from A is at distance D - t from B).

For a vertex at position t on the diameter:
```
e(t) = max(t, D - t)
```

We want to minimize max(t, D - t).

The function t is increasing, D - t is decreasing. They cross at t = D/2.
- The minimum of max(t, D - t) is D/2, achieved at t = D/2.

**If D is even:** t = D/2 is an integer. Exactly one vertex on the
diameter path is at distance D/2 from both A and B. The centre is a
single vertex.

**If D is odd:** t = D/2 is not an integer. The minimum of max(t, D-t)
over integer values is achieved at t = floor(D/2) and t = ceil(D/2).
At both, max(t, D-t) = ceil(D/2). The centre consists of exactly two
adjacent vertices.

### 5.6 Theorem: The centre is unique (1 or 2 vertices)

**Theorem (Jordan, 1869).** The centre of a tree consists of either 1 vertex (when
diameter is even) or 2 adjacent vertices (when diameter is odd). Moreover,
every diameter path passes through the centre.

**Proof.** We showed the centre is the midpoint(s) of the diameter path.
If there were another diameter pair (A', B') whose midpoint were different,
the centre (= min eccentricity set) would include vertices off the original
diameter path, contradicting Lemma 2 applied to the new diameter. More
precisely, the centre is determined by the eccentricity function, which
is the same regardless of which diameter pair we use. By Lemma 1,
eccentricity is determined by any diameter pair, so the min-eccentricity
set is the same. The midpoints of all diameters must coincide.

### 5.7 Iterative leaf-peeling characterisation

The centre can also be found by repeatedly removing all leaves:

```
while n > 2:
    remove all current leaves
    (they have the largest eccentricity among remaining vertices)
```

The last 1 or 2 vertices remaining are the centre. This is equivalent to
finding the midpoint of the diameter, because each round of leaf removal
reduces the diameter by 2 (one from each end).

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

## 6. Tree Triangle Inequality

### Statement

For any three vertices x, y, z in a tree T:
```
dist(x, z) <= dist(x, y) + dist(y, z)
```

### Proof

In any graph, the shortest-path distance satisfies the triangle inequality.
(A path from x to y concatenated with a path from y to z gives a walk
from x to z of length dist(x,y) + dist(y,z). The shortest path from x
to z is at most this length.)

In a tree, there is only one simple path between any two vertices, so
dist(x, z) is the length of the unique path from x to z. The unique path
from x to y followed by the unique path from y to z gives a walk from x
to z (possibly with repeated vertices). The unique path from x to z is
no longer than this walk.

In fact, something stronger is true in trees. Let w = LCA(x, z). Then:
```
dist(x, z) = dist(x, w) + dist(w, z)
```
The triangle inequality follows because the detour through y cannot be
shorter than the direct path.

---

## Summary of key formulas

```
Tree edges:                    m = n - 1
Distance via LCA:              dist(u,v) = depth(u) + depth(v) - 2*depth(LCA(u,v))
Eccentricity:                  e(u) = max(dist(u,A), dist(u,B))  for diameter pair (A,B)
Diameter:                      Two BFS calls, O(n)
Centre:                        Midpoint of diameter. 1 node (even D) or 2 nodes (odd D).
Leaf check:                    degree == 1 && node != root
```
