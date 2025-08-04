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
  public:
    int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold) {
        // we find the distance from each to node to every other node
        // using floyd-warshall
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));

        // initialize the distance array
        for (int node = 0; node < n; node++) {
            dist[node][node] = 0;
        }

        for (auto &vec : edges) {
            int u = vec[0];
            int v = vec[1];
            int w = vec[2];
            dist[u][v] = w;
            dist[v][u] = w;
        }

        for (int via = 0; via < n; via++) {
            for (int u = 0; u < n; u++) {
                for (int v = 0; v < n; v++) {
                    int uvia = dist[u][via];
                    int viav = dist[via][v];
                    int uv = dist[u][v];
                    if (uvia != INT_MAX && viav != INT_MAX && uvia + viav < uv) {
                        dist[u][v] = uvia + viav;
                    }
                }
            }
        }

        int minCount = INT_MAX;
        int ans = -1;

        for (int node = 0; node < n; node++) {
            int count = 0;
            for (int x = 0; x < n; x++) {
                if (x != node && dist[node][x] <= distanceThreshold)
                    count++;
            }

            if (count <= minCount) {
                minCount = count;
                ans = node;
            }
        }

        return ans;
    }
};