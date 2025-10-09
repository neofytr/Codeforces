#include <bits/stdc++.h>
using namespace std;

#define int long long

// A **Strongly Connected Component (SCC)** of a directed graph is a *maximal* subset of vertices C
// such that for every pair of vertices (a, b) in C, there exists a path from a → b and from b → a.
//
// -----------------------------------------------------------------------------
// Key Properties:
// -----------------------------------------------------------------------------
// 1. **Mutual reachability** (i.e., "a can reach b and b can reach a") defines an equivalence relation
//    over the set of vertices, since it is:
//      - Reflexive   → every vertex can reach itself
//      - Symmetric   → if a can reach b and b can reach a
//      - Transitive  → if a ↔ b and b ↔ c, then a ↔ c
//    Hence, the vertices of the graph partition into *disjoint* SCCs.
//
// 2. A vertex lies on a directed cycle **iff** it belongs to an SCC of size ≥ 2,
//    or to an SCC of size = 1 that contains a self-loop.
//
// -----------------------------------------------------------------------------
// Problem:
// -----------------------------------------------------------------------------
// Given a directed graph G(V, E) and a vertex v ∈ V,
// we want to find all vertices that belong to the *same SCC* as v.
//
// -----------------------------------------------------------------------------
// Observation:
// -----------------------------------------------------------------------------
// For any vertex u ∈ V,
//    u is in the same SCC as v  ⇔  (v → u) and (u → v)
//
// In other words:
// - If there is a path from v to u  (v → u),
//   and a path from u to v  (u → v),
//   then u and v are mutually reachable → same SCC.
// - If either direction is missing, u is *not* in the same SCC as v.
//
// -----------------------------------------------------------------------------
// Approach:
// -----------------------------------------------------------------------------
// 1. Perform a BFS (or DFS) from v on the original graph G
//      → This gives all vertices reachable *from* v (denote this set R₁).
//
// 2. Construct the **reversed graph** Gʳ (all edges reversed),
//    and perform a BFS from v on Gʳ
//      → This gives all vertices that can reach v in G,
//        i.e., all vertices *reachable from v* in Gʳ (denote this set R₂).
//
// 3. The intersection of these two sets, R₁ ∩ R₂,
//    contains exactly the vertices that are both reachable from v
//    and can reach v — i.e., the vertices in the same SCC as v.
//
// -----------------------------------------------------------------------------
// Complexity:
// -----------------------------------------------------------------------------
// Each BFS runs in O(N + M), where N = |V| and M = |E|.
// Therefore, the total time complexity is O(N + M), and space complexity is O(N).
//
// -----------------------------------------------------------------------------
// Summary:
// -----------------------------------------------------------------------------
// - Forward BFS on G → vertices reachable from v
// - Forward BFS on Gʳ → vertices that can reach v
// - Intersection → SCC(v)

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

	que.push(src);
	vis[src] = true;
	while(!que.empty()) {
		int x = que.front();
		que.pop();

		for (int v : graph[x])
			if (!vis[v])
				vis[v] = true, que.push(v);
	}

	que.push(src);
	revVis[src] = true;
	while(!que.empty()) {
		int x = que.front();
		que.pop();

		for (int v : revGraph[x])
			if (!revVis[v])
				revVis[v] = true, que.push(v);
	}

	vector<int> scc;

	for (int node = 0; node < n; node++)
		if (revVis[node] && vis[node])
			scc.push(node);
	return 0;
}
