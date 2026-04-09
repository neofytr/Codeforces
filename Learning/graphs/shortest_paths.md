# Shortest Path Algorithms

A rigorous treatment of shortest path algorithms: BFS, 0-1 BFS, Dijkstra, Bellman-Ford,
Floyd-Warshall, state-augmented shortest paths, and shortest cycle detection.

---

## 1. Taxonomy of Shortest Path Algorithms

| Algorithm       | Graph Type           | Complexity       | Negative Edges?          |
|-----------------|----------------------|------------------|--------------------------|
| BFS             | Unweighted           | O(V + E)         | N/A                      |
| 0-1 BFS         | Weights in {0, 1}    | O(V + E)         | No                       |
| Dijkstra        | Non-negative weights | O((V + E) log V) | No                       |
| Bellman-Ford    | Any                  | O(VE)            | Yes (detects neg cycles) |
| Floyd-Warshall  | Any (all-pairs)      | O(V^3)           | Yes (detects neg cycles) |

**Guiding principle:** Use the simplest algorithm that handles the problem's constraints.
BFS when unweighted, 0-1 BFS when weights are binary, Dijkstra for general non-negative
weights, Bellman-Ford when negative edges exist, Floyd-Warshall for all-pairs queries.

---

## 2. Dijkstra's Algorithm -- Proof of Correctness

### 2.1 Algorithm Description

Dijkstra's algorithm computes single-source shortest paths from source s in a graph
with non-negative edge weights.

1. Initialize d[s] = 0, d[v] = infinity for all v != s.
2. Insert all vertices into a priority queue keyed by d[v].
3. While the priority queue is non-empty:
   a. Extract vertex u with minimum d[u].
   b. For each neighbor v of u with edge weight w(u, v):
      - If d[u] + w(u, v) < d[v], set d[v] = d[u] + w(u, v) (relaxation).

### 2.2 Correctness

**Theorem.** When all edge weights are non-negative, upon extracting vertex u from the
priority queue, d[u] = dist(s, u), the true shortest-path distance.

*Proof.* We prove by induction on the order in which vertices are extracted (finalized).

Let S denote the set of already-finalized vertices.

**Base case:** The first vertex extracted is s with d[s] = 0 = dist(s, s). Correct.

**Inductive hypothesis:** For all vertices already in S, d[v] = dist(s, v).

**Inductive step:** Let u be the next vertex extracted (u has the minimum d-value among
vertices not in S). Suppose for contradiction that d[u] > dist(s, u).

Let P be a true shortest path from s to u. Since s is in S and u is not, P must cross
the boundary of S at some point. Let (x, y) be the first edge on P with x in S and
y not in S.

We claim d[y] <= dist(s, u):
- Since x is in S, by the IH, d[x] = dist(s, x).
- When x was finalized, the edge (x, y) was relaxed, so d[y] <= d[x] + w(x, y).
- The subpath of P from s to y has weight dist(s, x) + w(x, y) = dist(s, y).
- So d[y] <= dist(s, y).
- Since all edge weights are non-negative, the remaining subpath from y to u on P has
  non-negative weight. Therefore dist(s, y) <= dist(s, u).
- Combining: d[y] <= dist(s, y) <= dist(s, u) < d[u].

But y is not in S (by construction), and d[y] < d[u]. This contradicts the fact that u
was chosen as the vertex with minimum d-value outside S. QED.

### 2.3 Why Negative Edges Break Dijkstra

The proof critically relies on the inequality dist(s, y) <= dist(s, u), which uses the
fact that continuing along path P from y to u can only increase the total weight.
With negative edges, the subpath from y to u could have negative total weight, making
dist(s, u) < dist(s, y). Then d[y] > d[u] is possible even though y is on the shortest
path to u, and Dijkstra may finalize u with an incorrect distance.

**Concrete example:** Graph with vertices {s, a, b}, edges s->a (weight 1), s->b
(weight 3), b->a (weight -5). Dijkstra finalizes a with d[a] = 1, but the true
shortest path is s->b->a with weight 3 + (-5) = -2.

### 2.4 Complexity Analysis

With a binary heap (or `std::priority_queue`):
- Each vertex is extracted at most once: O(V log V).
- Each edge triggers at most one decrease-key (or one insertion of a duplicate entry):
  O(E log V).
- Total: O((V + E) log V).

With `std::set<pair<int,int>>`:
- Insertion and deletion are both O(log V).
- To decrease key: erase the old entry, insert the new one. O(log V) per operation.
- Total: O((V + E) log V), same asymptotic complexity, but with a slightly larger
  constant factor.

With a Fibonacci heap (theoretical): O(V log V + E), but impractical for competitive
programming due to large constants.

**Lazy deletion variant:** Use `priority_queue` (which doesn't support decrease-key).
Instead, insert a new entry (d[v], v) on each relaxation. When extracting, skip entries
where d[v] has already been improved. Correct because the first extraction of v uses
the smallest d[v]. Slightly worse constant but simpler to implement.

---

## 3. 0-1 BFS

### 3.1 Motivation

When all edge weights are 0 or 1, Dijkstra's O((V + E) log V) is wasteful. We can
achieve O(V + E) by exploiting the special structure.

### 3.2 Algorithm

Use a **deque** (double-ended queue) instead of a priority queue.

1. Initialize d[s] = 0, d[v] = infinity for all v != s.
2. Push s to the front of the deque.
3. While the deque is non-empty:
   a. Pop vertex u from the front.
   b. For each edge (u, v) with weight w:
      - If d[u] + w < d[v]:
        - Set d[v] = d[u] + w.
        - If w = 0: push v to the **front** of the deque.
        - If w = 1: push v to the **back** of the deque.

### 3.3 Correctness

**Invariant:** The deque is always "sorted" in the sense that distances of elements form
a sequence of the pattern [d, d, ..., d, d+1, d+1, ..., d+1] for some d. That is,
elements at the front have distance <= elements at the back.

*Proof of invariant:* Initially the deque contains only s with distance 0. When
processing a front element u with distance d:
- A weight-0 edge produces d[v] = d, pushed to the front. The front still has
  distance d. Invariant maintained.
- A weight-1 edge produces d[v] = d + 1, pushed to the back. The back has distance
  d + 1. All existing back elements have distance d or d + 1. Invariant maintained.

Since we always process the front element (minimum distance), the same inductive
argument as Dijkstra's proof applies: when a vertex is first popped, its distance is
correct.

### 3.4 Complexity

Each vertex is processed at most once (after being popped from the front). Each edge is
examined once. All deque operations are O(1). Total: O(V + E).

### 3.5 When to Use

0-1 BFS is applicable whenever the edge weights are exactly 0 and 1. Common scenarios:
- Grid problems where some moves are "free" (cost 0) and others cost 1.
- Problems reducible to shortest path with binary weights.

---

## 4. Bellman-Ford Algorithm

### 4.1 Algorithm Description

Compute single-source shortest paths, handling negative edge weights.

1. Initialize d[s] = 0, d[v] = infinity for all v != s.
2. Repeat V - 1 times:
   - For each edge (u, v) with weight w:
     - If d[u] + w < d[v], set d[v] = d[u] + w (relaxation).
3. (Negative cycle detection) Run one more iteration. If any d[v] decreases, a
   negative cycle is reachable from s.

### 4.2 Correctness

**Theorem.** After iteration k (1 <= k <= V - 1), for every vertex v, d[v] is at most
the weight of the shortest path from s to v using at most k edges.

*Proof* (by induction on k):

**Base case (k = 1):** After iteration 1, each edge (s, v) is relaxed, so d[v] <=
w(s, v), which is the shortest path using at most 1 edge.

**Inductive hypothesis:** After iteration k - 1, for every vertex v, d[v] is at most the
weight of the shortest path from s to v using at most k - 1 edges.

**Inductive step:** Consider the shortest path P from s to v using at most k edges:
s = v_0 -> v_1 -> ... -> v_j = v (j <= k). Let u = v_{j-1}. By IH, after iteration
k - 1, d[u] <= weight of shortest path from s to u using at most k - 1 edges <=
weight of s -> v_0 -> ... -> v_{j-1}. In iteration k, edge (u, v) is relaxed:
d[v] <= d[u] + w(u, v) <= weight(P). QED.

**Corollary.** Since any shortest path in a graph without negative cycles has at most
V - 1 edges (a simple path visits at most V vertices), after V - 1 iterations d[v] =
dist(s, v) for all reachable v.

### 4.3 Negative Cycle Detection

**Theorem.** A negative cycle reachable from s exists if and only if the V-th iteration
of Bellman-Ford reduces some distance value.

*Proof.*
(=>) If a negative cycle C is reachable from s, then by traversing C repeatedly, path
weights can be made arbitrarily negative. Therefore no finite d[v] is optimal for
vertices reachable from C. Relaxations will continue to find improvements indefinitely.
In particular, the V-th iteration will reduce some d[v].

(<=) If the V-th iteration reduces d[v] for some v, then the shortest path to v (as
found by the algorithm) uses at least V edges. A path with V edges visits V + 1
vertices, so by the pigeonhole principle, some vertex is repeated -- the path contains
a cycle. This cycle must have negative total weight (otherwise, removing it would yield
a shorter or equal path with fewer edges, contradicting the need for V edges). QED.

### 4.4 Complexity

Each of V - 1 iterations examines all E edges: O(VE).

### 4.5 Application: Maximum Score with Cycle Detection

**Problem pattern (e.g., CSES High Score):** Find the maximum-weight path from source
to destination, where positive cycles may exist.

**Approach:**
1. Negate all edge weights to convert max-weight to min-weight.
2. Run Bellman-Ford. Detect negative cycles (originally positive cycles).
3. A negative cycle invalidates the answer only if it lies on some path from source to
   destination. Use BFS/DFS to check: does the cycle contain a vertex reachable from
   source AND from which the destination is reachable?

If such a cycle exists, the answer is infinity (or -1, per problem conventions).
Otherwise, report -d[destination] as the maximum score.

---

## 5. Floyd-Warshall Algorithm

### 5.1 Problem: All-Pairs Shortest Paths

Given a weighted graph, compute dist(i, j) for ALL pairs (i, j).

### 5.2 Dynamic Programming Formulation

Let the vertices be labeled 1, 2, ..., n.

**Definition.** dp[k][i][j] = weight of the shortest path from i to j using only
intermediate vertices from the set {1, 2, ..., k}.

**Base case.** dp[0][i][j] = w(i, j) if edge (i, j) exists, 0 if i = j, infinity
otherwise. (No intermediate vertices allowed -- only direct edges.)

**Recurrence.**

    dp[k][i][j] = min(dp[k-1][i][j], dp[k-1][i][k] + dp[k-1][k][j])

**Interpretation:** The shortest path from i to j using intermediates from {1, ..., k}
either:
1. Does NOT pass through vertex k: dp[k-1][i][j], or
2. DOES pass through vertex k: the path decomposes into i ~> k ~> j, where both
   subpaths use only intermediates from {1, ..., k-1}.

### 5.3 Proof of Correctness

*Proof* (by induction on k):

**Base case (k = 0):** dp[0][i][j] correctly gives the shortest path using no
intermediate vertices, which is the direct edge weight (or infinity if no direct
edge exists). Correct.

**Inductive hypothesis:** dp[k-1][i][j] is the shortest path from i to j using only
intermediates from {1, ..., k-1}.

**Inductive step:** Any shortest path from i to j using intermediates from {1, ..., k}
either uses vertex k or not.
- If it does not use k, its weight is dp[k-1][i][j] by the IH.
- If it does use k, it can be decomposed at the (first) occurrence of k into a path
  i ~> k using intermediates from {1, ..., k-1} (weight dp[k-1][i][k]) and a path
  k ~> j using intermediates from {1, ..., k-1} (weight dp[k-1][k][j]).

The minimum of these two cases is correct. QED.

### 5.4 Space Optimization

The recurrence only references dp[k-1], suggesting we need two 2D arrays. However, we
can update in place (using a single 2D array) because:

**Claim.** dp[k][i][k] = dp[k-1][i][k] and dp[k][k][j] = dp[k-1][k][j].

*Proof.* dp[k][i][k] = min(dp[k-1][i][k], dp[k-1][i][k] + dp[k-1][k][k]). Since
dp[k-1][k][k] >= 0 (assuming no negative cycles; or = 0 for the shortest path from k
to k using no negative cycles), the second term is >= dp[k-1][i][k]. So the minimum
is dp[k-1][i][k]. Similarly for dp[k][k][j].

This means when computing dp[k][i][j], the values dp[i][k] and dp[k][j] in the array
are still their dp[k-1] values. So in-place update is safe.

**Implementation:** Triple nested loop with k as the outermost loop:
```
for k = 1 to n:
    for i = 1 to n:
        for j = 1 to n:
            dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j])
```

### 5.5 Negative Cycle Detection

After running Floyd-Warshall, check the diagonal: if dp[v][v] < 0 for any vertex v,
then a negative cycle passes through v.

*Proof.* dp[v][v] represents the shortest "path" from v to v, i.e., the shortest cycle
through v (or 0 if no cycle). If dp[v][v] < 0, that cycle has negative total weight.

**Identifying all affected vertices:** Vertex u is affected by a negative cycle
(dist is -infinity) if there exists v with dp[v][v] < 0 such that dp[u][v] < infinity
and dp[v][u] < infinity (u can reach v and v can reach u, so u can use the negative
cycle).

### 5.6 Path Reconstruction

Maintain a matrix next[i][j] storing the first vertex after i on the shortest path
from i to j.

**Initialization:** next[i][j] = j for each direct edge (i, j).

**Update:** When dp[i][k] + dp[k][j] < dp[i][j], set next[i][j] = next[i][k].

**Path recovery:** To find the path from i to j, follow:
i -> next[i][j] -> next[next[i][j]][j] -> ... -> j.

### 5.7 Complexity

Three nested loops over V vertices: O(V^3) time, O(V^2) space.

This is optimal for all-pairs shortest paths in dense graphs. For sparse graphs,
running Dijkstra from each vertex gives O(V(V + E) log V), which is better when
E = o(V^2 / log V).

---

## 6. State-Augmented Shortest Paths

### 6.1 General Framework

**Key idea:** When the problem has additional constraints or resources beyond just
"reach vertex v," encode these constraints into an expanded state space and run
standard shortest path algorithms on the expanded graph.

Formally, define a new graph G' = (V', E') where:
- V' = V x S, where S is the set of possible "extra states" (e.g., number of stops
  used, whether a coupon has been applied, etc.).
- E' connects states according to the problem's transition rules.

The shortest path in G' corresponds to the optimal solution under the original
problem's constraints.

### 6.2 Example: Flight with K Stops

**Problem:** Find cheapest flight from source to destination with at most K intermediate
stops.

**State:** (vertex v, number of stops used k), where 0 <= k <= K.

**Transitions:** From state (u, k), for each edge (u, v) with cost c, transition to
state (v, k + 1) if k + 1 <= K + 1.

**State space size:** O(V * K). Apply BFS/Bellman-Ford on this expanded graph.

**Alternative (modified Bellman-Ford):** Run exactly K + 1 iterations of Bellman-Ford
(instead of V - 1). After k iterations, d[v] gives the shortest path to v using at
most k edges (equivalently, k - 1 intermediate stops). This avoids explicitly
constructing the expanded graph.

### 6.3 Example: Flight Discount (One Coupon)

**Problem:** Find shortest path from 1 to n, with the option to halve the cost of
exactly one edge.

**State:** (vertex v, coupon_used in {0, 1}).

**Transitions:**
- From (u, 0): take edge (u, v) normally -> (v, 0) with cost w(u, v).
- From (u, 0): take edge (u, v) with coupon -> (v, 1) with cost w(u, v) / 2.
- From (u, 1): take edge (u, v) normally -> (v, 1) with cost w(u, v).

**State space:** 2V vertices, standard edges between them. Run Dijkstra on this graph.
Answer = d[(n, 0)] or d[(n, 1)], whichever is smaller.

### 6.4 Example: Minimizing Maximum Edge Weight

**Problem:** Find a path from s to t minimizing the maximum edge weight along the path.

**Observation:** Dijkstra's algorithm works here despite the non-standard objective
function. Define d[v] = minimum over all paths from s to v of (maximum edge weight on
the path). Relaxation: d[v] = min(d[v], max(d[u], w(u, v))).

**Why Dijkstra works:** The key property needed is monotonicity -- extending a path can
never decrease the objective. For max-edge-weight, max(d[u], w(u, v)) >= d[u], so the
objective is non-decreasing. The same proof structure as standard Dijkstra applies:
when u is extracted with minimum d[u], no future relaxation can improve d[u].

**More generally,** Dijkstra works for any objective function f that satisfies:
1. f(path extended by edge e) >= f(path) for all paths and edges (monotonicity).
2. f is computed incrementally: f(P + e) = g(f(P), w(e)) for some function g.

### 6.5 General Principle

When faced with shortest-path-like problems with extra constraints:
1. Identify the extra state dimensions.
2. Verify that the state space is polynomially bounded.
3. Construct the expanded graph (possibly implicitly).
4. Apply the appropriate shortest path algorithm.

The expanded graph has |V'| = |V| * |S| vertices and proportionally more edges. The
algorithm's complexity scales accordingly: Dijkstra becomes O((|V||S| + |E||S|) log(|V||S|)).

---

## 7. Shortest Cycle

### 7.1 Problem Statement

Find the length of the shortest cycle in an unweighted graph.

### 7.2 BFS-Based Approach

**Algorithm:** For each vertex u, run BFS from u. During BFS, when we examine an edge
(v, x) and x is already visited with x != parent[v], we have found a cycle. Its length
is d[v] + d[x] + 1.

**Why this works:** The BFS tree gives shortest-path distances. When edge (v, x) closes
a cycle, the cycle consists of:
- The BFS tree path from u to v (length d[v]),
- The edge (v, x) (length 1),
- The BFS tree path from u to x traversed backwards (length d[x]).

Total cycle length = d[v] + d[x] + 1. (This may slightly overcount if u is not on the
actual shortest cycle, but the minimum over all u and all such events gives the correct
answer.)

**Correctness detail:** For the globally shortest cycle, there exists some vertex u on
the cycle such that BFS from u finds this cycle with the minimum d[v] + d[x] + 1.

**Complexity:** O(V * (V + E)). We run BFS from each vertex.

### 7.3 Weighted Graphs

For weighted graphs, replace BFS with Dijkstra. For each vertex u, run Dijkstra and
look for edges (v, x) where x is already finalized: cycle length through this edge is
d[v] + w(v, x) + d[x].

**Complexity:** O(V * (V + E) log V).

### 7.4 Directed Graphs

In directed graphs, shortest cycle is equivalent to finding the minimum-weight cycle.
One approach: Floyd-Warshall, then answer = min over all v of dp[v][v].

**Complexity:** O(V^3).
