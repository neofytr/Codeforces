#include <bits/stdc++.h>
using namespace std;

// If every node of an undirected graph has at most two nodes, then for any connected component of the graph, only one of
// the following two are possible:
// 1. The component is a linear chain and the degree of all nodes except the ends (which have degree 1) of the chain have degree 2
// 2. The component is a pure cycle and the degree of all its node is 2
// 3. The component consists of a single node and the degree of all nodes in the component is 0

// So, a component of such a graph is a pure cycle iff all its nodes have degree 2

// A Bipartite graph is a graph whose vertices can be divided into two disjoint sets so that
// every edge connects two vertices from different sets (i.e, there are no edges which connect vertices from the same set)
// These sets are usually called sides

// A graph is bipartite iff there are no cycles of odd lengths in it
// A graph is bipartite iff it is two-colorable

// Bipartite Check

bool dfs(int x, vector<int> &color, vector<vector<int>> &graph) {
	for (int v : graph[x])
		if (color[v] == -1) {
			color[v] = !color[x];
			if (!dfs(v, color, graph))
				return false;
		} else if (color[v] != !color[x])
			return false;
	return true;
}

bool isBipartite(vector<vector<int>> &graph) {
	int n = graph.size();

	vector<int> color(n, -1);
	for (int r = 0; r < n; r++)
		if (color[r] == -1) {
			color[r] = 0;
			if (!dfs(r, color, graph))
				return false;
		}
	return true;
}