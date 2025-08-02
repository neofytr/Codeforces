#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <vector>
using namespace std;

// Problem: shortestBinary
// URL: https://leetcode.com/problems/shortest-path-in-binary-matrix/description/
// Difficulty: medium
// Tags:
// Strategy:

class Solution {
  public:
    int shortestPathBinaryMatrix(vector<vector<int>> &grid) {
        int n = grid.size();
        if (grid[0][0] != 0 || grid[n - 1][n - 1] != 0)
            return -1;

        queue<pair<int, int>> que;
        vector<vector<bool>> vis(n, vector<bool>(n, false));
        const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

        que.push({0, 0});
        vis[0][0] = true;
        int depth = 1;

        while (!que.empty()) {
            int sz = que.size();
            while (sz--) {
                auto [y, x] = que.front();
                que.pop();
                if (y == n - 1 && x == n - 1) // checking and returning here is much safer and correct; what will happen if there is only one element, we can't check in the loop
                    return depth;
                for (int dir = 0; dir < 8; ++dir) {
                    int ny = y + dy[dir], nx = x + dx[dir];
                    if (ny >= 0 && ny < n && nx >= 0 && nx < n && !vis[ny][nx] && !grid[ny][nx]) {
                        vis[ny][nx] = true;
                        que.push({ny, nx});
                        
                    }
                }
            }
            depth++;
        }

        return -1;
    }
};

int main() {
    int n;
    cin >> n;
    vector<vector<int>> grid(n, vector<int>(n));
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            cin >> grid[row][col];
        }
    }

    Solution sol;
    cout << sol.shortestPathBinaryMatrix(grid) << endl;
    return EXIT_SUCCESS;
}