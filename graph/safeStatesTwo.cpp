// https://leetcode.com/problems/find-eventual-safe-states/
#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Solution {
  private:
    bool traverse(int node, vector<int> &dp, vector<bool> &path, vector<vector<int>> &graph) {
        if (dp[node] != -1) {
            return dp[node];
        }

        path[node] = true;

        for (int v : graph[node]) {
            if (path[v] || !traverse(v, dp, path, graph)) {
                path[node] = false;
                return dp[node] = false;
            }
        }

        path[node] = false;
        return dp[node] = true;
    }

  public:
    vector<int> eventualSafeNodes(vector<vector<int>> &graph) {
        int n = (int)graph.size();
        vector<int> safe;

        vector<bool> path(n, false);
        vector<int> dp(n, -1);
        for (int node = 0; node < n; node++) {
            if (traverse(node, dp, path, graph)) {
                safe.push_back(node);
            }
        }

        return safe;
    }
};