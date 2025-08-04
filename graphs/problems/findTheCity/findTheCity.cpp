#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

// Problem: findTheCity
// URL: https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/description/
// Difficulty: medium
// Tags:
// Strategy:

struct cmp {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) const {
        if (a.first != b.first)
            return a.first < b.first; // ascending by the first element
        else
            return a.second > b.second; // descending by the first
    }
};

class Solution {
  public:
    int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold) {
        vector<vector<pair<int, int>>> graph(n);
        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }

        set<pair<int, int>, cmp> ans;
        for (int src = 0; src < n; src++) {
            vector<int> dist(n, INT_MAX);
            set<pair<int, int>> heap;

            dist[src] = 0;
            heap.insert({dist[src], src});
            while (!heap.empty()) {
                auto [d, x] = *heap.begin();
                heap.erase(heap.begin());

                for (auto &[v, w] : graph[x]) {
                    if (dist[x] + w < dist[v] && dist[x] + w <= distanceThreshold) {
                        dist[v] = dist[x] + w;
                        heap.insert({dist[v], v});
                    }
                }
            }

            int count = 0;
            for (int node = 0; node < n; node++) {
                if (node != src && dist[node] != INT_MAX) {
                    count++;
                }
            }

            ans.insert({count, src});
        }

        return (ans.begin())->second;
    }
};

class SolutionTwo {
    
}