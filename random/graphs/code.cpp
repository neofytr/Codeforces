#include <bits/stdc++.h>
using namespace std;

// A undirected (simple) graph G is an ordered pair (V, E) where V is a (non-empty)subset of N (the natural numbers)
// and E is a subset of the set F = {{u, v} such that u, v are in V and u != v}.
// The elements of V are called the vertices of G and each element {u, v} in E
// is called an edge of G and is denoted u-v (or v-u).

// A directed (simple) graph G is an ordered pair (V, E) where V is a (non-empty) subset of N (the natural numbers)
// and E is a subset of the cartesian product V x V.
// The elements of V are called the vertices of G and each element (u, v) in E 
// is called an edge of G and is denoted u->v.

// Let G is an undirected graph
// The degree of a vertex v of G is the number of edges v-u in G
// where u is a vertex of G.
// The sum of degrees of all the vertices of G = 2 * number of edges in G,
// since any edge of G contributes 2 to this sum (one for each of its endpoints). 

// Let G is a directed graph
// The indegree (outdegree) of a vertex v of G is the number of edges u->v (v->u) in G where u is a
// vertex of G.
// The number of edges of G (i.e., |E|) is equal to the sum of outdegrees (or indegrees) of all nodes
// of G.

// Let G = (V, E) is an undirected graph
// Let u, v be some vertices of G
// 1. A simple path is said to exist between nodes u and v if for some 1 <= k <= |E|, there exist k edges
// {ar, br} (1 <= r <= k) of G such that a1 = u, bk = v and br = a(r + 1) for all 1 <= r <= k - 1. The sequence
// of edges {a1, b1},..., {ak, bk} is then said to be a simple path between u and v (of length k). If u = v, then
// {v, v} is defined as the simple path between v and u.
// 2. u and v are connected if a simple path exists between them.
// 3. u is reachable from v if there exists a simple path between u and v.
// 4. A connected component of G is a maximal set of vertices of G such that for any vertex v 
// in the set, there is a between u and v for any vertex u in the set.
// 5. The set of connected components of G is a partition of V.
// 6. A cycle is said to exist in G if for some vertex v of G, there exist a simple path of length >= 2
// between v and v. The graph G is then said to be cyclic.

// Let G = (V, E) is an directed graph
// Let u, v be some vertices of G
// 1. A simple path is said to exist between nodes u and v if for some 1 <= k <= |E|, there exist k edges
// (ar, br) (1 <= r <= k) of G such that a1 = u, bk = v and br = a(r + 1) for all 1 <= r <= k - 1. The sequence
// of edges (a1, b1),..., (ak, bk) is then said to be a simple path between u and v (of length k). If u = v, then
// (v, v) is defined as the simple path between v and u.
// 2. u and v are connected if a simple path exists between them.
// 3. u is reachable from v if there exists a simple path between u and v.
// 4. A connected component of G is a maximal set of vertices of G such that for any vertex v 
// in the set, there is a between u and v for any vertex u in the set.
// 5. The set of connected components of G is a partition of V.
// 6. A cycle is said to exist in G if for some vertex v of G, there exist a simple path of length >= 2
// between v and v. The graph G is then said to be cyclic.

// Assume the graph G = (V, E) is stored using an adjacency list.
// Adjacency list representation of G has memory complexity O(|V| + |E|).
// DFS marks each vertex as visited the first time it is encountered.
// Hence, the DFS procedure is invoked at most once per vertex.
// Therefore, the total number of DFS calls is |V|.
//
// In the DFS call for a vertex v:
//   - O(1) work is done (marking visited, function overhead, etc.).
//   - The adjacency list of v is scanned once, which has size deg(v)
//     (or outdegree(v) in the directed case).
// Thus, the total running time is:
//
//   Σ ( O(1) + O(deg(v)) )  for all v ∈ V
// = O(|V|) + O( Σ deg(v) )
//
// For an undirected graph:
//   Σ deg(v) = 2|E|
//
// For a directed graph:
//   Σ outdegree(v) = |E|
//
// Hence, in both cases, the total time complexity of DFS is:
//   O(|V| + |E|)
// This bound is tight, since DFS must examine every vertex and every edge
// in the worst case.

// The space used by DFS consists of:
// 1. Adjacency list representation:
//    - O(|V| + |E|)
// 2. Visited array (or equivalent):
//    - O(|V|)
// 3. Recursion stack (or explicit stack for iterative DFS):
//    - In the worst case (e.g., a path graph), the recursion depth can be |V|
//    - Hence, O(|V|) auxiliary space
// Therefore, the total space complexity of DFS is:
//   O(|V| + |E|)

// The mapping pattern appears in many graph problems where we need to convert or copy
// structure while preserving relationships.
// The critical technique: add nodes to your map before processing their connections. This
// handles cycles gracefully, i.e, before recursing into an unmarked node, first mark it and
// then recurse into it to avoid cycles.

// Multi-source BFS is the same as single-source BFS, except you
// initialize the queue with multiple starting nodes. The rest is identical.
// Anytime you have multiple simultaneous starting points, think multi-source BFS.
// The core trick is pushing all sources into the queue before BFS loop starts. After that,
// this runs normally.
// We should think by reversing our perspective too. Instead of running BFS from each target cell to
// find the nearest source, run BFS once from all sources to find all targets.
// Multi-source BFS computes the distance from every cell to the nearest source in a single pass. This
// is faster than running single-source BFS multiple times.
// Anytime you need distance to the nearest element from a set, push all elements into the
// queue first, then run BFS once. The first visit to each cell gives you the answer.