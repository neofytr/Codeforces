#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    int u, v;
    vector<vector<int>> graph(n + 1);
    while (m--) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<bool> vis(n + 1, false);
    vector<int> parent(n + 1);
    vector<int> dist(n + 1, INT_MAX); // no need to create a distance array everytime as
    // we are dependent upon visited to find visited nodes and we change distance to nodes anyway everytime

    for (int node = 1; node <= n; node++)
        parent[node] = node;
    for (int node = 1; node <= n; node++) {
        if (!vis[node]) {
            queue<int> que; // node

            int src = node;
            vis[src] = true;
            dist[src] = 0;
            que.push(src);
            while (!que.empty()) {
                int x = que.front();
                que.pop();
                for (int v : graph[x]) {
                    if (!vis[v]) {
                        vis[v] = true;
                        dist[v] = dist[x] + 1;
                        parent[v] = x;
                        que.push(v);
                    } else if (v != parent[x]) {
                        // got a node that has already been visited but isn't the parent of x
                        // thus, we have a cycle
                        // the edge v - x creates a cycle
                        // nodes v and x can be at the same depth, or, v can be at depth[x] + 1
                        if (dist[x] == dist[v]) {
                            // they both have a common node at the same height
                            int a = x;
                            int b = v;
                            int depth = 1;
                            vector<int> pathA, pathB;
                            while (a != b) {
                                depth++;
                                pathA.push_back(a);
                                pathB.push_back(b);
                                a = parent[a];
                                b = parent[b];
                            }
                            pathA.push_back(a);
                            reverse(pathB.begin(), pathB.end());
                            pathB.push_back(x);

                            cout << 2 * depth << endl;
                            for (int k : pathA)
                                cout << k << " ";
                            for (int k : pathB)
                                cout << k << " ";
                            cout << endl;
                            return EXIT_SUCCESS;
                        } else if (dist[v] == dist[x] + 1) { // while processing the next depth, all nodes may not be processed, so, the previously processed ones can have one more depth
                            int a = parent[v];
                            int b = x;

                            int depth = 1;
                            vector<int> pathA, pathB;
                            pathA.push_back(v);
                            while (a != b) {
                                depth++;
                                pathA.push_back(a);
                                pathB.push_back(b);
                                a = parent[a];
                                b = parent[b];
                            }
                            pathA.push_back(a);
                            reverse(pathB.begin(), pathB.end());
                            pathB.push_back(v);

                            cout << 2 * depth + 1 << endl;
                            for (int k : pathA)
                                cout << k << " ";
                            for (int k : pathB)
                                cout << k << " ";
                            cout << endl;
                            return EXIT_SUCCESS;
                        }
                    }
                }
            }
        }
    }

    cout << "IMPOSSIBLE\n";
    return EXIT_SUCCESS;
}