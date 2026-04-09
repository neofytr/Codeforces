#include <bits/stdc++.h>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;

class UndirectedGraph {
  private:
    vector<vector<int>> adjList;
    int nodes;
    enum Color { UNCOLORED = -1, RED = 1, BLUE = 2 };

    bool startColoringDFS(int node, vector<Color> &color) { // the first call to this function should assign a color to node
        for (int v : adjList[node]) {
            if (color[v] == UNCOLORED) {
                color[v] = (color[node] == RED) ? BLUE : RED;
                if (!startColoringDFS(v, color))
                    return false;
            } else if (color[v] == color[node]) {
                return false;
            } // else, the node v has a color that is not the parent's color; we don't care about this case
        }

        return true;
    }

    bool startColoringBFS(int node, vector<Color> &color) {
        queue<int> que;
        color[node] = RED; // arbitrary assignment
        que.push(node);

        while (!que.empty()) {
            int currNode = que.front();
            Color currColor = color[currNode];
            que.pop();

            for (int v : adjList[currNode]) {
                if (color[v] == -1) {
                    color[v] = (currColor == RED) ? BLUE : RED; // assign a color different from the current node
                    que.push(v);
                } else if (color[v] == currColor) {
                    // the node already has a color which is the same as the current node
                    // this means the graph isnt' bipartite
                    return false;
                } // else, if the node has a color which is diff from the current node, this means the node was
                  // already visited before and we don't need to bother with it now
            }
        }

        return true;
    }

  public:
    UndirectedGraph(int nodes, int edges) {
        adjList.resize(nodes);
        this->nodes = nodes;

        // undirected graph
        // 0-indexed nodes (0 to n - 1)
        int a, b;
        while (edges--) {
            cin >> a >> b;
            adjList[a].push_back(b);
            adjList[b].push_back(a);
        }
    }
    bool isBipartiteBFS() {
        // a graph is said to be bipartite if it can be colored with just two colors such that
        // no two adjacent nodes have the same color

        vector<Color> color(nodes, UNCOLORED); // -1 is uncolored
        // iterate over all the distinct connected components
        for (int node = 0; node < nodes; node++) {
            if (color[node] == UNCOLORED) { // uncolored means not yet visited too
                if (!startColoringBFS(node, color))
                    return false;
            }
        }

        return true;
    }

    bool isBipartiteDFS() {
        vector<Color> color(nodes, UNCOLORED); // -1 is uncolored
        // iterate over all the distinct connected components
        for (int node = 0; node < nodes; node++) {
            if (color[node] == UNCOLORED) { // uncolored means not yet visited too
                color[node] = RED;          // arbitrary
                if (!startColoringDFS(node, color))
                    return false;
            }
        }

        return true;
    }
};

int main() {
    int n, m; // vertices, edges
    cin >> n >> m;

    UndirectedGraph graph(n, m);

    if (graph.isBipartiteDFS()) {
        cout << "The graph is bipartite." << endl;
    } else {
        cout << "The graph is not bipartite." << endl;
    }

    return EXIT_SUCCESS;
}