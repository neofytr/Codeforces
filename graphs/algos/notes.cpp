#include <bits/stdc++.h>
#include <vector>
using namespace std;

void dfs(int x, vector<bool> &vis, vector<vector<int>> &graph) {
    vis[x] = true;

    for (int v : graph[x]) {
        if (!vis[v]) {
            dfs(v, vis, graph);
        }
    }
}

void dfsInfo() {
    // dfs is a straightforward graph traversal technique
    // the algo begins at a starting node, and proceeds to all other nodes that are
    // reachable from the starting node using the edges of the graph

    // dfs always follows a single path in the graph as long as it finds new nodes
    // after this, it returns the previous nodes and begins to explore other parts of the graph
    // the algo keeps track of visited nodes, so that it processes each node only once

    int n, m;
    cin >> n >> n;

    // 0-indexed nodes, undirected, unweighted graph
    vector<vector<int>> graph(n);
    int u, v;
    while (m--) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(v);
    }

    // dfs can be conveniently implemented using recursion
    // the following function dfs begins depth-first search at a given node

    int start;
    cin >> start;

    // the function assumes that the graph is stored as an adjacency list
    // and also maintains an array

    vector<bool> vis(n, false);

    // that keeps track of the visited nodes
    // initially, each array value is false, and when the search arrives at a node s, the value of
    // vis[s] becomes true

    dfs(start, vis, graph);

    // the time-complexity of dfs is O(n + m) becasuse the algorithm processes each edge and each node
    // only once

    return;
}

void bfsInfo() {
    // bfs visits the nodes of a graph in increasing order of their distance from the starting node
    // thus, we can calculate the distance from the starting node to all other nodes using bfs

    // bfs goes through the nodes one level after another
    // first, the search explores the nodes whose distance from the starting node is 1, then the nodes
    // whose distance is 2, and so on
    // this continues untill all the nodes are visited

    // a typical bfs implementation is based on a queue that contains nodes
    // at each step, the next node in the queue will be processed

    int n, m;
    cin >> n >> n;

    // 0-indexed nodes, undirected, unweighted graph
    vector<vector<int>> graph(n);
    int u, v;
    while (m--) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(v);
    }

    queue<int> que;
    vector<bool> vis(n, false);
    vector<int> dist(n, INT_MAX);

    // the queue contains nodes to be processed in increasing order of their distance
    // new nodes are always added to the end of the queue, and the node at the beginning of the queue is the next node to be processed
    // the array vis indicates which nodes the search has already visited
    // and the array distance will contain the distances from the starting node to all nodes of the graph

    int start;
    cin >> start;

    // if we do this way, we don't really need a visited array
    // since bfs visits level by level, the first time we visit a node, it will be through the
    // minimum number of edges and thus through the shortest path
    // so, once it's distance is updated from INT_MAX to that distance and pushed into the queue, the node can never be
    // pushed into the queue again if it's encountered later
    que.push(start);
    dist[start] = 0;
    while (!que.empty()) {
        int x = que.front();
        que.pop();

        for (int v : graph[x]) {
            if (dist[x] + 1 < dist[v]) {
                dist[v] = dist[x] + 1;
                que.push(v);
            }
        }
    }

    // the tc of bfs is O(n + m)
    return;
}

int main() {
    // dfs is a simple way to visit all nodes that can be reached from a starting node, and bfs
    // visits the nodes in increasing order of their distance from the starting node

    // The bellman-ford algorithm is a simple algorithm that finds shortest paths from a starting node
    // to all other nodes. Dijkstra's algorithm is a more efficient algorithm which requires that
    // all edge weights are non-negative. The Floyd-Warshall algorithm determines shortest paths
    // between all node pairs of a graph.

    // a graph consists of nodes that are connected with edges
    // a path leads from a node to another node through the edges of the graph
    // a simple path is a one that does not repeat any edges/nodes
    // the length of a path is the number of edges in it
    // a cycle is a path where the first and the last node is the same
    // a graph is connected if there is a path between any two nodes
    // the connected parts of a graph are called it's components
    // a tree is a connected graph that does that contain any cycles

    // a connected graph of n nodes has atleast n - 1 edges

    // A graph G is a tree iff
    // 1. G is acyclic and connected
    // 2. G is connected and has exactly n - 1 edges
    // 3. G is acyclic and adding any edge would introduce a cycle
    // 4. G is connected and removing any edge would disconnect it
    // 5. There exists exactly one simple path between any two vertices
    // 6. G has no cycles and has the maximum possible number of edges without forming a cycle
    // 7. G is connected and its edges are all bridges (removing any edge increases components)

    // in a directed graph, the edges can be traversed in only one direction
    // in a weighted graph, each edge is assigned a weight
    // two nodes are adjacent if there is an edge between them
    // the degree of a node is the number of nodes adjacent to it

    // the sum of degree of all nodes in the graph is two times the number of edges in the graph since each edge of the graph increases
    // the degree of exactly two nodes by 1

    // a graph is regular if the degree of all nodes is exactly d
    // a graph is complete if the degree of all nodes is  n - 1, where n is the number of nodes in the graph
    // a complete graph of n vertices has n * (n - 1) / 2 edges

    // in a directed graph, the indegree of a node is the number of incoming edges to the node, and
    // the outdegree is the number of outgoing edges from the node

    // a graph is bipartite if it's possible to color all of its vertices in such a manner that if there
    // is an edge between vertices u and v, then they both have a different color

    // a graph is bipartite iff it has no cycle that contains an odd number of nodes

    // both bfs and dfs are fundamental graph algoithms that are given a starting node in the graph, and
    // they visit all nodes that can reached from the starting node
    // the difference in the algorithms is the order in which they visit the nodes

    // using the graph traversal algorithms, we can have the following applications

    // 1. Connectivity Check
    // a graph is connected if there is a path between any two nodes in the graph
    // thus, we can check if a graph is connected by starting at an arbitrary node and
    // finding out if we can reach all the other nodes
    // in a similar way, we can find all the connected components of a graph by iterating through
    // the nodes and always starting a new dfs if the current node does not belong to any component yet

    int n, m;
    cin >> n >> n;

    // 0-indexed nodes, undirected, unweighted graph
    vector<vector<int>> graph(n);
    int u, v;
    while (m--) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(v);
    }

    vector<bool> vis(n, false);
    int comp = 0;
    for (int node = 0; node < n; node++) {
        if (!vis[node]) {
            comp++;
            dfs(node, vis, graph);
        }
    }

    // 2. Cycle Detection
    // a graph contains a cycle if during a graph traversal, we find a node whose neighbour
    // (other than the previous node in the current path, i.e, it's parent) has already been visited

    /*
    Another  way  to  determine  if  a  graph  contains  a  cycle  is  to  simply  calculate  the
    number  of  nodes  and  edges  in  every  component.  If  a  component  contains c nodes
    and  no  cycle,  it  must  contain  exactly c − 1 edges  (so  it  has  to  be  a  tree).  If  there  are
    c or  more  edges,  the  component  surely  contains  a  cycle.
    */

    // 3. Bipartiteness Check
    // a graph is
}