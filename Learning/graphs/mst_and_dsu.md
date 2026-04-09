# Minimum Spanning Trees and Disjoint Set Union

A rigorous treatment of DSU with amortized analysis, MST theory with the cut and cycle
properties, Kruskal's and Prim's algorithms, and common DSU application patterns.

---

## 1. Disjoint Set Union -- Formal Analysis

### 1.1 Abstract Data Type

A Disjoint Set Union (DSU), also known as Union-Find, maintains a collection of
disjoint sets and supports two operations:

- **find(x):** Return the *representative* (root) of the set containing x.
- **union(x, y):** Merge the sets containing x and y into one set.

### 1.2 Forest Representation

Represent each set as a rooted tree. Each element x stores a parent pointer parent[x].
The root of each tree is the representative of its set (parent[root] = root).

**Naive find:** Follow parent pointers from x to the root. Cost: O(depth of x).

**Naive union:** find(x), find(y), then make one root point to the other.

Without optimizations, a sequence of n unions can create a degenerate chain of depth n,
making find O(n) in the worst case. Two optimizations bring this down to nearly O(1)
amortized.

### 1.3 Union by Size (or Rank)

**Strategy:** When merging two trees, attach the root of the *smaller* tree (fewer nodes)
under the root of the *larger* tree. Maintain a size[x] array (or equivalently, a
rank[x] array tracking an upper bound on tree height).

**Theorem.** With union by size, the depth of any node is at most log_2(n).

*Proof* (by induction on union operations):

**Claim:** A tree of depth d has at least 2^d nodes.

**Base case:** A single-node tree has depth 0 and 1 = 2^0 nodes. Correct.

**Inductive step:** Suppose node x has its depth increased from d to d + 1. This
happens only when the tree T_x containing x is attached under the root of another tree
T_y, meaning |T_x| <= |T_y|. The new tree has size |T_x| + |T_y| >= 2|T_x|. By the
inductive hypothesis, T_x had at least 2^d nodes (since x had depth d within T_x), so
the new tree has at least 2 * 2^d = 2^{d+1} nodes.

Therefore, if the total number of elements is n, the maximum depth is at most log_2(n).
This gives O(log n) per find operation. QED.

### 1.4 Path Compression

**Strategy:** During find(x), after finding the root r, set parent[y] = r for every
node y on the path from x to r. This flattens the tree, making subsequent finds faster.

```
find(x):
    if parent[x] != x:
        parent[x] = find(parent[x])
    return parent[x]
```

**Effect:** After a find(x) operation, every node on the path from x to the root points
directly to the root. Future finds on these nodes are O(1).

**Path compression alone** gives O(log n) amortized per operation (provable via an
amortized argument, though the analysis is non-trivial).

### 1.5 Combined Analysis: Inverse Ackermann

**Theorem (Tarjan, 1975; refined by Tarjan and van Leeuwen, 1984).** A sequence of m
union/find operations on n elements, using both union by size and path compression,
runs in O(m * alpha(n)) time, where alpha is the inverse Ackermann function.

**Definition of alpha.** The Ackermann function A(k, j) grows extraordinarily fast:
- A(1, j) = 2j for j >= 1
- A(2, j) = 2^j for j >= 1 (tower of j-1 twos)
- A(3, j) is a tower of 2s of height j
- A(4, j) is an iterated tower...

The inverse Ackermann function alpha(n) = min{k : A(k, 1) >= n}. For all practical
purposes (n <= 10^{80}), alpha(n) <= 4. Thus O(m * alpha(n)) is effectively O(m).

**Proof sketch.** The full proof uses a potential function argument. Assign each node x a
potential based on its "rank" (an upper bound on its subtree height) and the rank of
its current parent. Path compression reduces the potential of nodes along the compressed
path. The total potential decrease over all operations is bounded, yielding the
amortized bound.

The key insight is that path compression is "self-improving": the more operations you
perform, the flatter the trees become, making future operations cheaper.

### 1.6 Implementation

```
// Initialization
for (int i = 0; i < n; i++) {
    parent[i] = i;
    sz[i] = 1;
}

// Find with path compression
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

// Union by size
void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (sz[x] < sz[y]) swap(x, y);
    parent[y] = x;
    sz[x] += sz[y];
}
```

---

## 2. Minimum Spanning Trees -- Theory

### 2.1 Definitions

**Definition (Spanning Tree).** Given a connected undirected graph G = (V, E), a
*spanning tree* T = (V, E_T) is a subgraph that:
1. Contains all vertices of G.
2. Is a tree (connected and acyclic).
3. E_T is a subset of E.

By the tree equivalences (traversals_and_connectivity.md, Section 1.5), T has exactly
|V| - 1 edges.

**Definition (Minimum Spanning Tree).** A *minimum spanning tree* (MST) of a weighted
connected graph G = (V, E, w) is a spanning tree T that minimizes the total weight:

    w(T) = sum_{e in E_T} w(e).

**Existence.** Every connected weighted graph has at least one MST (the set of spanning
trees is finite and non-empty for connected graphs, so a minimum exists).

**Uniqueness.** If all edge weights are distinct, the MST is unique. (Proof below, as a
consequence of the cut property.)

### 2.2 Cut Property

**Definition (Cut).** A *cut* of G is a partition of V into two non-empty sets (S, V\S).
An edge *crosses* the cut if it has one endpoint in S and one in V\S.

**Theorem (Cut Property).** For any cut (S, V\S) of G, the minimum-weight edge e
crossing the cut belongs to some MST.

*Proof.* Let e = {u, v} be the unique minimum-weight crossing edge (we handle ties
momentarily). Let T be an MST. If e is in T, we are done.

Suppose e is not in T. Adding e to T creates exactly one cycle C (since T is a tree;
adding any edge to a tree creates exactly one cycle). The cycle C must contain at least
one other edge e' that also crosses the cut (S, V\S), because the cycle enters S via e
and must leave S to return -- it needs another crossing edge.

Consider T' = T - {e'} + {e}. We verify T' is a spanning tree:
- T - {e'} disconnects T into two components. Adding e reconnects them (since e crosses
  the same cut that e' crossed). So T' is connected.
- T' has |V| - 1 edges.
- Therefore T' is a spanning tree.

Weight comparison: w(T') = w(T) - w(e') + w(e) <= w(T) since w(e) <= w(e') (e is the
minimum crossing edge). Since T is an MST, w(T') >= w(T). Therefore w(T') = w(T), and
T' is also an MST that contains e. QED.

**Corollary (Uniqueness with distinct weights).** If all edge weights are distinct, the
MST is unique.

*Proof.* With distinct weights, in the proof above, w(e) < w(e'), so w(T') < w(T),
contradicting T being an MST. Therefore e must have been in T to begin with. Since this
holds for every cut and the MST edges are determined by the cut property, the MST is
unique.

### 2.3 Cycle Property

**Theorem (Cycle Property).** For any cycle C in G, the maximum-weight edge in C (unique
if weights are distinct) does NOT belong to any MST.

*Proof.* Let e be the unique maximum-weight edge in cycle C. Suppose e = {u, v} is in
some MST T. Removing e from T partitions V into two components, say S (containing u)
and V\S (containing v). This defines a cut (S, V\S). The cycle C must contain another
edge e' crossing this cut (since C passes through both u and v and is a cycle). We have
w(e') < w(e) (since e is the unique maximum in C).

Then T' = T - {e} + {e'} is a spanning tree with w(T') < w(T), contradicting T being
an MST. QED.

---

## 3. Kruskal's Algorithm

### 3.1 Algorithm

1. Sort all edges by weight in non-decreasing order.
2. Initialize a DSU on V vertices.
3. For each edge (u, v, w) in sorted order:
   a. If find(u) != find(v) (u and v are in different components):
      - Add edge (u, v) to the MST.
      - union(u, v).
   b. Otherwise skip (would create a cycle).
4. Stop when |V| - 1 edges have been added.

### 3.2 Proof of Correctness

**Theorem.** Kruskal's algorithm produces an MST.

*Proof.* We show that every edge added by Kruskal's satisfies the cut property.

When edge e = {u, v} is added, u and v are in different components C_u and C_v.
Consider the cut (C_u, V\C_u). Edge e crosses this cut. We claim e is the minimum-
weight crossing edge.

Any edge e' that crosses this cut and has w(e') < w(e) would have been processed before
e (since edges are sorted by weight). When e' was processed:
- If e' connected two different components at that time, it would have been added. But
  then u and v might already be in the same component -- however, the claim is about the
  current cut (C_u, V\C_u). If e' was added earlier and doesn't cross the current cut
  (C_u, V\C_u), then at the time of processing, u and v's component membership was
  different. Let us reconsider.

More precisely: any crossing edge e' with w(e') < w(e) was processed before e. It
crosses the cut (C_u, V\C_u), meaning one endpoint is in C_u and the other is not.
If e' was NOT added (skipped), then its endpoints were already in the same component
at the time -- but that component was a subset of either C_u or V\C_u. This is
impossible since e' has endpoints on both sides. Therefore e' WAS added, meaning it's
already in the partial MST. But added edges within C_u don't cross the cut, and e'
crosses the cut -- contradiction with e' being "within" a single component.

Wait, this needs more care. The correct argument: at the time e' was considered, its
endpoints may have been in two different components, one of which is now a subset of C_u
and the other a subset of V\C_u. If e' was added, it merged two components, one inside
current C_u and one outside. But that contradicts C_u being a component at the time we
consider e (C_u is exactly the set of vertices connected to u through previously added
edges; if e' was added and connects inside to outside, then C_u would include the
outside part too).

**Cleaner proof:** Consider the moment edge e = {u, v} is added. Let S be the component
containing u (the set of vertices reachable from u via previously added MST edges). The
cut (S, V\S) separates u from v. Edge e crosses this cut. Every previously processed
edge e' with w(e') <= w(e) was either:
(a) Not crossing this cut (both endpoints in S or both in V\S), or
(b) Crossing this cut and already added to the MST -- but then v would be reachable
    from u, contradicting find(u) != find(v).

In case (a), e' is irrelevant to this cut. In case (b), we reach a contradiction.
Therefore, no crossing edge with weight less than w(e) was added or skipped. If a
crossing edge e' with w(e') < w(e) was skipped, it means its endpoints were in the same
component at the time of processing. But e' crosses the current cut (S, V\S), so its
endpoints are in different current components -- meaning they were joined by some
later edge, but that can't make them in the "same component" at the earlier time.

Therefore e is the minimum-weight crossing edge for the cut (S, V\S), and by the cut
property, e belongs to some MST.

Since every added edge belongs to some MST, and Kruskal's adds exactly |V| - 1 edges
forming a spanning tree, the result is an MST. (With distinct weights, all edges must
belong to THE unique MST, so the result is THE MST.) QED.

### 3.3 Complexity

- Sorting edges: O(E log E) = O(E log V) (since E <= V^2, log E <= 2 log V).
- DSU operations: E find/union operations in O(E * alpha(V)).
- Total: O(E log E), dominated by sorting.

---

## 4. Prim's Algorithm

### 4.1 Algorithm

Grow the MST from a starting vertex, one edge at a time.

1. Initialize: Start with any vertex s. Set key[s] = 0, key[v] = infinity for v != s.
2. Use a priority queue. Insert all vertices keyed by key[v].
3. While the priority queue is non-empty:
   a. Extract vertex u with minimum key[u].
   b. For each neighbor v of u with edge weight w(u, v):
      - If v is still in the priority queue and w(u, v) < key[v]:
        - Set key[v] = w(u, v), parent[v] = u. Update priority queue.

### 4.2 Proof of Correctness

**Theorem.** Prim's algorithm produces an MST.

*Proof.* At each step, the algorithm selects the minimum-weight edge connecting the
current MST fragment S to V\S. This is precisely the minimum-weight edge crossing the
cut (S, V\S). By the cut property, this edge belongs to some MST.

By induction on the number of edges added:
- After 0 edges, the empty set is a subset of every MST (vacuously).
- After k edges, assume the current set F is a subset of some MST T. The (k+1)-th edge
  e is the min-weight crossing edge for some cut. If e is in T, then F + {e} is still
  a subset of T. If e is not in T, then by the cut property proof, we can swap e for
  another edge in T to get another MST T' containing F + {e}.

After |V| - 1 edges, F is a spanning tree that is a subset of some MST, hence IS that
MST. QED.

### 4.3 Complexity

With a binary heap:
- Each of |V| extractions: O(log V).
- Each of |E| potential decrease-key operations: O(log V).
- Total: O((V + E) log V).

With a Fibonacci heap (theoretical): O(E + V log V).

### 4.4 Kruskal vs. Prim: When to Use Which

| Criterion | Kruskal's | Prim's |
|-----------|-----------|--------|
| Graph density | Better for sparse (E ~ V) | Better for dense (E ~ V^2) |
| Implementation | Simple with DSU | Needs priority queue with decrease-key |
| Edge list input | Natural (just sort) | Needs adjacency list |
| Disconnected graph | Finds MSF naturally | Needs modification (restart from unvisited) |
| Typical CP choice | More common (simpler DSU) | Less common |

In competitive programming, Kruskal's with DSU is the standard choice due to simplicity.
Prim's is preferred in dense graphs or when the graph is given as an adjacency matrix.

---

## 5. DSU Application Patterns

### 5.1 Components Minus One

**Problem:** Given a graph, find the minimum number of edges to add to make it connected.

**Solution:** Count the number of connected components k (using DSU: iterate all edges,
union endpoints, count distinct roots). Answer: k - 1.

**Proof:** A spanning tree on k components requires k - 1 edges to connect them (see
traversals_and_connectivity.md, Section 6.2).

This is one of the most common DSU patterns, appearing in problems like: "build roads
to connect cities," "minimum wires to connect computers," etc.

### 5.2 Component Size Tracking

Maintain size[x] for each root x. On union(x, y), update: size[root] += size[other].

**Application:** After processing all edges, for each vertex v, size[find(v)] gives the
size of v's connected component.

This is useful for problems where the answer depends on component sizes:
- "How many people can each person communicate with?" -> component size - 1.
- "How many pairs of vertices are in the same component?" -> sum of C(size_i, 2) over
  all components.

### 5.3 Component Property Verification

**Pattern:** After building components with DSU, verify a property of each component.

**Example: Complete Graph Check.** Given a graph, determine if every connected component
is a complete graph.

A component of size s is complete iff it has exactly s(s-1)/2 edges. Track both
size[root] and edge_count[root]. On adding edge (u, v):
- If find(u) == find(v): increment edge_count[find(u)].
- Else: union, merge edge counts (edge_count[new_root] += edge_count[old_root] + 1).

After processing all edges, check: for each root r, edge_count[r] == size[r] * (size[r] - 1) / 2.

### 5.4 Online Connectivity

DSU naturally supports online (incremental) connectivity queries: edges are added one at
a time, and after each addition, we can answer "are u and v connected?" in O(alpha(n)).

**Limitation:** Standard DSU does not support edge deletion. For fully dynamic
connectivity (insertions and deletions), more advanced structures are needed (e.g.,
link-cut trees, Euler tour trees), which are rarely needed in competitive programming.

### 5.5 Functional Graphs

**Definition.** A *functional graph* on n vertices is a directed graph where every vertex
has exactly one outgoing edge. Equivalently, it is defined by a function f : V -> V,
where the edge from v goes to f(v).

**Structure theorem.** Each weakly connected component of a functional graph consists of
exactly one directed cycle (the "rho" shape), with trees hanging off the cycle vertices,
directed toward the cycle.

**DSU application:** To find connected components of the underlying undirected graph,
treat the functional graph as undirected and use DSU. Each component has exactly one
cycle, detectable as the edge (u, f(u)) where find(u) == find(f(u)) before the union.

### 5.6 MST-Related DSU Patterns

**Minimum edge to connect two components:** In Kruskal's algorithm, the first edge that
connects components containing vertices u and v gives the minimum bottleneck weight on
any path from u to v in the MST. This follows from the sorted processing order.

**Second-best MST:** Find the MST, then for each non-MST edge (u, v), find the maximum
edge weight on the MST path from u to v. The second-best MST is obtained by swapping
the non-MST edge (u, v) with this maximum MST path edge, choosing the swap that
increases total weight the least.

**Formal statement:** Let T be the MST. For each edge e not in T, adding e creates a
cycle C in T + {e}. Let max_e be the maximum-weight edge in C other than e. The
second-best MST has weight w(T) + w(e) - w(max_e), minimized over all non-MST edges e.

---

## 6. Summary of Complexities

| Operation / Algorithm | Time Complexity | Space |
|----------------------|-----------------|-------|
| DSU find (both optimizations) | O(alpha(n)) amortized | O(n) |
| DSU union (both optimizations) | O(alpha(n)) amortized | O(n) |
| Kruskal's MST | O(E log E) | O(V + E) |
| Prim's MST (binary heap) | O((V + E) log V) | O(V + E) |
| Prim's MST (Fibonacci heap) | O(E + V log V) | O(V + E) |

For competitive programming, the practical takeaways:
1. DSU with path compression and union by size is effectively O(1) per operation.
2. Kruskal's is the default MST algorithm -- simple, efficient, and pairs naturally
   with DSU.
3. The cut property is the theoretical foundation: every greedy MST algorithm works by
   repeatedly choosing minimum-weight cut edges.
