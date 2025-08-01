#include <bits/stdc++.h>
#include <cstdlib>
#include <ostream>
#include <queue>
#include <vector>
using namespace std;

// this function is called whenever we want to "process" an edge (u, v)
// in real problems, you might update some data, count things, etc.
void process_edge(int u, int v) {
    // process_edge u - v
    return;
}

// we define three states for each node:
// UNVISITED: the node has never been seen before
// VISITED: the node has been added to the queue but not processed yet
// PROCESSED: the node has been removed from the queue and all its neighbors have been checked
#define UNVISITED 0 // never seen before
#define VISITED 1   // pushed into the queue
#define PROCESSED 2 // popped from the queue

int main() {
    int n, m;
    cin >> n >> m;                // n = number of nodes, m = number of edges
    vector<vector<int>> graph(n); // adjacency list for the graph
    vector<int> parent(n);        // to keep track of bfs tree parent

    // initially, set parent of each node as itself
    for (int node = 0; node < n; node++) {
        parent[node] = node;
    }

    int start;
    cin >> start; // the starting node for bfs

    // read m edges and construct the graph
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // since the graph is undirected
    }

    queue<int> que;
    vector<int> state(n, UNVISITED); // initialize all nodes as unvisited

    // begin bfs from the start node
    que.push(start);
    state[start] = VISITED; // we have seen this node and put it in the queue

    while (!que.empty()) {
        int x = que.front();  // get the node at the front of the queue
        que.pop();            // remove it from the queue
        state[x] = PROCESSED; // we are now processing this node fully

        // explore all neighbors of x
        for (int v : graph[x]) {
            // if v has not been seen before, we mark it as seen (VISITED)
            // and add it to the queue for future processing
            if (state[v] == UNVISITED) {
                state[v] = VISITED;
                parent[v] = x; // we came to v from x
                que.push(v);
            }

            // process_edge(x, v); -> if you want to process x - v and v - x separately

            // even if v is already VISITED (in the queue), but not yet PROCESSED,
            // we still want to process the edge (x, v) once
            // this ensures that in undirected graphs, each edge is processed only once
            if (state[v] != PROCESSED) { // this helps in processing edges in the forward direction (from x to v)
                // no processing of the edge x - v happens again since the processing can now occur when
                // we remove v from the queue and scan all it's edges, but by that time x is marked PROCESSED, hence
                // the edge x - v won't be processed again
                process_edge(x, v);
            }
        }
    }

    // print one of the shortest paths from start to node
    // print -1 if there is no path
    for (int node = 0; node < n; node++) {
        if (state[node] == UNVISITED)
            cout << -1 << endl;
        else {
            stack<int> path;
            int x = node;
            while (parent[x] != x) {
                path.push(x);
                x = parent[x];
            }
            path.push(start);

            while (!path.empty()) {
                cout << path.top() << " ";
                path.pop();
            }
            cout << endl;
        }
    }

    return EXIT_SUCCESS;
}
