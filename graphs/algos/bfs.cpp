#include <bits/stdc++.h>
using namespace std;

#define int long long 

// As a result of how this algorithm works, the path found by BFS to any node is the shortest path to that node, i.e,
// the path that contains the smallest number of edges in unweighted graphs

// The algorithm works in O(n + m) time, where n is the number of vertices and m is the number of edges

// The algorithm takes as input an unweighted graph and the id of the source vertex s
// The input graph can be directed or undirected, it does matter to the algorithm

// The algorithm can be understood as a fire spreading on the graph: at the zeroth step only the source s
// is on fire
// At each step, the fire burning at each vertex spreads to all of its neighbours
// In one iteration of the algorithm, the "ring of fire" is expanded in width by one unit

// More precisely, the algorithm can be stated as follows: Create a queue q which will contain the vertices
// to be processed as a boolean array used[] which indicates for each vertex, if it has been lit (or visited) or not

// Initially, push the source s to the queue and set used[s] = true, and for all other vertices v, set used[v] = false
// Then, loop until the queue is empty and in each iteration, pop a vertex from the front of the queue
// Iterate through all the edges going out of this vertex and if some of these edges go to vertices that are not already lit, 
// set them on fire and place them in the queue

// As a result, when the queue is empty, the "ring of fire" contains all vertices reachable from the source s, with 
// each vertex reached in the shortest possible way
// We can also calculate the lengths of the shortest paths (which just requires maintaining an array of path lengths dist[])
// as well as save information to restore all of these shortest paths (for this, it is necessary to maintain an array of
// "parents" p, which stores for each vertex the vertex from which we reached it)

void bfs(int n, int src, int dst, vector<vector<int>> &graph) {
	queue<int> que;
	vector<bool> used(n, false);
	vector<int> dist(n);
	vector<int> parent(n);

	que.push(src);
	parent[src] = src;
	dist[src] = 0;
	while(!que.empty()) {
		int x = que.front();
		que.pop();

		// process each node exactly once

		for (int v : graph[x]) {
			if (!used[v])
				dist[v] = dist[x] + 1, parent[v] = x, used[v] = true, que.push(v);

			if (x < v) // process each edge exactly once
				// process the edge (x, v) exactly once
		}
	}

	if (!used[dst])
		cout << "No path!\n";
	else {
		int x = dst;
		stack<int> path;
		while (x != parent[x])
			path.push(dst), x = parent[x];
		while(!path.empty())
			cout << path.top() << " ", path.pop();
		cout << endl;
	}
}

// Applications of BFS

// Find the shortest path from a source to other vertices in a unweighted graph

// Find all connected components in an undirected graph in O(n + m) time: To do this, we just run BFS
// starting from each vertex, except for vertices which have already been visited from previous runs
// Thus, we perform normal BFS from each of the vertices, but do not reset the used[] each and every time
// we get a new connected components, and the total running time will still be O(n + m) (performing multiple BFS
// on the graph without zeroing the array used[] is called a series of breadth first searches)

// Finding a solution of a problem or a game with the least number of moves, if each state of the game
// can be represented as a graph vertex, and the transitions from one state to the other are the edges of
// the graph

// 0-1 BFS: Finding the shortest path in a graph with weights 0 or 1

void binaryBFS() {
	int n, m;
	cin >> n >> m;

	int u, v, w;
	vector<vector<pair<int, int>>> graph;
	while(m--) 
		cin >> u >> v >> w, graph[u].push_back({v, w}), graph[v].push_back({u, w});

	int src;
	cin >> src;

	vector<int> dist(n, LLONG_MAX);
	dequeue<int> que;

	que.push(src);
	dist[src] = 0;
	while(!que.empty()) {
		int x = que.front();
		que.pop();

		for (auto &[v, w] : graph[x]) 
			if (dist[v] > dist[x] + w) {
				dist[v] = dist[x] + w
				if (!w) que.push_front(w);
				else que.push_back(w);
			}
	}
}

// Finding the shortest cycle in a directed unweighted graph
// Start a BFS from each vertex
// As soon as we try to go from the current vertex back to the source vertex, we have found the
// shortest cycle containing the source vertex
// At this point we can stop the BFS, and start a new BFS from the next vertex
// From all such cycles (at most one from each BFS), choose the shortest

// Finding all the edges that lie on any shortest path between a given pair of vertices (a, b)
// To do this, run two BFS, one from a and one from b
// Let da[] be the array containing the shortest distances from the first BFS (from a) and db[] be the
// array containing shortest distances obtained from the second BFS (from b)
// Now for every edge (u, v) it is easy to check whether that edge lies on any shortest path between a and b:
// The criterion is the condition da[u] + db[v] + 1 = da[b] or da[v] + db[u] + 1 = da[b]

// Finding all the vertices on any shortest path between a given pair of vertices (a, b)
// To accomplish this, run two BFS: one from a and one from b
// Let da[] be the array containing the shortest distances from the first BFS (from a) and db[] be the
// array containing shortest distances obtained from the second BFS (from b)
// Now for each vertex v it is easy to check whether it lies on any shortest path between a and b:
// The criterion is the condition da[v] + db[v] = da[b]

// If we are to find the shortest path from all nodes of a graph to a specific node v, we can
// reverse the edges of the graph and just find the shortest distance to all nodes of the new graph
// from node v