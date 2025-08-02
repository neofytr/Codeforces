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
        int n = (int)grid.size();
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        queue<pair<int, int>> que;
        vector<vector<bool>> vis(n, vector<bool>(n, false));

        int srcX = 0, srcY = 0;
        int destX = n - 1, destY = n - 1;
        if (!grid[srcY][srcX]) {
            dist[srcY][srcX] = 0;
            vis[srcY][srcY] = true;
            que.push({srcY, srcX});
        }

        while (!que.empty()) {
            int s = (int)que.size();
            while (s--) {
                auto elt = que.front();
                int nodeX = elt.second;
                int nodeY = elt.first;
                que.pop();

                for (int x = nodeX - 1; x <= nodeX + 1; x++) {
                    for (int y = nodeY - 1; y <= nodeY + 1; y++) {
                        if (x >= 0 && x < n && y >= 0 && y < n && !(x == nodeX && y == nodeY)) {
                            if (!grid[y][x] && !vis[y][x]) {
                                vis[y][x] = true;
                                dist[y][x] = dist[nodeY][nodeX] + 1;
                                que.push({y, x});
                            }
                        }
                    }
                }
            }
        }

        if (dist[destY][destX] == INT_MAX)
            return -1;

        return dist[destY][destX] + 1; // since we've to return the number of visited cells and not distance
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