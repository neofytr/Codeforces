#include <bits/stdc++.h>
using namespace std;

#define int long long

// DFS is a straightforward graph traversal technique
// The algorithm begins at the starting node, and proceeds to all other nodes that are reachable from the
// starting node using the edges of the graph

// DFS always follows a single path in the graph as long as it finds new nodes
// After this, it returns to previous nodes and begins to explore other parts of the graph
// The algorithm keeps track of visited nodes, so that it processes each node exactly once

// The time complexity of DFS is O(n + m), where n is the number of nodes and m is the number of edges in the graph,
// because the algorithm visits each node and edge exactly once

// Assumes that node is not visited when its called
// So, always check if node is visited before calling this function on node
void dfs(int node, vector<bool> &vis, vector<vector<int>> &graph) {
	vis[node] = true;
	for (int v : graph[node])
		if (!vis[v])
			dfs(v, vis, graph);
} 

// BFS visits the nodes in increasing order of their distance from the starting node
// Thus, we can calculate the distance from the starting node to all other nodes using BFS
// BFS goes through the nodes one level after another
// First the search explores the nodes whose distance from the starting node is 1, then the nodes whose
// distance is 2, and so on
// This process continues until all the nodes have been visited

// The time complexity of BFS is O(n + m) as each node and edge has been visited exactly once

void bfs() {
	int n;
	cin >> n;

	int u, v;
	vector<vector<int>> graph(n);
	for (int r = 1; r <= n; r++)
		cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

	queue<pair<int, int>> que; // node, parent
	vector<int> dist(n, LLONG_MAX);
	vector<int> parent(n);

	int src;
	cin >> src;
	que.push(src);
	dist[src] = 0;
	parent[src] = src;

	while(!que.empty()) {
		auto [x, p] = que.front();
		que.pop();

		// process each node here exactly once

		for (int v : graph[x]) {
			if (dist[v] > dist[x] + 1) {
				dist[v] = dist[x] + 1;
				parent[v] = x;
				que.push(v);
			}

			if (x < v) { // process each edge in the graph exactly once
				// process the edge (x, v) here exactly once
			}
		}		
	}
}

// Another way to find out whether a graph contains a cycle is to simply calculate the number of
// nodes and edges in every component
// If a component contains c nodes and no cycle, it must contain exactly c - 1 edges (so it has to be a tree)
// If there are c or more edges, the component surely contains a cycle