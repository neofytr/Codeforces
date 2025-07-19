#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define ROTTEN (2)
#define FRESH (1)

class Solution {
  public:
    int orangesRotting(vector<vector<int>> &grid) {
        int minutes;
        int visitedCount = 0;
        int totalCount = 0;
        int m = (int)grid.size();
        int n = (int)grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int row = 0; row < m; row++) {
            for (int col = 0; col < n; col++) {
                if (!grid[row][col])
                    continue;
                totalCount++;
            }
        }

        for (int row = 0; row < m; row++) {
            for (int col = 0; col < n; col++) {
                if (!visited[row][col] && grid[row][col] == ROTTEN) {
                }
            }
        }

        return minutes;
    }
};