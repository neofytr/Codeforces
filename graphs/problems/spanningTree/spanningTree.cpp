#include <bits/stdc++.h>
#include <queue>
#include <vector>
using namespace std;

// Problem: spanningTree
// URL: https://www.geeksforgeeks.org/problems/minimum-spanning-tree/1
// Difficulty: medium
// Tags:
// Strategy:

class Solution {
  public:
    int spanningTree(int n, vector<vector<int>> &edges) {
        int sum = 0;
        vector<vector<pair<int, int>>> graph(n);
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        vector<bool> vis(n, false);

        pq.push({0, 0}); // {weight, node}

        while (!pq.empty()) {
            auto [weight, node] = pq.top();
            pq.pop();

            if (vis[node])
                continue;

            vis[node] = true;
            sum += weight;

            for (auto &[v, w] : graph[node]) {
                if (!vis[v]) {
                    pq.push({w, v});
                }
            }
        }

        return sum;
    }
};
