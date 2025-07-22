// https://leetcode.com/problems/find-eventual-safe-states/description/

#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Solution {
  private:
    // checks if node is a safe vertex
    bool checkSafe(int node, vector<int> &isSafe, vector<bool> &path, vector<vector<int>> &graph) {
        if (isSafe[node] != -1) {
            return isSafe[node];
        }
        path[node] = true;

        for (int v : graph[node]) {
            if (path[v] || !checkSafe(v, isSafe, path, graph)) {
                // if we've seen this node before in the path
                // or it's not safe, then, the current node is also not safe, and nor is any other node
                // in the current path
                path[node] = false;
                return isSafe[node] = 0;
            }
        }

        path[node] = false;
        return isSafe[node] = 1; // all paths for this node lead to a terminal node
    }

  public:
    vector<int> eventualSafeNodes(vector<vector<int>> &graph) {
        int n = graph.size();
        vector<int> safe;
        vector<int> isSafe(n, -1);
        vector<bool> path(n, false);
        for (int node = 0; node < n; node++) {
            if (checkSafe(node, isSafe, path, graph)) {
                safe.push_back(node);
            }
        }

        return safe;
    }
};
