#include <bits/stdc++.h>
#include <climits>
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
        int dr[] = {0, -1, 0, +1};
        int dc[] = {-1, 0, +1, 0};
        // effort[y][x] is the min effort required to move from 0,0 to y,x along any path
        // a path's effort is the maximum of the absolute difference between any two consecutive nodes in it
        vector<vector<int>> effort(n, vector<int>(m, INT_MAX));
        set<pair<int, pair<int, int>>> minHeap;

        effort[0][0] = 0;
        minHeap.insert({0, {0, 0}});
        while (!minHeap.empty()) {
            auto elt = *(minHeap.begin());
            int currEffort = elt.first;
            int nodeY = elt.second.first;
            int nodeX = elt.second.second;
            minHeap.erase(elt);

            for (int index = 0; index < 4; index++) {
                int dy = nodeY + dr[index];
                int dx = nodeX + dc[index];

                if (dy >= 0 && dx >= 0 && dx < m && dy < n) {
                    int newCurrEffort = max(currEffort, abs(heights[dy][dx] - heights[nodeY][nodeX])); // effort value along the current path
                    if (effort[dy][dx] > newCurrEffort) {
                        minHeap.erase({effort[dy][dx], {dy, dx}});
                        // wont traverse back to the parent since the parent's effort would necessarily be <= currEffort
                        effort[dy][dx] = newCurrEffort;
                        minHeap.insert({effort[dy][dx], {dy, dx}});
                    }
                }
            }
        }

        return effort[n - 1][m - 1];
    }
};