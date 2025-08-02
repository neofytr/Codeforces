#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

// Problem: shortestPathWeightedUndirectedGraph
// URL: https://www.geeksforgeeks.org/problems/shortest-path-in-weighted-undirected-graph/1
// Difficulty: medium
// Tags:
// Strategy:

class Solution {
  public:
    vector<int> shortestPath(int n, int m, vector<vector<int>> &edges) {
        int size = (int)edges.size();
        vector<int> path;
        vector<vector<pair<int, int>>> graph(n);
        for (int i = 0; i < size; i++) {
            int a = edges[i][0];
            int b = edges[i][1];
            int w = edges[i][2];
            a--, b--;
            graph[a].push_back({b, w});
            graph[b].push_back({a, w});
        }

        int src = 0;
        int end = n - 1;
        vector<int> parent(n);
        vector<int> dist(n, INT_MAX);
        set<pair<int, int>> heap;

        for (int node = 0; node < n; node++) {
            parent[node] = node;
        }
        dist[src] = 0;
        heap.insert({dist[src], src});

        while (!heap.empty()) {
            auto elt = *(heap.begin());
            heap.erase(elt);
            int node = elt.second;
            for (auto e : graph[node]) {
                int v = e.first;
                int w = e.second; 
                if (dist[node] + w < dist[v]) {
                    heap.erase({dist[v], v});
                    dist[v] = dist[node] + w;
                    parent[v] = node;
                    heap.insert({dist[v], v});
                }
            }
        }

        if (dist[end] == INT_MAX)
            return {-1};

        for (int v = end; v != parent[v]; v = parent[v]) {
            path.push_back(v);
        }
        path.push_back(src);
        path.push_back(dist[end]);
        reverse(path.begin(), path.end());
        for (int index = 1; index < path.size(); index++) {
            path[index]++;
        }

        return path;
    }
};