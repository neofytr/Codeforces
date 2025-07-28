// https://leetcode.com/problems/number-of-enclaves/description/

#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Solution {
  public:
    int numEnclaves(vector<vector<int>> &grid) {
        int m = (int)grid.size();
        int n = (int)grid[0].size();

        queue<pair<int, int>> que;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int dr[] = {0, -1, 0, +1};
        int dc[] = {-1, 0, +1, 0};
        for (int row = 0; row < m; row++) {
            if (grid[row][0]) {
                visited[row][0] = true;
                que.push({row, 0});
            }
            if (grid[row][n - 1]) {
                visited[row][n - 1] = true;
                que.push({row, n - 1});
            }
        }

        for (int col = 0; col < n; col++) {
            if (grid[0][col]) {
                visited[0][col] = true;
                que.push({0, col});
            }
            if (grid[m - 1][col]) {
                visited[m - 1][col] = true;
                que.push({m - 1, col});
            }
        }

        while (!que.empty()) {
            auto elt = que.front();
            int row = elt.first;
            int col = elt.second;
            que.pop();

            for (int index = 0; index < 4; index++) {
                int nrow = row + dr[index];
                int ncol = col + dc[index];

                if (nrow >= 0 && nrow < m && ncol >= 0 && ncol < n && !visited[nrow][ncol] && grid[nrow][ncol]) {
                    visited[nrow][ncol] = true;
                    que.push({nrow, ncol});
                }
            }
        }

        int count = 0;
        for (int row = 0; row < m; row++) {
            for (int col = 0; col < n; col++) {
                if (!visited[row][col] && grid[row][col]) {
                    count++;
                }
            }
        }

        return count;
    }
};

/*


0 0 0 0
1 0 1 0
0 1 1 0
0 0 0 0

*/