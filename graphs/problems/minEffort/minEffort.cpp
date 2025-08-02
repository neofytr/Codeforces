#include <bits/stdc++.h>
#include <climits>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

// Problem: minEffort
// URL: http://leetcode.com/problems/path-with-minimum-effort/description/
// Difficulty: medium
// Tags:
// Strategy:

class Solution {
  public:
    int minimumEffortPath(vector<vector<int>> &heights) {
        int n = (int)heights.size();
        int m = (int)heights[0].size();
        int dy[] = {0, -1, 0, 1};
        int dx[] = {-1, 0, +1, 0};

        // effort[y][x] is the min effort needed to go from 0, 0 to y, x along any path
        // the effort of a path is the maximum value of absolute diff of heights of any two consecutive nodes in the path
        vector<vector<int>> effort(n, vector<int>(m, INT_MAX));
        set<pair<int, pair<int, int>>> heap;

        effort[0][0] = 0;
        heap.insert({effort[0][0], {0, 0}});
        while (!heap.empty()) {
            auto elt = *(heap.begin());
            int currMinEffort = elt.first;
            int currX = elt.second.second;
            int currY = elt.second.first;
            heap.erase(elt);

            if (currX == m - 1 && currY == n - 1)
                return currMinEffort;

            for (int index = 0; index < 4; index++) {
                int ny = currY + dy[index];
                int nx = currX + dx[index];

                if (ny >= 0 && nx >= 0 && nx < m && ny < n) {
                    int newEffort = max(currMinEffort, abs(heights[ny][nx] - heights[currY][currX]));
                    if (effort[ny][nx] > newEffort) {
                        heap.erase({effort[ny][nx], {ny, nx}});
                        effort[ny][nx] = newEffort;
                        heap.insert({effort[ny][nx], {ny, nx}});
                    }
                }
            }
        }

        return -1;
    }
};