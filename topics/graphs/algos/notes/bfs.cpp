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

	que.push_front(src);
	dist[src] = 0;
	while(!que.empty()) {
		int x = que.front();
		que.pop_front();

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

// Maximizing/Minimizing some property on all the shortest paths from some src to dst in an unweighted graph
// This is based on the fact that 
// 1. Any node is reached from all its shortest paths from a node that is one above in level (one less in distance) from the former node
// 2. Let u1, u2, u3, ..., un are the neighbours of a node v that are one distance less than v in a BFS from some source
//    This method works only if the property we want to calculate dp[k] (the value of the property calculated from all shortest paths from src to k)
// 	  has a recurrence of the following type:
//    dp[v] = calculate(dp[u1], dp[u2], ..., dp[un]);
//    and this calculate function can work incrementally (that is, it builds the final value as the values dp[u1], .., dp[un] are coming)
int prop() {
	int n, m;
	cin >> n >> m;

	int u, v;
	vector<vector<int>> graph(n);
	while (m--) 
		cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

	vector<int> happy(n);
	for (int &r : happy)
		cin >> r;

	int src, dst;
	cin >> src >> dst;
	vector<int> dist(n, LLONG_MAX);
	vector<int> dp(n, -1); // dp[r] is the largest value of happiness of a node on any shortest path from src to r
	queue<int> que;

	que.push(src);
	dist[src] = 0;
	dp[src] = happy[src];
	while(!que.empty()) {
		int x = que.front();
		que.pop();

		for (int v : graph[x])
			if (dist[v] > dist[x] + 1)
				dist[v] = dist[x] + 1, dp[v] = max(happy[v], dp[x]), que.push(v); // <- this is the first time we reach node v (through a shortest path), the calculate function works with dp[u1]
			else if (dist[v] == dist[x] + 1) // <- these are all other shortest ways to reach node v, here the calculate function builds incrementally the final result using dp[u2], ..., dp[un]
				dp[v] = max(dp[x], dp[v]);
	}
	cout << dp[dst] << endl;
}

/*
    ============================================================
    =======  Using parents[] to compute properties  ============
    ============================================================

    // parents[v] = all nodes u such that dist[u] + 1 = dist[v]
    // i.e., all predecessors of v on some shortest path from src.

    // Once we have parents[], we can compute properties over *all shortest paths*
    // in two main ways:

    // 1. Backtracking DFS:
    //    -> Explicitly enumerate every shortest path by starting from the target
    //       and recursively following parents[] until we reach src.
    //    -> At each complete path, evaluate the property (e.g., sum of values,
    //       maximum happiness, etc.) and aggregate.
    //    -> Exponential in the number of paths → works if number of shortest paths is small.

    // 2. Dynamic Programming over DAG of shortest paths:
    //    -> Since BFS ensures dist[] is non-decreasing along parents[],
    //       the graph (src → … → v) restricted to shortest paths is a DAG.
    //    -> We can DP from src forward (or dst backward) to aggregate properties
    //       across *all* shortest paths without enumerating them.
    //    -> Much more efficient when number of paths is huge.

    // Example below: counting paths using DP on parents[],
    // then extending to compute sum of happiness along all shortest paths.
*/

// Example property: count number of shortest paths using parents[]
long long countPathsDP(int src, int dst, vector<vector<int>>& parents) {
    int n = parents.size();
    vector<long long> dp(n, -1);

    function<long long(int)> solve = [&](int u) {
        if (u == src) return 1LL;   // base case: only one path (the trivial one)
        if (dp[u] != -1) return dp[u];

        long long ways = 0;
        for (int p : parents[u]) 
            ways += solve(p);

        return dp[u] = ways;
    };

    return solve(dst);
}

// Example property: sum of happiness values along all shortest paths
long long sumHappinessOnAllPaths(int src, int dst, vector<int>& happy, vector<vector<int>>& parents) {
    int n = parents.size();
    vector<long long> dp(n, -1);

    function<long long(int)> solve = [&](int u) {
        if (u == src) return (long long)happy[u]; // base case

        if (dp[u] != -1) return dp[u];

        long long total = 0;
        for (int p : parents[u]) {
            total += solve(p) + happy[u]; 
            // add current node’s happiness to every path that reaches u
        }
        return dp[u] = total;
    };

    return solve(dst);
}


// If you want to maintain a property/value on some shortest path between a source and nodes reachable from source (or some specific node reachable from src),
// you can modify the queue used to perform the BFS to maintain this property/value as ->
// queue<pair<int, int>> que // (current_node, property/value on a shortest path from src to current_node)
// We cannot guarantee which shortest path we calculate the property one

#include <bits/stdc++.h>
using namespace std;

/*
    ============================================================
    =============  BFS with Shortest Paths Variants  ============
    ============================================================

    // If you want to maintain a property/value along *some* shortest path 
    // between a source node and nodes reachable from it,
    // you can simply modify the BFS queue to also carry this property/value like ->
    //
    // queue<pair<int, int>> que; // (current_node, property/value on a shortest path from src to current_node)
    //
    // This way BFS ensures shortest distances, but you are only guaranteed
    // that the property is calculated along *one* arbitrary shortest path. 
    // Which shortest path exactly? BFS does not guarantee — it just depends
    // on the order nodes are discovered.
    //
    // ------------------------------------------------------------
    //
    // If you want to maintain a property/value aggregated from *all shortest paths*
    // between a source node and nodes reachable from it, BFS must be modified differently.
    //
    // Idea:
    // -> BFS naturally gives shortest distances from the source node.
    // -> Instead of storing a single parent for each node, we store *all* parents
    //    that appear on *any* shortest path.
    // -> During BFS:
    //      - If we discover a node `v` for the first time through `u`:
    //            dist[v] = dist[u] + 1
    //            parents[v] = { u }
    //            push v in queue
    //      - If we later find another shortest path to `v` of the same length:
    //            dist[v] remains unchanged
    //            add u to parents[v] (another shortest path found)
    // -> After BFS completes, parents[v] contains *all predecessors* on shortest paths.
    // -> Using parents[v], we can:
    //      - Reconstruct all shortest paths by backtracking.
    //      - Maintain properties that require considering all shortest paths
    //        (e.g. count the number of shortest paths, OR/AND over edge properties, etc.)
*/

// BFS storing all parents on shortest paths
void allShortestPaths() {
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
    vector<vector<int>> parents(n);

    queue<int> que;
    dist[src] = 0;
    que.push(src);

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (int v : graph[u]) {
            if (dist[v] == INT_MAX) {
                dist[v] = dist[u] + 1;
                parents[v].push_back(u);
                que.push(v);
            } else if (dist[v] == dist[u] + 1) {
                parents[v].push_back(u);
            }
        }
    }

    // Example: print distance and parents of each node
    for (int i = 0; i < n; i++) {
        cout << "Node " << i << " (dist = ";
        if (dist[i] == INT_MAX) cout << "INF"; 
        else cout << dist[i];
        cout << "): parents = { ";
        for (int p : parents[i]) cout << p << " ";
        cout << "}\n";
    }
}

/*
    ============================================================
    ==========  Counting Number of Shortest Paths  =============
    ============================================================

    // Another common modification:
    // Counting the number of distinct shortest paths from source to every node.
    //
    // -> Maintain an array count[] alongside dist[].
    // -> Initialization:
    //        count[src] = 1
    // -> During BFS:
    //        - If v is discovered for first time from u:
    //              dist[v] = dist[u] + 1
    //              count[v] = count[u]
    //        - If v already discovered at same shortest distance:
    //              count[v] += count[u]
    // -> At the end, count[v] gives number of distinct shortest paths src → v
*/

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

    for (int i = 0; i < n; i++) {
        cout << "Node " << i << " shortest paths count = " << count[i] << "\n";
    }
}

/*
    ============================================================
    ==========  Reconstructing All Shortest Paths  =============
    ============================================================

    // Using the `parents[]` structure from allShortestPaths(),
    // we can explicitly reconstruct and print all shortest paths
    // from a source node to a given destination node.
    //
    // Approach:
    // -> Start DFS/Backtracking from destination node.
    // -> Recursively walk backwards using parents[] until reaching src.
    // -> Collect nodes along the path, then reverse and print.
*/

void dfsReconstruct(int u, int src, vector<vector<int>>& parents, vector<int>& path) {
    if (u == src) {
        // Reached source, print current path
        vector<int> fullPath = path;
        reverse(fullPath.begin(), fullPath.end());
        cout << "Path: ";
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

void printAllShortestPathsToDst() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int src, dst;
    cin >> src >> dst;

    vector<int> dist(n, INT_MAX);
    vector<vector<int>> parents(n);

    queue<int> que;
    dist[src] = 0;
    que.push(src);

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int v : graph[u]) {
            if (dist[v] == INT_MAX) {
                dist[v] = dist[u] + 1;
                parents[v].push_back(u);
                que.push(v);
            } else if (dist[v] == dist[u] + 1) {
                parents[v].push_back(u);
            }
        }
    }

    if (dist[dst] == INT_MAX) {
        cout << "No path exists from " << src << " to " << dst << "\n";
        return;
    }

    vector<int> path;
    path.push_back(dst);
    dfsReconstruct(dst, src, parents, path);
}

/*
    ============================================================
    ==========  Maximizing/Minimizing Property  ================
    ============================================================

    // Another algorithmic idea:
    // Maximizing (or minimizing) some property across all shortest paths
    // from src to dst in an unweighted graph.
    //
    // Example: "happiness" value at each node. 
    // Task: Among all shortest paths src → dst, find the one that maximizes
    // the maximum happiness of any node along the path.
    //
    // Idea:
    // -> Perform BFS to compute shortest distances.
    // -> Maintain dp[v] = best achievable property (e.g. maximum happiness)
    //    along any shortest path from src to v.
    // -> Update rule:
    //      - If discovering v for first time from x:
    //            dist[v] = dist[x] + 1
    //            dp[v] = max(happy[v], dp[x])
    //      - If another shortest path to v found:
    //            dp[v] = max(dp[v], dp[x])
    // -> At the end, dp[dst] contains the optimal property value.
*/

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

