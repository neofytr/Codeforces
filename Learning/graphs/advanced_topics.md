# Advanced Graph Topics

A rigorous treatment of advanced graph algorithms and techniques that complement
the foundational material in traversals, shortest paths, and MST/DSU. Topics
covered: strongly connected components, articulation points and bridges, BFS
variants for shortest-path counting and property optimization, and 2D dominance
queries.

---

## 1. Strongly Connected Components (Kosaraju's Algorithm)

### 1.1 Definitions

**Definition (Strongly Connected Component).** A *strongly connected component*
(SCC) of a directed graph G = (V, E) is a maximal subset of vertices C such that
for every pair of vertices u, v in C, there exists a directed path from u to v
and a directed path from v to u.

**Definition (Mutual Reachability).** Two vertices u, v in V are *mutually
reachable* if there exists a directed path from u to v and from v to u.

### 1.2 Equivalence Relation on Vertices

**Theorem.** Mutual reachability is an equivalence relation on V, and therefore
the vertices of any directed graph partition into disjoint SCCs.

**Proof.** We verify the three properties of an equivalence relation:

1. *Reflexive*: Every vertex v can reach itself via the trivial (empty) path,
   so v is mutually reachable with itself.

2. *Symmetric*: If u is mutually reachable with v, then by definition there
   exist paths u -> v and v -> u. Therefore v is mutually reachable with u.

3. *Transitive*: If u is mutually reachable with v (paths u -> v and v -> u
   exist) and v is mutually reachable with w (paths v -> w and w -> v exist),
   then u can reach w via u -> v -> w and w can reach u via w -> v -> u.
   Therefore u is mutually reachable with w.

Since mutual reachability is an equivalence relation, its equivalence classes
partition V into disjoint subsets. Each such equivalence class is an SCC, and
maximality follows from the partition property: any vertex mutually reachable
with a member of class C is already in C. QED.

**Corollary.** A vertex v lies on a directed cycle if and only if it belongs to
an SCC of size >= 2, or to an SCC of size 1 that contains a self-loop.

### 1.3 Finding the SCC of a Specific Vertex

**Observation.** For any vertex u in V:

    u in SCC(v) <==> (v can reach u) AND (u can reach v)

This yields a simple O(V + E) algorithm for the SCC containing a given vertex v:

1. Perform BFS/DFS from v on the original graph G. Let F = set of all vertices
   reachable from v.

2. Construct the reverse graph G^R (reverse all edge directions). Perform
   BFS/DFS from v on G^R. Let R = set of all vertices reachable from v in G^R.
   Equivalently, R is the set of vertices that can reach v in G.

3. SCC(v) = F intersection R.

**Proof of correctness.** A vertex u is in SCC(v) iff there is a path v -> u
(meaning u in F) and a path u -> v (meaning u is reachable from v in G^R, i.e.,
u in R). Therefore SCC(v) = F intersection R.

**Complexity.** Each BFS/DFS runs in O(V + E). Total: O(V + E) time, O(V) space.

**Implementation** (from `graphs/algos/notes/kosaraju.cpp`):

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n, m;
    cin >> n >> m;

    int u, v;
    vector<vector<int>> graph(n);
    vector<vector<int>> revGraph(n);
    while(m--)
        cin >> u >> v, graph[u].push_back(v), revGraph[v].push_back(u);

    int src;
    cin >> src;

    // We want to find all the nodes in the SCC of src

    vector<int> vis(n, false), revVis(n, false);
    queue<int> que;

    // Forward BFS on G: find all vertices reachable FROM src
    que.push(src);
    vis[src] = true;
    while(!que.empty()) {
        int x = que.front();
        que.pop();
        for (int v : graph[x])
            if (!vis[v])
                vis[v] = true, que.push(v);
    }

    // Forward BFS on G^R: find all vertices that can REACH src in G
    que.push(src);
    revVis[src] = true;
    while(!que.empty()) {
        int x = que.front();
        que.pop();
        for (int v : revGraph[x])
            if (!revVis[v])
                revVis[v] = true, que.push(v);
    }

    // SCC(src) = intersection of both sets
    vector<int> scc;
    for (int node = 0; node < n; node++)
        if (revVis[node] && vis[node])
            scc.push_back(node);
    return 0;
}
```

### 1.4 Kosaraju's Full Algorithm (All SCCs)

The approach in Section 1.3 finds only the SCC of a single vertex. To find *all*
SCCs of the entire graph, we use Kosaraju's algorithm:

**Algorithm (Kosaraju, O(V + E)):**

1. Run DFS on the original graph G, visiting all vertices. When a vertex
   finishes (all descendants fully explored), push it onto a stack S. This
   records vertices in order of increasing finish time.

2. Construct the reverse graph G^R.

3. Pop vertices from S one at a time (highest finish time first). For each
   unvisited vertex, run DFS on G^R starting from it. All vertices visited
   in this DFS form one SCC.

**Theorem.** Kosaraju's algorithm correctly identifies all SCCs.

**Proof sketch.** Let C_1, C_2, ..., C_k be the SCCs of G. The *condensation*
of G is the DAG D where each SCC is contracted to a single vertex, with edge
(C_i, C_j) in D iff there exists an edge (u, v) in G with u in C_i, v in C_j.

Key lemma: if there is an edge (C_i, C_j) in the condensation DAG, then the
maximum finish time in C_i is greater than the maximum finish time in C_j during
the first DFS.

By processing vertices in decreasing finish time order:
- We start with a vertex in the SCC with the highest finish time. In the
  condensation DAG, this SCC has no incoming edges from other SCCs (it is a
  "source" in the condensation).
- DFS on G^R from this vertex cannot leave the SCC, because in G^R the
  condensation edges are reversed, making this SCC a "sink" with no outgoing
  condensation edges.
- After marking all vertices of this SCC as visited, we continue with the next
  unvisited vertex of highest finish time, which is now a source in the
  remaining condensation DAG.

By induction, each DFS in step 3 discovers exactly one SCC. QED.

### 1.5 Condensation Graph

**Definition (Condensation).** Given G = (V, E) with SCCs C_1, ..., C_k, the
*condensation graph* is the DAG D = ({C_1, ..., C_k}, E_D) where (C_i, C_j)
in E_D iff there exist u in C_i, v in C_j with (u, v) in E and i != j.

**Theorem.** The condensation graph is a DAG.

**Proof.** Suppose for contradiction that D contains a cycle
C_{i1} -> C_{i2} -> ... -> C_{it} -> C_{i1}. Then every vertex in the union of
these SCCs can reach every other vertex (by traversing through the inter-SCC
edges). This contradicts the maximality of each SCC, since the union would form
a larger strongly connected set. QED.

**Applications of condensation:**
- Longest path in the condensation DAG (DP on DAG)
- Reachability queries: u can reach v iff SCC(u) can reach SCC(v) in D
- Minimum number of edges to add to make the entire graph strongly connected:
  max(sources in D, sinks in D) where sources/sinks refer to vertices with
  in-degree/out-degree 0 in D (special case: if the graph is already strongly
  connected, the answer is 0).

---

## 2. Articulation Points and Bridges

### 2.1 Definitions

**Definition (Articulation Point).** A vertex v in an undirected connected graph
G = (V, E) is an *articulation point* (or *cut vertex*) if the graph G - v
(obtained by removing v and all its incident edges) is disconnected.

**Definition (Bridge).** An edge (u, v) in an undirected connected graph
G = (V, E) is a *bridge* (or *cut edge*) if the graph G - (u,v) (obtained by
removing that edge) is disconnected.

**Motivation.** Articulation points and bridges identify structural
vulnerabilities: vertices or edges whose failure disconnects the network.

### 2.2 DFS Tree Structure

**Proposition.** In a DFS of an undirected graph, every edge is either a *tree
edge* (part of the DFS tree) or a *back edge* (connecting a vertex to an
ancestor in the DFS tree). There are no cross edges in undirected DFS.

**Proof.** Suppose edge (u, v) is not a tree edge. Without loss of generality,
assume u is discovered before v. Since (u, v) exists, v must be discovered
during the DFS call from u (otherwise, when v was discovered, it would have
found the edge to u, which was already visited -- making u an ancestor of v).
But if v was discovered during u's DFS, then v is a descendant of u and (u, v)
is a back edge. QED.

### 2.3 Tarjan's Algorithm

Tarjan's algorithm finds all bridges and articulation points in O(V + E) time
using a single DFS.

**Definitions used in the algorithm:**

- disc[v]: the discovery time of vertex v in the DFS (a timestamp that
  increments with each new vertex discovered).

- low[v]: the minimum discovery time reachable from the subtree rooted at v
  using tree edges and at most one back edge.

**Recurrence for low[v]:**

    low[v] = min(
        disc[v],
        min over all back edges (v, w):  disc[w],
        min over all tree edges (v, c) where c is a child of v:  low[c]
    )

**Intuition.** low[v] captures how "high up" in the DFS tree we can reach from
v's subtree using back edges. If low[v] equals disc[v], no back edge from v's
subtree reaches above v, meaning v's subtree is only connected to the rest of
the graph through v (or through the edge from v to its parent).

### 2.4 Bridge Detection

**Theorem.** A tree edge (u, v) where u is the parent of v in the DFS tree is a
bridge if and only if low[v] > disc[u].

**Proof.**

(=>) Suppose (u, v) is a bridge. Then removing (u, v) disconnects v's subtree
from u. This means no back edge from v's subtree reaches u or any ancestor of u.
Therefore the minimum discovery time reachable from v's subtree is at best
disc[v] > disc[u] (since v is discovered after u). Hence low[v] > disc[u].

(<=) Suppose low[v] > disc[u]. Then no vertex in v's subtree has a back edge to
u or any ancestor of u. Therefore the only connection between v's subtree and
the rest of the graph is the tree edge (u, v). Removing it disconnects v's
subtree. Hence (u, v) is a bridge. QED.

**Note on the strict inequality.** We require low[v] > disc[u], not
low[v] >= disc[u]. If low[v] = disc[u], there is a back edge from v's subtree
to u, so removing (u, v) still leaves a path from v to u via that back edge.

### 2.5 Articulation Point Detection

**Theorem.** A vertex u is an articulation point if and only if one of the
following holds:

1. u is the root of the DFS tree and u has >= 2 children in the DFS tree.

2. u is not the root and there exists a child v of u in the DFS tree such that
   low[v] >= disc[u].

**Proof of condition 1.** If u is the root with >= 2 DFS tree children, then
no tree child can reach another tree child's subtree without going through u
(since back edges only go to ancestors, and u is the root). Removing u
disconnects the subtrees. Conversely, if u is the root with <= 1 child,
removing u leaves a connected graph (the single subtree, or empty graph).

**Proof of condition 2.** If u is not the root and has a child v with
low[v] >= disc[u], then no vertex in v's subtree has a back edge to a proper
ancestor of u. Hence v's subtree connects to the rest of the graph only through
u. Removing u disconnects v's subtree. Conversely, if low[v] < disc[u] for all
children v, then every child's subtree can reach an ancestor of u, so removing
u does not disconnect the graph. QED.

### 2.6 Pseudocode

```
function dfs(u, parent):
    disc[u] = low[u] = timer++
    childCount = 0

    for each neighbor v of u:
        if disc[v] == -1:           // tree edge
            childCount++
            dfs(v, u)
            low[u] = min(low[u], low[v])

            // Bridge check
            if low[v] > disc[u]:
                (u, v) is a bridge

            // Articulation point check (non-root)
            if parent != -1 and low[v] >= disc[u]:
                u is an articulation point

        else if v != parent:        // back edge
            low[u] = min(low[u], disc[v])

    // Articulation point check (root)
    if parent == -1 and childCount >= 2:
        u is an articulation point
```

**Complexity.** O(V + E) -- a single DFS traversal.

### 2.7 Relation to Biconnected Components

**Definition (Biconnected Component).** A *biconnected component* (or *2-edge-
connected component* / *2-vertex-connected component*) is a maximal subgraph
that contains no bridge (edge version) or no articulation point (vertex
version).

Bridges partition the edge set into biconnected components (edge version):
removing all bridges splits the graph into maximal 2-edge-connected subgraphs.
Articulation points partition the graph into biconnected components (vertex
version), where each component is a maximal 2-vertex-connected subgraph.

---

## 3. BFS Variants: Counting and Enumerating Shortest Paths

### 3.1 Counting Shortest Paths

**Problem.** Given an unweighted graph G = (V, E) and a source vertex s, for
each vertex v, compute cnt[v] = the number of distinct shortest paths from s
to v.

**Algorithm.** Modify standard BFS to maintain a count array alongside the
distance array:

- Initialize: dist[s] = 0, cnt[s] = 1. For all other v: dist[v] = infinity,
  cnt[v] = 0.

- During BFS, when processing edge (u, v):
  - If dist[v] = infinity (first discovery): set dist[v] = dist[u] + 1,
    cnt[v] = cnt[u], push v to queue.
  - If dist[v] = dist[u] + 1 (another shortest path found): set
    cnt[v] += cnt[u].

**Theorem.** This algorithm correctly computes cnt[v] for all v.

**Proof.** By induction on dist[v] = d.

*Base case (d = 0)*: Only v = s has distance 0, and cnt[s] = 1. Correct.

*Inductive step*: Assume cnt[u] is correct for all u with dist[u] < d. Consider
a vertex v with dist[v] = d. The shortest paths from s to v are exactly those
that go from s to some neighbor u of v with dist[u] = d - 1, then take edge
(u, v). The number of such paths is:

    cnt[v] = sum over all neighbors u of v with dist[u] = d - 1: cnt[u]

BFS processes all vertices at distance d - 1 before those at distance d. Each
edge (u, v) with dist[u] = d - 1 contributes cnt[u] to cnt[v] exactly once
(either via the first-discovery case or the equal-distance case). By the
inductive hypothesis, each cnt[u] is correct. Therefore cnt[v] is correct. QED.

**Implementation** (from `graphs/algos/notes/bfs.cpp`):

```cpp
void countAllShortestPaths() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int src;
    cin >> src;

    vector<int> dist(n, INT_MAX);
    vector<long long> count(n, 0);

    queue<int> que;
    dist[src] = 0;
    count[src] = 1;
    que.push(src);

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (int v : graph[u]) {
            if (dist[v] == INT_MAX) {
                dist[v] = dist[u] + 1;
                count[v] = count[u];
                que.push(v);
            } else if (dist[v] == dist[u] + 1) {
                count[v] += count[u];
            }
        }
    }
}
```

**Complexity.** O(V + E) time, O(V) space.

### 3.2 All Shortest Paths via Parent Tracking

**Problem.** Given an unweighted graph and source s, for each vertex v, find
all vertices that can be the predecessor of v on some shortest path from s.

**Algorithm.** Maintain parents[v] = list of all vertices u such that
dist[u] + 1 = dist[v] and (u, v) is an edge.

- During BFS, when processing edge (u, v):
  - If dist[v] = infinity: set dist[v] = dist[u] + 1, parents[v] = {u},
    push v.
  - If dist[v] = dist[u] + 1: append u to parents[v].

**Theorem.** parents[v] contains exactly all predecessors of v on shortest
paths from s.

**Proof.** A vertex u is a predecessor of v on some shortest path iff (u, v)
is an edge and dist[u] + 1 = dist[v]. The algorithm adds u to parents[v]
precisely when both conditions hold (either on first discovery or when finding
another equal-length path). No vertex is added when dist[u] + 1 != dist[v],
since in BFS, dist[u] + 1 < dist[v] is impossible when v is already discovered
(BFS processes vertices in non-decreasing distance order). QED.

**Reconstructing all shortest paths** (backtracking DFS from target):

```cpp
void dfsReconstruct(int u, int src, vector<vector<int>>& parents,
                    vector<int>& path) {
    if (u == src) {
        vector<int> fullPath = path;
        reverse(fullPath.begin(), fullPath.end());
        for (int node : fullPath) cout << node << " ";
        cout << "\n";
        return;
    }
    for (int p : parents[u]) {
        path.push_back(p);
        dfsReconstruct(p, src, parents, path);
        path.pop_back();
    }
}
```

**Warning.** The number of shortest paths can be exponential, so explicit
enumeration is only feasible when the count is small.

### 3.3 DP on the Shortest-Path DAG

**Observation.** The subgraph induced by all shortest-path edges (i.e., edges
(u, v) where dist[u] + 1 = dist[v]) forms a DAG, because dist strictly
increases along each edge.

This DAG structure enables efficient DP without enumerating paths:

**Counting paths via DP on parents[]:**

```cpp
long long countPathsDP(int src, int dst, vector<vector<int>>& parents) {
    int n = parents.size();
    vector<long long> dp(n, -1);

    function<long long(int)> solve = [&](int u) {
        if (u == src) return 1LL;
        if (dp[u] != -1) return dp[u];
        long long ways = 0;
        for (int p : parents[u])
            ways += solve(p);
        return dp[u] = ways;
    };

    return solve(dst);
}
```

**Theorem.** countPathsDP correctly returns the number of shortest paths from
src to dst.

**Proof.** The recurrence dp[v] = sum of dp[p] for p in parents[v], with base
case dp[src] = 1, counts the number of paths in the shortest-path DAG from src
to v. Since the DAG has no cycles, the memoized recursion terminates and
computes each dp[v] exactly once. The value dp[dst] equals the number of
distinct src-to-dst paths in the DAG, which by construction equals the number
of shortest paths in the original graph. QED.

### 3.4 Maximizing/Minimizing Properties on Shortest Paths

**Problem.** Given an unweighted graph with a value happy[v] at each vertex,
among all shortest paths from src to dst, find the one maximizing the maximum
happiness of any node along the path.

**Algorithm.** During BFS, maintain dp[v] = best achievable property value
along any shortest path from src to v:

- If discovering v for the first time from u:
  dp[v] = max(happy[v], dp[u])

- If finding another shortest path to v from u:
  dp[v] = max(dp[v], dp[u])

**Theorem.** This correctly computes dp[v] = max over all shortest paths P
from src to v of (max over all w on P of happy[w]).

**Proof.** By induction on dist[v]. The base case dp[src] = happy[src] is
trivially correct. For the inductive step, any shortest path to v passes
through some neighbor u with dist[u] = dist[v] - 1 as its penultimate vertex.
The maximum happiness on such a path is max(happy[v], dp[u]). Taking the
maximum over all such u gives dp[v]. The BFS update rules compute exactly this:
the first discovery initializes dp[v] from one such u, and subsequent
equal-distance discoveries update dp[v] with contributions from other such u
values. QED.

**Implementation** (from `graphs/algos/notes/bfs.cpp`):

```cpp
int maximizePropertyOnShortestPath() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> happy(n);
    for (int &r : happy) cin >> r;

    int src, dst;
    cin >> src >> dst;

    vector<int> dist(n, INT_MAX);
    vector<int> dp(n, -1);

    queue<int> que;
    dist[src] = 0;
    dp[src] = happy[src];
    que.push(src);

    while (!que.empty()) {
        int x = que.front();
        que.pop();

        for (int v : graph[x]) {
            if (dist[v] > dist[x] + 1) {
                dist[v] = dist[x] + 1;
                dp[v] = max(happy[v], dp[x]);
                que.push(v);
            } else if (dist[v] == dist[x] + 1) {
                dp[v] = max(dp[v], dp[x]);
            }
        }
    }

    cout << dp[dst] << endl;
    return dp[dst];
}
```

### 3.5 Other BFS Applications

From the codebase notes, additional applications of BFS include:

1. **Shortest cycle in a directed unweighted graph**: Start BFS from each
   vertex. As soon as we attempt to visit the source vertex again, we have
   found the shortest cycle through it. Overall O(V(V + E)).

2. **Edges on any shortest path between (a, b)**: Run BFS from a (giving da[])
   and from b (giving db[]). Edge (u, v) lies on some shortest path from a to b
   iff da[u] + 1 + db[v] = da[b] or da[v] + 1 + db[u] = da[b].

3. **Vertices on any shortest path between (a, b)**: Vertex v lies on some
   shortest path iff da[v] + db[v] = da[b].

4. **0-1 BFS**: For graphs with edge weights in {0, 1}, use a deque instead of
   a queue. Push to front for 0-weight edges, to back for 1-weight edges.
   Gives O(V + E) shortest paths (same as Dijkstra but without the log factor).

---

## 4. 2D Dominance Queries

### 4.1 Problem Statement

Given a set of n points P = {(x_1, y_1), ..., (x_n, y_n)} in the plane,
answer multiple queries of the form: given (x_q, y_q), does there exist a point
(x, y) in P such that x >= x_q and y >= y_q? If so, find one such point.

This is also known as a *top-right quadrant dominance query*.

### 4.2 Solution

**Algorithm:**

1. Sort all points by x-coordinate in descending order.

2. Build a suffix maximum array on the y-coordinates: suffMaxY[i] = max(y_i,
   y_{i+1}, ..., y_{n-1}) where points are indexed after sorting.

3. For each query (x_q, y_q):
   a. Binary search in the sorted x-array for the first index i with x_i >= x_q.
   b. If i exists and suffMaxY[i] >= y_q, then a dominating point exists
      (tracked via a companion index array).

**Theorem.** This algorithm correctly answers dominance queries.

**Proof.** After sorting by x descending, the points at indices i, i+1, ...,
n-1 are exactly those with x-coordinate >= some threshold. Binary search finds
the smallest index i such that all points at positions i through n-1 have
x >= x_q. Among these points, we need at least one with y >= y_q. The suffix
maximum suffMaxY[i] = max(y_i, ..., y_{n-1}) is the largest y-coordinate among
all candidate points. If suffMaxY[i] >= y_q, at least one candidate satisfies
both conditions. If suffMaxY[i] < y_q, no candidate does. QED.

**Complexity:**
- Preprocessing: O(n log n) for sorting, O(n) for suffix maximum.
- Each query: O(log n) for binary search.
- Space: O(n).

**Implementation** (from `graphs/algos/notes/2dDominanceQuery.cpp`):

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n;
    cin >> n;

    int x, y;
    vector<pair<int, int>> pts;
    for (int r = 1; r <= n; r++)
        cin >> x >> y, pts.push_back({x, y});

    // Sort points by x descending
    sort(pts.begin(), pts.end(), [](auto &a, auto &b) {
        return a.first > b.first;
    });

    // Compute suffix max array for y and store index of that max
    vector<int> maxY(n);
    vector<int> maxIdx(n);

    maxY[n - 1] = pts[n - 1].second;
    maxIdx[n - 1] = n - 1;

    for (int r = n - 2; r >= 0; r--) {
        if (pts[r].second > maxY[r + 1])
            maxY[r] = pts[r].second, maxIdx[r] = r;
        else
            maxY[r] = maxY[r + 1], maxIdx[r] = maxIdx[r + 1];
    }

    // Extract x-coordinates for binary search
    vector<int> xs;
    for (auto &p : pts) xs.push_back(p.first);

    int q;
    cin >> q;
    int xr, yr;
    while(q--) {
        cin >> xr >> yr;

        // Binary search for first point with x >= xr
        // xs is sorted descending, so we use greater<int>()
        auto itr = lower_bound(xs.begin(), xs.end(), xr, greater<int>());

        if (itr != xs.end()) {
            int idx = itr - xs.begin();
            int candidateIdx = maxIdx[idx];
            pair<int, int> pt = pts[candidateIdx];
            if (pt.second >= yr)
                cout << "YES: (" << pt.first << "," << pt.second << ")\n";
            else
                cout << "NO\n";
        } else {
            cout << "NO\n";
        }
    }
}
```

### 4.3 Correctness of Binary Search on Descending Array

**Lemma.** Using `lower_bound` with `greater<int>()` on a descending array of
x-coordinates finds the last position with x >= x_q.

**Proof.** `lower_bound(begin, end, val, comp)` returns an iterator to the
first element for which `comp(element, val)` is false. With `comp =
greater<int>()`, `comp(x, xr)` is `x > xr`. The function returns the first
position where x <= xr, which is equivalent to: all positions before it satisfy
x > xr, and positions from it onward satisfy x <= xr. Therefore the range
[0, itr) contains all points with x > xr, and the element at itr (if it equals
xr) also satisfies x >= xr. More precisely, all elements in [0, itr] with
x >= xr are valid candidates, and suffMaxY at the found index covers all of
them. QED.

### 4.4 Extensions

- **Online queries with insertions**: Use a balanced BST (e.g., `std::set`)
  keyed by x, maintaining a "staircase" of maximal points (those not dominated
  by any other point). Queries and updates in O(log n) amortized.

- **k-d trees**: For higher-dimensional dominance queries, k-d trees offer
  O(n^{1-1/d} + k) query time for d dimensions and k reported points.

- **Persistent segment trees**: For 2D dominance counting (how many points
  dominate the query), sweep by x and use a persistent segment tree on
  y-coordinates. O(n log n) preprocessing, O(log n) per query.

---

## 5. Summary of Complexities

| Algorithm / Technique                  | Time         | Space  |
|----------------------------------------|--------------|--------|
| SCC of specific vertex (dual BFS)      | O(V + E)     | O(V)   |
| Kosaraju (all SCCs)                    | O(V + E)     | O(V+E) |
| Tarjan (bridges + articulation pts)    | O(V + E)     | O(V)   |
| BFS shortest path counting            | O(V + E)     | O(V)   |
| BFS all parents tracking              | O(V + E)     | O(V+E) |
| 2D dominance preprocessing            | O(n log n)   | O(n)   |
| 2D dominance per query                | O(log n)     | --     |
