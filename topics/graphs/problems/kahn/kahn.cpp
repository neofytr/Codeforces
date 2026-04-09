#include <bits/stdc++.h>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // directed graph
    // 1-indexed nodes
    vector<vector<int>> graph(n + 1, vector<int>());
    vector<int> inDegree(n + 1, 0);
    int a, b;
    while (m--) {
        cin >> a >> b; // a -> b
        graph[a].push_back(b);
        inDegree[b]++; // compute indegree of each node
    }

    queue<int> que;
    for (int node = 1; node <= n; node++) {
        // add all nodes with indegree 0 to the queue
        if (!inDegree[node]) {
            que.push(node);
        }
    }

    vector<int> topoSort;
    while (!que.empty()) {
        // while queue is not empty
        int x = que.front(); // remove a node from the queue
        que.pop();

        topoSort.push_back(x); // push it to the order
        for (int v : graph[x]) {
            // for each neighbour v of x
            inDegree[v]--; // decrease indegree of v by 1
            if (!inDegree[v]) {
                // if the inDegree of v is now 0, add it to the queue
                que.push(v);
            }
        }
    }

    // if all the n nodes are in the result, we have valid topological order
    // else, the graph has a cycle and a valid topological order is not possible
    if (topoSort.size() == n) {
        for (int node : topoSort) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "the given graph has a cycle\nno valid topological ordering possible\n";
    }

    return EXIT_SUCCESS;
}