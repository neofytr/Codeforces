#include <bits/stdc++.h>
#include <climits>
#include <functional>
#include <queue>
#include <vector>
using namespace std;

void bellmanFord() {
    // this algo finds shortest paths from a starting node to all nodes of a graph

    // the algo can process all kinds of graphs, provided that the graph does not contain
    // a cycle with a total negative length (called a negative cycle)
    // if the graph contains a negative cycle, the algorithm can detect this

    // the algo keeps track of distances from the starting node to all nodes of the graph
    // initially, the distance to the starting node is 0 and the distances to any other node is infinite
    // the algo reduces the distances by finding edges that shorten the paths until it is not possible
    // to reduce any distance

    int n, m;
    cin >> n >> m;

    // 0-indexed nodes, undirected, weighted graph
    vector<tuple<int, int, int>> edges;
    int u, v, w;
    while (m--) {
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    int start;
    cin >> start;

    // the below algo determines the shortest path from start to all other nodes
    // the code assumes that the graph is stored as an edge list that contains tuples of the form (a, b, w)
    // meaning there is an edge from a to b with weight w

    // the algo consists of n - 1 rounds, and on each round the algorithm goes through all edges
    // of the graph and attempts to reduce the distances
    // the algo constructs an array dist that will contain the distances from node x to all nodes

    vector<int> parent(n);
    for (int node = 0; node < n; node++)
        parent[node] = node;
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;

    for (int iter = 1; iter < n; iter++) {
        for (auto &[u, v, w] : edges) {
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    /*
    The  time  complexity  of  the  algorithm  is O(nm),  because  the  algorithm  consists  of
    n − 1 rounds  and  iterates  through  all m edges  during  a  round.  If  there  are  no  negative
    cycles  in  the  graph (reachable from x),  all  distances  are  final  after n − 1 rounds,  because  each  shortest
    path  can  contain  at  most n − 1 edges.
    */

    // shortest path length in a weighted graph is defined only when there is no negative cycle in the
    // graph reachable from x

    // to see if there is a negative cycle in the graph, iterate through the edges one more time
    // if we find a distance reduction again, we have a negative cycle in the graph
    for (auto &[u, v, w] : edges) {
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            // the graph contains a negative cycle
            return;
        }
    }

    int dst;
    cin >> dst;
    if (dist[dst] == INT_MAX) // there is no path from start to dst
        return;

    // we construct a path from start to dst;
    vector<int> path;
    while (dst != parent[dst]) {
        path.push_back(dst);
        dst = parent[dst];
    }
    path.push_back(dst);

    reverse(path.begin(), path.end()); // this is a shortest path from start to dst

    return;
}

void floydWarshall() {
    int n, m;
    cin >> n >> m;

    // 0-indexed nodes, undirected, weighted graph
    vector<vector<pair<int, int>>> graph(n);
    int u, v, w;
    while (m--) {
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    // this algo provides an alternative way to approach the problem of finding shortest paths
    // it finds the shortest paths between all node pairs of the graph in a single run

    // the algo maintains a matrix that contains distances between the nodes
    // the initial matrix is constructed based on the adjacency list of the graph
    // then, the algo consists of consecutive rounds, and on each round, it selects a new node that
    // can act as an intermediate node in paths from now on, and reduces distances using this node

    // this algo finds the shortest path only when there are no negative cycles in the graph
    // it can also detect if there is a negative cycle

    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    vector<vector<int>> next(n, vector<int>(n, -1));
    for (int node = 0; node < n; node++) {
        dist[node][node] = 0;
        next[node][node] = node;
    }
    for (int node = 0; node < n; node++) {
        for (auto &[v, w] : graph[node]) {
            dist[node][v] = w;
            next[node][v] = v;
        }
    }

    for (int via = 0; via < n; via++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                int uvia = dist[u][via];
                int viav = dist[via][v];
                int uv = dist[u][v];
                if (uvia != INT_MAX && viav != INT_MAX && uvia + viav < uv) {
                    next[u][v] = next[u][via];
                    dist[u][v] = uvia + viav;
                }
            }
        }
    }

    // there is a negative cycle in the graph if any dist[node][node] < 0 now
    for (int node = 0; node < n; node++) {
        if (dist[node][node] < 0)
            return; // there is a negative cycle in the graph
    }

    // the algorithm runs in O(n^3) time

    int src, dst;
    cin >> src >> dst;
    if (dist[src][dst] == INT_MAX)
        return; // no path from src to dst

    vector<int> path = {src};
    int r = next[src][dst];
    while (r != dst) {
        path.push_back(r);
        r = next[r][dst];
    }
    path.push_back(dst);
    return;
}

void dijkstra() {
    // this algo finds shortest paths from the starting node to all nodes of the graph
    // the benefit of this is that its more efficient that bellman-ford and can be used for
    // processing large graphs
    // however, the algo requires that there are no negative weight edges in the graph

    // dijkstras algo maintains distances to the nodes and reduces them during the search
    // at each step, this algo selects a node that has not been processed yet and whose distance is as small as possible
    // then the algo goes through all edges that start at the node and reduces the distances using them
    // this algo is efficient, because it only processes each edge in the graph once, using the fact that
    // there are no negative edges

    // an efficient implementation of the algo requires that we can efficiently find the min-distance node
    // that has not been processed

    // an appropriate data structure for this is a priority queue that contains the remaining nodes
    // ordered by their distances
    // using a pq, the next node to be processed can be retrieved in logarithmic time

    // the following implementation calculates min distances from a node x to all other nodes in the graph
    // the graph is stored as an adjacency list

    int n, m;
    cin >> n >> m;

    // 0-indexed nodes, undirected, weighted graph
    vector<vector<pair<int, int>>> graph(n);
    int u, v, w;
    while (m--) {
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // (dist, node)
    vector<int> dist(n, INT_MAX);
    vector<bool> vis(n, false);
    vector<int> parent(n);
    for (int node = 0; node < n; node++)
        parent[node] = node;

    // while there may be several instances of a node in the pq, only the instance with the minimum distance
    // will be processed

    int src;
    cin >> src;

    // the maintained invariant is that once a node is popped from the pq, it's minimum distance has been finalized
    // the visited array is not needed, since a node will be pushed into the queue again only when a shorter path to it
    // is found
    dist[src] = 0;
    pq.push({dist[src], src});
    while (!pq.empty()) {
        auto [d, x] = pq.top();
        pq.pop();

        for (auto &[v, w] : graph[x]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                parent[v] = x;
                pq.push({dist[v], v});
            }
        }
    }

    /*

    The  time  complexity  of  the  above  implementation  is O(n + m log m),  because
    the  algorithm  goes  through  all  nodes  of  the  graph  and  adds  for  each  edge  at  most
    one  distance  to  the  priority  queue.

    */

    int dst;
    cin >> dst;
    if (dist[dst] == INT_MAX) // there is no path from start to dst
        return;

    // we construct a path from start to dst;
    vector<int> path;
    while (dst != parent[dst]) {
        path.push_back(dst);
        dst = parent[dst];
    }
    path.push_back(dst);

    reverse(path.begin(), path.end()); // this is a shortest path from start to dsts
    return;
}

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
    cin >> n >> m;

    // 0-indexed nodes, undirected, unweighted graph
    vector<vector<int>> graph(n);
    int u, v;
    while (m--) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // dfs can be conveniently implemented using recursion
    // the following function dfs begins depth-first search at a given node

    int start;
    cin >> start;

    // the function assumes that the graph is stored as an adjacency list
    // and also maintains a dist array

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
    cin >> n >> m;

    // 0-indexed nodes, undirected, unweighted graph
    vector<vector<int>> graph(n);
    int u, v;
    while (m--) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
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

    vector<int> parent(n);
    for (int node = 0; node < n; node++) {
        parent[node] = node;
    }

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
                parent[v] = x;
                dist[v] = dist[x] + 1;
                que.push(v);
            }
        }
    }

    int dst;
    cin >> dst;
    if (dist[dst] == INT_MAX) // there is no path from start to dst
        return;

    // we construct a path from start to dst;
    vector<int> path;
    while (dst != parent[dst]) {
        path.push_back(dst);
        dst = parent[dst];
    }
    path.push_back(dst);

    reverse(path.begin(), path.end()); // this is a shortest path from start to dst

    // the tc of bfs is O(n + m)
    return;
}

// this is also a way to detect cycles in a directed graph
bool dfsTopo(int node, vector<int> &state, vector<int> &topo, vector<vector<int>> &graph) {
    state[node] = 1;

    for (int v : graph[node]) {
        if (state[v] == 1 || (!state[v] && !dfsTopo(v, state, topo, graph)))
            return false; // we have a cycle
    }

    state[node] = 2;
    topo.push_back(node);
    return true;
}

// Multi-source BFS — Shortest distance from any of multiple starting nodes
// Why it works:
// BFS explores in "layers". If multiple sources start at distance 0,
// they expand simultaneously, so the first time we visit a node is via
// the shortest path from any source.
// Time: O(V+E)
void multi_source_bfs(int n, vector<vector<int>> &graph, vector<int> &sources) {
    vector<int> dist(n, INT_MAX);
    queue<int> q;

    for (int s : sources) {
        dist[s] = 0;
        q.push(s);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : graph[u]) {
            if (dist[v] == INT_MAX) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    for (int i = 0; i < n; i++)
        cout << "Dist from nearest source to " << i << " = " << dist[i] << "\n";
}

// Prim's Algorithm — Minimum Spanning Tree (Proof idea: MST grows greedily)
// Why it works:
// 1. Start from any node, grow the tree by always choosing the smallest weight edge
//    that connects a visited node to an unvisited one.
// 2. This works by the cut property of MST: the smallest crossing edge is always in some MST.
// Time: O((V+E) log V) with priority queue
void prims(int n, vector<vector<pair<int, int>>> &graph) {
    vector<int> visited(n, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // {weight, node}
    int total = 0;

    pq.push({0, 0}); // start from node 0

    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();
        if (visited[u])
            continue;
        visited[u] = 1;
        total += w; // add edge weight to MST

        for (auto [v, wt] : graph[u]) {
            if (!visited[v])
                pq.push({wt, v});
        }
    }
    cout << "MST weight = " << total << "\n";
}

void topoSort() {
    // a topological sort is an ordering of the nodes of a directed graph such that if there is a
    // path from node u to node v, then u appears before v in the ordering

    // a topological sort of a directed graph exists iff the graph is acyclic
    // dfs can be used to both check if a directed graph contains a cycle, and if it does not, to
    // construct a topological sort

    // the idea is to go through the nodes of the graph and always begin a dfs at the current node
    // if it has not been processed yet
    // during the searches, the nodes have three possible states ->
    // 1. state 0 -> the node has not been processed
    // 2. state 1 -> the node is under processing
    // 3. state 2 -> the node has been processed

    // initially, the state of each node is 0
    // when a search reaches a node for the first time, it's state becomes 1
    // finally, after all the edges from the node have been processed, it's state becomes 2

    // if the graph contains a cycle, we will discover this during the search, because sooner or later
    // we will arrive at a node whose state is 1. In this case, it is not possible to construct a topological
    // sort

    // if the graph does not contain a cycle, we can construct a topo sort by adding each node to a list
    // when its state becomes 2
    // finally, we reverse the list to get a topo sort for the graph

    // a topo sort for a DAG is not unique; there can be several topo sorts for a graph

    int n, m;
    cin >> n >> m;

    // 0-indexed nodes, directed graph
    vector<vector<int>> graph(n);
    vector<int> indegree(n, 0);
    int u, v;
    while (m--) {
        cin >> u >> v;
        graph[u].push_back(v);
        indegree[v]++;
    }

    int src = 0; // arbitrary
    vector<int> topo;
    vector<int> state(n, 0);
    if (!dfsTopo(src, state, topo, graph))
        return; // graph has a cycle
    reverse(topo.begin(), topo.end());

    // Kahn's Algorithm
    vector<int> kahnTopo;
    queue<int> que;
    for (int node = 0; node < n; node++)
        if (!indegree[node]) {
            que.push(node);
        }

    // we don't need to maintain a visited array since a node's indegree will become 0 exactly once
    // and at the at time, the node will be pushed into the queue
    while (!que.empty()) {
        int x = que.front();
        que.pop();

        kahnTopo.push_back(x);
        for (int v : graph[x]) {
            if (!(--indegree[v])) // remove the edge x -> v
                que.push(v);
        }
    }

    if (kahnTopo.size() != n)
        return; // the graph has a cycle; no topo sort exists
    return;
}

// assumes undirected graph with 0-indexed nodes
class disjointSetUnion {
    // a union-find structure can be used to process graph related problems only for undirected graphs
    /*
        A union-find structure maintains a collection of connected sets
        The sets are disjoint, so no element belongs to more than one set
        Two O(logn) time operations are supported -> the unite operation joins two sets, and the
        find operation finds the representative of the set that contains a given element

        In a union-find structure, one element in each set is the representative of the set, and
        there is a path from any other element of the set to the representative

        We can find the representative of any element by following the path that begins at the element.
        Two elements belong to the same set exactly when their representatives are the same.

        To join two sets, the representative of one set if connected to the representative of the other set
        The efficiency of the union-find structure depends on how the sets are joined
        It turns out that we can follow a simple strategy -> always connect the representative of the smaller set
        to the representative of the larget set (or if the sets are equal, we make an arbitrary size)
        Using this strategy, the length of any path from an element to it's representative will be atmost log(n), where n
        is the number of nodes in the entire graph, so we can find the representative of any element efficiently
        by following the corresponding path

        This is easily provable
        Suppose we want to join two sets A and B with size(A) >= size(B)
        The size of the final set C will be size(C) = size(A) + size(B) >= 2 * size(B)
        Also, since we connect the root of set B to root of set A, the longest path in set B, will increase
        by atmost one
        So, when we connect two sets, the size of the final set is atleast double of the smaller set and the
        path length of the longest path increases by atmost 1

        So, if in a graph, we have n nodes, which are all initially in their own sets, and we start connecting them,
        It will take atmost log(n) union operations to connect them, and since longest path increases by atmost 1 in each
        , finally, the longest path will be atmost of length log(n)
    */

    /*
        The union-find structure can be conveniently implemented using arrays
        In the following implementation, the array parent indicates for each element, the next element in the path,
        or the element itself if it's a set representative(root)
        The array size, for a root element r, represents the size of the component/set rooted at r through size[r]

        Initially, each element belongs to a separate set
        The function getRoot(x) returns the representative for an element x
        The representative can be found by following the path that begins at x

        The same function can check whether two elements belong to the same set by checking if the
        two elements have the same root

        The function join(x, y) joins the set containing element x and y if they are in different sets and
        does nothing if they are not
        The function first finds the representatives of the sets and then connects the smaller set to the larger set

        The time complexity of the function getRoot is O(logn) assuming that the worst-case path length of any path is logn
        In this case, the functions isConnected and join also work in O(logn) time
        The function join makes sure that the length of each path is atmost log(n) by connecting the smaller set to the larget set

        We can also do path compression in the getRoot function
        This way, each element in the path will point directly to it's representative (root) after the operation
        It can be shown that by using path compression, the union-find operations work in amortized O(alpha(n)) time,
        where alpha(n) is the inverse Ackermann function which grows very slowly (its almost a constant)
        However, path compression cannot be used in some applications (where the information about parents of a node in path
        is important) of the union-find structure, such as in the dynamic-connectivity algorithm
    */

  private:
    int numNodes;
    int numComp;
    vector<int> parent;
    vector<int> size;

    inline bool checkNode(int x) { return x < numNodes && x >= 0; }
    inline bool checkNodes(int x, int y) { return checkNode(x) && checkNode(y); }
    int getRoot(int x) {
        int y = x;
        while (x != parent[x])
            x = parent[x];

        // path compression
        int temp;
        while (y != parent[y]) {
            temp = parent[y]; // store the parent of the current node
            parent[y] = x;    // make the root node parent of the current node
            y = temp;         // go to the stored parent node
        }
        return x;
    }
    inline int getSize(int x) { return size[getRoot(x)]; }

  public:
    disjointSetUnion(int numNodes) {
        this->numNodes = numNodes;
        parent.resize(numNodes);
        size.resize(numNodes);
        for (int node = 0; node < numNodes; node++) {
            parent[node] = node;
            size[node] = 1; // each node is in it's own connected component
        }
        numComp = numNodes;
        return;
    }

    bool join(int x, int y) { // joins node x and y via an edge if they are not already joined
        if (!checkNodes(x, y))
            return false;

        int rootX = getRoot(x);
        int rootY = getRoot(y);

        if (rootX == rootY) // already in the same component
            return true;

        // x and y are not in the same component
        // they will be after these operations
        // so decrease the component number by 1
        numComp--;
        int sizeX = getSize(x);
        int sizeY = getSize(y);

        if (sizeX > sizeY) {
            swap(sizeX, sizeY);
            swap(rootX, rootY);
        }

        // from here, sizeY >= sizeX always
        // attach X root to Y root
        parent[rootX] = rootY;
        size[rootY] += sizeX;

        return true;
    }

    int isConnected(int x, int y) {
        if (!checkNodes(x, y))
            return -1;

        return getRoot(x) == getRoot(y);
    }

    int componentSize(int x) { return checkNode(x) ? getSize(x) : -1; }
    int numComponents() { return numComp; }
};

void Kruskal() {
    /*
        This algorithm builds a minimum spanning tree by greedily adding edges to a graph
        that initally only contains the nodes of the original graph and no edges

        The algorithm goes through the edges of the original graph ordered by their weight, and
        always adds an edge to a new graph if the edge does not create a cycle

        The algorithm maintains the components of the new graph. Initially, each node of the graph
        belongs to a separate component. Always when an edge is added to the graph, two components are joined
        Finally, all nodes belong to the same component, and a minimum spanning tree has been found.

        The first step is to sort the edges in order of the edge weights
        Then, we go through the list and add each edge to the graph if it joins two separate components, since
        if two nodes belong to the same component, there is a path from one to another, so adding this edge would create a cycle

        We sort the edges by weight and then process the edges in increasing order of the weights
        The tree initially consists of all the nodes but no edges
        During each iteration, we add the edge in the tree if both nodes aren't already in the same component
        This is optimal since suppose that two nodes aren't in the same component and we find an edge connecting these nodes during the iteration
        This will be the minimum weighted edge that can connect the two components since we process the edges in increasing order of weights
        If we don't connect these components via this edge, later edges that connect these components will have their weigts >= this edge's weight,
        thus increasing the total weight of the tree
        Thus, this addition is optimial
    */

    int n, m;
    cin >> n >> m;

    set<tuple<int, int, int>> edges;
    vector<pair<int, int>> mst;
    disjointSetUnion dsu(n);
    int u, v, w;
    while (m--) {
        cin >> u >> v >> w;
        edges.insert({w, u, v});
    }

    int sum = 0;
    while (!edges.empty()) {
        auto [w, u, v] = *edges.begin();
        edges.erase(edges.begin());
        if (dsu.join(u, v)) {
            sum += w;
            mst.push_back({u, v});
        }
    }

    /*
        When implementing kruskal's algo, its convenient to use the edge list representation of the graph
        The first phase of the algo sorts the list representation in O(mlog(m)) time
        After this, the second phase of the algorithm buils the minimum spanning tree

        The loop goes through the edges in the list and always processes an edge (a, b) where a and b are two nodes
        The dsu.join function runs in amortized constant time (almost), so, the time complexity of this algo is
        O(mlog(m))
    */

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
    // a graph is bipartite if its node can be colored so that there are no adjacent nodes with the same color
    // its easy to check if a graph is bipartite using traversal algorithms
    // the idea is to pick two colors X and Y, color the starting node X, all its neighbours Y,
    // and all their neighbours X, and so on
    // if at some point of the search we notice that two adjacent nodes have the same color, this means
    // that the graph is not bipartite
    // otherwise, the graph is bipartite and one coloring has been found

    // in the general case it is difficult to find out if the nodes in a graph can be colored using k colors
    // so that no adjacent nodes have the same color
    // the problem is NP-hard already for k = 3

    /*

    Shortest Paths

    In an unweighted graph, the length of a path equals the number of its edges, and we can simply use
    bfs to find a shortest path

    In a weighted graph, the length of a path is the sum of weights of the edges in the path
    A negative cycle in a weighted graph is a cyclic path that has a negative length

    There are three algorithms we discuss
    1. Bellman-Ford
    2. Dijkstra's
    3. Floyd-Warshall

    */

    // directed graphs that do not contain a cycle are called DAGs
    // we can always construct a topological sort for the graph and then apply dynamic programming

    // using DP, we can efficiently answer many questions regarding paths in DAGs; for eg ->
    // 1. what is the shortest/longest path from node a to node b
    // 2. how many different paths are there from node a to node b
    // 3. what is the minimum/maximum number of edges in a path
    // 4. which nodes appear in every possible paths

    // note that many of the above problems are difficult to solve or not well-defined for general graphs

    // as an example, consider the problem of calculating the number of paths from node a to node b
    // let paths(x) denote the number of paths from node a to node x
    // as a base case paths(a) = 1
    // then, to calculate other values of paths(x), we can use the recursive formula
    // paths(x) = paths(s1) + ... + paths(sk)
    // where s1, ..., sk are all the nodes that have an edge s -> x
    // since the graph is acyclic, the value of paths can be calculated in the order of a topo sort

    /*

    For a DAG, if for calculating dp(x) for some node x, we need the values of all dp(s) such that
    there is an edge s -> x, we can process the nodes in a topo sort ordering since when we reach
    some node x in the ordering, it's guaranteed that we've processed all nodes s such that s -> x
    by the definition of a topo sort ordering.

    */

    /*

    Minimum Spanning Trees
    All the following information is for undirected connected graphs

    A spanning tree contains all nodes of a graph and some of it's edges so that there is a
    path between any two nodes
    Like trees in general, spanning trees are connected and acyclic
    The weight of a spanning tree is the sum of its edge weights

    A minimum spanning tree is a spanning tree whose weight is as small as possible
    In a similar way, a maximum spanning tree is a spanning tree whose weight is as large as possible
    Note that a graph may have several minimum and maximum spanning trees, so the trees are not unique

    It turns out that several greedy methods can be used to construct minimum/maximum spanning trees
    We see Kruskal's algorithm that processes the edges of the graph ordered by their weight
    We focus on finding the minimum spanning tree, but the same algorithm can also find the maximum spanning trees
    by processing the edges in reverse order

    We also see Prims algorithm and multi source bfs

    */
}