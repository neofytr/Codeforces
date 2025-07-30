#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

// Problem: shortestPathInDAG
// URL: https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph/1
// Difficulty: easy
// Tags:
// Strategy:

class Solution {
  private:
    void dfs(int node, vector<bool> &vis, stack<int> &st, vector<vector<pair<int, int>>> &graph) {
        vis[node] = true;
        for (auto elt : graph[node]) {
            int v = elt.first;
            if (!vis[v]) {
                dfs(v, vis, st, graph);
            }
        }
        st.push(node);
        return;
    }

  public:
    vector<int> shortestPath(int V, int E, vector<vector<int>> &edges) {
        vector<int> dist(V, INT_MAX);
        int source = 0;
        vector<vector<pair<int, int>>> graph(V);
        for (int edge = 0; edge < E; edge++) {
            int a = edges[edge][0];
            int b = edges[edge][1];
            int w = edges[edge][2];
            graph[a].push_back({b, w});
        }

        // do a topo sort
        stack<int> st;
        vector<bool> vis(V, false);
        for (int node = 0; node < V; node++) {
            if (!vis[node])
                dfs(node, vis, st, graph);
        }

        bool found = false;
        while (!st.empty()) {
            int node = st.top();
            st.pop();
            if (!found && node != source) {
                dist[node] = -1;
                continue;
            }
            if (node == source) {
                found = true;
                dist[node] = 0;
            }

            for (auto elt : graph[node]) {
                int v = elt.first;
                int w = elt.second;
                dist[v] = min(dist[v], dist[node] + w);
            }
        }

        return dist;
    }
};
