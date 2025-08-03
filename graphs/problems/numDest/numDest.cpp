#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

// Problem: numDest
// URL: https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/description/
// Difficulty: hard
// Tags:
// Strategy:

#define MOD 1000000007

typedef pair<long long, long long> edge;
class Solution {

  public:
    int countPaths(int n, vector<vector<int>> &roads) {
        long long size = (long long)roads.size();
        vector<long long> paths(n, 0); // paths[r] is the number of shortest paths from src to r
        vector<long long> dist(n, LLONG_MAX);
        set<edge> heap;
        vector<vector<edge>> graph(n);

        for (long long index = 0; index < size; index++) {
            vector<int> &road = roads[index];
            long long u = road[0];
            long long v = road[1];
            long long w = road[2];
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }

        long long src = 0, dst = n - 1;
        paths[src] = 1;
        dist[src] = 0;
        heap.insert({dist[src], src});

        while (!heap.empty()) {
            auto [di, node] = *(heap.begin());
            heap.erase(heap.begin());

            for (auto &[v, w] : graph[node]) {
                if (di + w < dist[v]) {
                    paths[v] = paths[node];
                    dist[v] = w + di;
                    heap.insert({dist[v], v});
                } else if (di + w == dist[v]) {
                    paths[v] = (paths[v] + paths[node]) % MOD;
                }
            }
        }

        return paths[dst];
    }
};

#undef MOD