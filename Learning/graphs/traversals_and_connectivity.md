# Graph Traversals and Connectivity

A rigorous treatment of graph traversal algorithms, cycle detection, bipartiteness,
connected components, multi-source BFS, and topological sorting.

---

## 1. Graph Theory Foundations

### 1.1 Basic Definitions

**Definition (Graph).** A *graph* is a pair G = (V, E) where V is a finite set of
*vertices* (or nodes) and E is a set of *edges*. In an *undirected graph*, each edge
is an unordered pair {u, v} with u, v in V. In a *directed graph* (digraph), each edge
is an ordered pair (u, v), denoting a directed edge from u to v.

**Definition (Weighted Graph).** A *weighted graph* is a triple G = (V, E, w) where
w : E -> R assigns a real-valued *weight* to each edge. An *unweighted graph* is one
where all edges have equal weight (conventionally 1).

**Definition (Degree).** In an undirected graph, the *degree* of vertex v, written
deg(v), is the number of edges incident to v. In a directed graph, the *in-degree*
deg^-(v) counts edges entering v and the *out-degree* deg^+(v) counts edges leaving v.

### 1.2 Adjacency List Representation

Store for each vertex v a list adj[v] of its neighbors (or, for weighted graphs,
pairs (neighbor, weight)).

- **Space**: O(|V| + |E|). Each edge appears once (directed) or twice (undirected).
- **Iterate neighbors of v**: O(deg(v)).
- **Check if edge (u,v) exists**: O(deg(u)) in the worst case.

This is the representation of choice for competitive programming; adjacency matrices
use O(|V|^2) space and are only preferable for dense graphs or when O(1) edge lookup
is needed.

### 1.3 Handshaking Lemma

**Lemma (Handshaking).** For any undirected graph G = (V, E),

    sum_{v in V} deg(v) = 2|E|.

*Proof.* Each edge {u, v} in E contributes exactly 1 to deg(u) and exactly 1 to
deg(v). Therefore, when we sum degrees over all vertices, each edge is counted exactly
twice. QED.

**Corollary.** The number of vertices with odd degree is even.

*Proof.* The sum of all degrees is 2|E|, which is even. An even sum cannot contain an
odd number of odd terms. QED.

### 1.4 Grid Graphs

A rectangular grid of dimensions n x m (n rows, m columns) naturally defines a graph
where each cell (i, j) is a vertex and edges connect horizontally and vertically
adjacent cells.

- **Vertices**: n * m.
- **Edges**: Each row of m cells contributes m - 1 horizontal edges, and there are n
  rows, giving n(m - 1) horizontal edges. Similarly, m(n - 1) vertical edges.
  Total = n(m - 1) + m(n - 1) = 2nm - n - m.

This formula is useful for quick sanity checks on grid-based problems.

### 1.5 Tree Equivalences

**Theorem.** Let G be a graph on n vertices. The following are equivalent:

1. G is a tree (connected and acyclic).
2. G is connected and has exactly n - 1 edges.
3. G is acyclic and has exactly n - 1 edges.
4. There is exactly one path between any pair of vertices.
5. G is minimally connected: removing any edge disconnects it.

*Proof of (i) => (ii):*
Let G be a tree (connected, acyclic) on n vertices. We prove |E| = n - 1 by induction
on n.

Base case: n = 1. A single vertex has 0 edges. n - 1 = 0. Correct.

Inductive step: Assume all trees on fewer than n vertices have exactly (number of
vertices) - 1 edges. Let G be a tree on n >= 2 vertices. Since G is connected and has
at least 2 vertices, it has at least one edge. Since G is acyclic, G must have a leaf
(a vertex of degree 1). To see this: start at any vertex and walk along edges without
repeating; since G is finite and acyclic, the walk must terminate at a vertex with no
unvisited neighbors, which (being acyclic) has degree 1.

Let v be a leaf. Remove v and its incident edge to obtain G'. Then G' is connected
(v was a leaf, so its removal doesn't disconnect anything) and acyclic (removing
vertices/edges can't create cycles). So G' is a tree on n - 1 vertices. By the
inductive hypothesis, |E(G')| = n - 2. Therefore |E(G)| = n - 2 + 1 = n - 1. QED.

*Proof of (ii) => (iii):*
Suppose G is connected with n - 1 edges. We show G is acyclic. Suppose for
contradiction G contains a cycle. Removing one edge from the cycle yields a connected
graph (since the cycle provides an alternate path) with n - 2 edges. Repeat: as long
as cycles exist, remove a cycle edge. We eventually obtain a connected, acyclic graph
(a spanning tree) T with some number of edges t < n - 1. But by (i) => (ii), any tree
on n vertices has n - 1 edges, so t = n - 1. Contradiction with t < n - 1. QED.

*Proof of (iii) => (i):*
Suppose G is acyclic with n - 1 edges. We show G is connected. Let G have k connected
components, with vertex counts n_1, ..., n_k summing to n. Each component is acyclic
and connected (within itself), hence a tree. By (i) => (ii), component i has n_i - 1
edges. Total edges = sum(n_i - 1) = n - k. We are given |E| = n - 1, so n - k = n - 1,
giving k = 1. Therefore G is connected. QED.

---

## 2. BFS -- Formal Treatment

### 2.1 Algorithm Description

Breadth-First Search from source s:
1. Initialize d[s] = 0, d[v] = infinity for all v != s.
2. Enqueue s into a FIFO queue Q.
3. While Q is non-empty:
   a. Dequeue vertex u.
   b. For each neighbor v of u:
      - If d[v] = infinity, set d[v] = d[u] + 1, enqueue v.

### 2.2 Correctness

**Theorem.** BFS from source s visits all vertices reachable from s, and upon
termination d[v] = dist(s, v) for all reachable vertices v, where dist(s, v) is the
shortest-path distance in the unweighted graph.

*Proof* (by strong induction on dist(s, v)):

**Base case:** dist(s, s) = 0. We set d[s] = 0. Correct.

**Inductive hypothesis:** Assume that for all vertices v with dist(s, v) <= k, we have
d[v] = dist(s, v) and v is enqueued (and eventually processed) by BFS.

**Inductive step:** Let w be a vertex with dist(s, w) = k + 1. There exists a shortest
path s = v_0, v_1, ..., v_k, v_{k+1} = w. By the IH, d[v_k] = k and v_k is
processed by BFS. When v_k is dequeued, all neighbors of v_k are examined. In
particular, w is examined. If d[w] is still infinity at that time, we set
d[w] = d[v_k] + 1 = k + 1 and enqueue w. If d[w] was already set, then
d[w] <= k + 1 (by some earlier discovery).

We need d[w] >= dist(s, w) = k + 1. This follows because BFS only sets d[v] = d[u] + 1
for some vertex u, so by induction d[v] >= dist(s, v) for all v (BFS never
underestimates the true distance, since any path BFS constructs is a valid path).

Combining: d[w] = k + 1 = dist(s, w). QED.

### 2.3 Key Properties

**Corollary.** BFS processes vertices in non-decreasing order of distance from s. That
is, if u is dequeued before v, then d[u] <= d[v].

*Proof.* At any point, the queue contains vertices at distances d and d + 1 for some d
(all distance-d vertices were enqueued before any distance-(d+1) vertex, by the FIFO
property). Therefore vertices are dequeued in non-decreasing order of distance.

**Complexity.** O(|V| + |E|). Each vertex is enqueued and dequeued at most once (O(|V|)).
Each edge is examined at most twice in an undirected graph, once in a directed graph
(O(|E|)). Total: O(|V| + |E|).

### 2.4 BFS Tree

The edges through which vertices are first discovered form the **BFS tree**. Every edge
in the original graph either belongs to this tree or connects two vertices whose BFS
distances differ by at most 1.

---

## 3. DFS -- Formal Treatment

### 3.1 Algorithm Description

Depth-First Search explores as deep as possible before backtracking. Assign each vertex
a discovery time disc[v] (when first visited) and a finishing time fin[v] (when its
subtree is fully explored). Use a global timer.

```
timer = 0
DFS(u):
    color[u] = GRAY
    disc[u] = ++timer
    for each neighbor v of u:
        if color[v] == WHITE:
            parent[v] = u
            DFS(v)
    color[u] = BLACK
    fin[u] = ++timer
```

### 3.2 Edge Classification

When DFS processes an edge (u, v):
- **Tree edge**: v is WHITE (unvisited). The edge becomes part of the DFS tree.
- **Back edge**: v is GRAY (started but not finished). v is an ancestor of u in the
  DFS tree. These indicate cycles.
- **Forward edge**: v is BLACK and disc[u] < disc[v]. v is a descendant of u already
  finished. (Directed graphs only.)
- **Cross edge**: v is BLACK and disc[u] > disc[v]. v is neither ancestor nor
  descendant. (Directed graphs only.)

**In undirected graphs**, only tree edges and back edges exist. There are no forward or
cross edges because if (u, v) is an edge and v was already fully processed (BLACK),
then v would have already explored the edge to u.

### 3.3 Parenthesis Theorem

**Theorem (Parenthesis Theorem).** In any DFS, for any two vertices u and v, exactly
one of the following holds:

1. [disc[u], fin[u]] and [disc[v], fin[v]] are entirely disjoint, and neither is an
   ancestor of the other in the DFS forest.
2. [disc[u], fin[u]] is entirely contained in [disc[v], fin[v]], and u is a descendant
   of v in the DFS tree.
3. [disc[v], fin[v]] is entirely contained in [disc[u], fin[u]], and v is a descendant
   of u in the DFS tree.

*Proof.* If u is discovered while v is being processed (v is GRAY), then u will finish
before v finishes, giving [disc[u], fin[u]] subset of [disc[v], fin[v]]. The converse
holds symmetrically. If neither is discovered during the other's processing, their
intervals are disjoint.

The key observation: DFS intervals behave like properly nested parentheses. They never
partially overlap.

### 3.4 White-Path Theorem

**Theorem.** Vertex v is a descendant of u in the DFS forest if and only if at the time
disc[u] (when u is discovered), there exists a path from u to v consisting entirely of
WHITE (unvisited) vertices.

*Proof sketch.*
(=>) If v is a descendant of u, the tree path from u to v consists of vertices
discovered after u. At time disc[u], they are all still WHITE.

(<=) If a white path u = w_0, w_1, ..., w_k = v exists at time disc[u], then w_1 is
white and adjacent to u, so DFS will visit w_1 before finishing u. By induction, each
w_i is visited before u finishes. Therefore v is a descendant of u.

### 3.5 Complexity

O(|V| + |E|), same as BFS. Each vertex is processed once, and each edge is examined a
constant number of times.

---

## 4. Cycle Detection

### 4.1 Undirected Graphs

**Theorem.** An undirected graph contains a cycle if and only if DFS discovers a back
edge (an edge to a visited vertex that is NOT the parent in the DFS tree).

*Proof.*
(=>) If a cycle C exists, consider the first vertex u on C that DFS discovers. The DFS
will explore along C until it reaches u again via a back edge.

(<=) If DFS finds a back edge (v, w) where w is an ancestor of v in the DFS tree, then
the tree path from w to v plus the edge (v, w) forms a cycle.

**Implementation note:** When checking neighbors of u, skip the parent (the vertex from
which u was discovered). An edge to a visited non-parent vertex is a back edge.

**Theorem.** A connected undirected graph is acyclic if and only if |E| = |V| - 1.

*Proof.* A connected acyclic graph is a tree, which has exactly |V| - 1 edges (Section
1.5). Conversely, if |E| >= |V|, then since a spanning tree uses |V| - 1 edges, the
remaining edge(s) create cycle(s).

More generally, an undirected graph on n vertices with k connected components is acyclic
iff |E| = n - k.

### 4.2 Directed Graphs

**Theorem.** A directed graph contains a cycle if and only if DFS discovers an edge to
a GRAY vertex (a vertex that has been discovered but not yet finished).

*Proof.*
(=>) If a directed cycle v_1 -> v_2 -> ... -> v_k -> v_1 exists, consider the first
vertex v_i discovered by DFS. By the white-path theorem, all other vertices on the
cycle become descendants of v_i. The edge v_{i-1} -> v_i (indices mod k) goes from a
descendant to v_i. When this edge is explored, v_i is still GRAY (it has a descendant
still being processed). So DFS finds an edge to a gray vertex.

(<=) If DFS finds edge (u, v) where v is GRAY, then v is an ancestor of u on the
current DFS path. The DFS tree path from v to u plus the edge (u, v) forms a directed
cycle.

**Implementation:** Use three states:
- WHITE (0): unvisited
- GRAY (1): discovered, currently in the recursion stack
- BLACK (2): finished, all descendants processed

A cycle exists iff we encounter an edge to a GRAY vertex.

---

## 5. Bipartite Graphs

### 5.1 Definition and Characterization

**Definition.** A graph G = (V, E) is *bipartite* if V can be partitioned into two
disjoint sets A and B such that every edge has one endpoint in A and one in B.

**Theorem (Characterization of Bipartite Graphs).** A graph G is bipartite if and only
if it contains no odd cycle.

*Proof.*
(=>) Suppose G is bipartite with partition (A, B). Any cycle must alternate between A
and B, so its length is even.

(<=) Suppose G has no odd cycle. For each connected component, pick any vertex s and
assign colors by BFS: color[s] = 0, and for each edge (u, v), color[v] = 1 - color[u].
If this produces a conflict (two adjacent vertices with the same color), then the BFS
tree path between them plus the conflicting edge forms an odd cycle, contradicting our
assumption. Therefore the coloring succeeds and G is bipartite.

### 5.2 2-Coloring Algorithm

Run BFS from any unvisited vertex. Assign color 0 to the source. For each discovered
vertex, assign the opposite color of its parent. If any edge connects two vertices of
the same color, the graph is not bipartite.

**Correctness** follows directly from the theorem above.

**Complexity:** O(|V| + |E|) -- same as BFS.

### 5.3 Vertex Cover in Bipartite Graphs

A *vertex cover* is a set S of vertices such that every edge has at least one endpoint
in S.

A simple heuristic: in a bipartite graph with partition (A, B), take the smaller of
{A, B} as a vertex cover. This gives a cover of size <= |V|/2.

**Caution:** This is NOT necessarily a *minimum* vertex cover. Konig's theorem states
that in a bipartite graph, the minimum vertex cover has size equal to the maximum
matching. Computing the minimum vertex cover therefore requires finding a maximum
matching, not merely a 2-coloring.

---

## 6. Connected Components

### 6.1 Undirected Components

Run DFS (or BFS) from each unvisited vertex. Each run discovers one connected
component. The number of components equals the number of DFS/BFS runs initiated.

**Complexity:** O(|V| + |E|) total across all runs.

### 6.2 The "Components Minus 1" Pattern

**Theorem.** To make a graph with k connected components into a single connected
component, exactly k - 1 edges must be added.

*Proof.* (Lower bound) Each added edge can reduce the number of components by at most 1
(it can merge at most two components). Starting with k components and needing 1, we
need at least k - 1 edges.

(Upper bound) Pick one vertex from each component. Chain them with k - 1 edges:
v_1 -- v_2 -- ... -- v_k. This connects all components.

This pattern appears frequently: given a graph, "how many edges to connect everything?"
Answer: (number of connected components) - 1.

### 6.3 Grid Components

Treat a grid as a graph where cells are vertices and adjacent cells (up/down/left/right)
are neighbors. Run DFS/BFS to count or explore connected regions.

Common variants:
- Count connected components of a specific cell type (e.g., counting rooms, islands).
- Flood fill: mark all cells reachable from a source.
- 8-directional adjacency: add diagonal neighbors.

### 6.4 Boundary BFS Trick

**Problem pattern:** Find cells/regions that are NOT connected to the boundary.

**Algorithm:**
1. Initialize a multi-source BFS from all boundary cells of interest.
2. Mark all cells reachable from the boundary.
3. Any remaining unmarked cells of interest are "surrounded" (not connected to boundary).

**Why it works:** A cell is connected to the boundary iff there is a path from it to
some boundary cell. Multi-source BFS from all boundary cells finds exactly the set of
cells connected to the boundary. Everything else is surrounded.

This technique applies to problems like surrounded regions (flip surrounded 'O's to 'X's)
and counting enclaves (land cells not reachable from boundary).

---

## 7. Multi-Source BFS

### 7.1 Definition and Correctness

**Problem:** Given a set of source vertices S = {s_1, s_2, ..., s_k}, compute for
every vertex v the quantity dist(S, v) = min_{s in S} dist(s, v).

**Algorithm:** Initialize BFS queue with ALL sources simultaneously, each at distance 0.
Proceed with standard BFS.

**Theorem.** Multi-source BFS correctly computes dist(S, v) for all v.

*Proof.* Construct an augmented graph G' by adding a virtual vertex s_0 with zero-weight
edges to each s_i. Then dist_{G'}(s_0, v) = min_i dist_G(s_i, v) = dist(S, v). Running
BFS from s_0 in G' is equivalent to initializing BFS with all of S at distance 0,
since s_0's neighbors are exactly S and all edges from s_0 have weight 0 (effectively,
s_0 is processed immediately and all sources are enqueued at distance 0). QED.

### 7.2 Application: Escape Problems

**Pattern (Monsters/Fire):** A player must escape a grid while hazards spread. Both
move one step per turn.

**Algorithm:**
1. Multi-source BFS from all hazard sources to compute hazard arrival times h[v].
2. BFS from the player to compute player arrival times p[v].
3. The player can reach cell v if p[v] < h[v] (strictly less: player must arrive before
   the hazard). The player escapes if any boundary cell v satisfies this condition.

**Correctness:** Both BFS computations give true shortest distances. The player can
traverse a cell only if they arrive strictly before the hazard. Since both move
optimally (shortest paths), comparing arrival times suffices.

---

## 8. Topological Sort

### 8.1 Definition

**Definition.** A *topological ordering* of a directed graph G = (V, E) is a linear
ordering of all vertices such that for every directed edge (u, v), vertex u appears
before vertex v in the ordering.

**Theorem.** A directed graph admits a topological ordering if and only if it is a DAG
(directed acyclic graph).

*Proof.*
(=>) If G has a cycle v_1 -> v_2 -> ... -> v_k -> v_1, then v_1 must appear before v_2,
v_2 before v_3, ..., v_k before v_1. This requires v_1 before v_1 -- impossible.

(<=) If G is a DAG, we construct a topological ordering. A DAG must have at least one
vertex with in-degree 0 (otherwise, following incoming edges indefinitely in a finite
graph produces a cycle). Place such a vertex first, remove it, and repeat. Each step
produces a DAG (removing a vertex from a DAG can't create a cycle), so we can always
find another vertex with in-degree 0. After n steps, all vertices are ordered.

### 8.2 DFS-Based Algorithm

Run DFS on the entire graph. Output vertices in reverse order of finishing times.

**Theorem.** For any edge (u, v) in a DAG, fin[u] > fin[v] in the DFS.

*Proof.* Consider edge (u, v).
- Case 1: v is WHITE when (u, v) is explored. Then v becomes a descendant of u, so v
  finishes before u. fin[u] > fin[v].
- Case 2: v is BLACK when (u, v) is explored. Then v is already finished while u is not.
  fin[u] > fin[v].
- Case 3: v is GRAY when (u, v) is explored. This means v is an ancestor of u with a
  path v ~> u, and edge (u, v) creates a cycle. Contradiction with G being a DAG.

So in all valid cases, fin[u] > fin[v]. Reversing the finish order gives a valid
topological sort. QED.

**Complexity:** O(|V| + |E|) -- same as DFS.

### 8.3 Kahn's Algorithm (BFS-Based)

1. Compute in-degree of every vertex.
2. Enqueue all vertices with in-degree 0.
3. While the queue is non-empty:
   a. Dequeue vertex u. Append u to the ordering.
   b. For each neighbor v of u, decrement in-degree of v. If in-degree becomes 0,
      enqueue v.
4. If fewer than |V| vertices are in the ordering, a cycle exists.

**Correctness:** Vertices with in-degree 0 have no prerequisites and can safely go next.
Removing them and updating in-degrees preserves the invariant. If all vertices are
processed, we have a valid topological order. If some vertices remain (all with
in-degree > 0), they form one or more cycles.

**Complexity:** O(|V| + |E|).

**Cycle detection via Kahn's:** If Kahn's algorithm processes fewer than |V| vertices,
the graph contains a cycle. The unprocessed vertices participate in at least one cycle.

### 8.4 Comparison of Approaches

| Property | DFS-based | Kahn's (BFS-based) |
|----------|-----------|-------------------|
| Cycle detection | Back edge to gray vertex | Unprocessed vertices remain |
| Lexicographic order | Hard to enforce | Use priority queue instead of queue |
| All topological sorts | Harder | Easier (backtracking with in-degree) |
| Implementation | Recursive/stack | Iterative with queue |

For problems requiring the lexicographically smallest topological order, use Kahn's
algorithm with a min-priority queue (min-heap).
