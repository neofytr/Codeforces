#include <bits/stdc++.h>
#include <climits>
#include <queue>
#include <vector>
using namespace std;

// Problem: easy
// URL: https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph-having-unit-distance/1
// Difficulty: shortestPathInUndirectedGraph
// Tags:
// Strategy:

class Solution {
  public:
    vector<int> shortestPath(vector<vector<int>> &adj, int src) {
        int n = (int)adj.size();
        vector<int> dist(n, -1);
        vector<bool> vis(n, false);
        queue<int> que;

        dist[src] = 0;
        vis[src] = true;
        que.push(src);

        while (!que.empty()) {
            int size = (int)que.size();
            while (size--) {
                // all are in the same depth
                int node = que.front();
                que.pop();
                for (int v : adj[node]) {
                    if (!vis[v]) {
                        vis[v] = true;
                        dist[v] = dist[node] + 1;
                        que.push(v);
                    }
                }
            }
        }

        return dist;
    }
};