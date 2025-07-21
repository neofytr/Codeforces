// https://www.geeksforgeeks.org/problems/number-of-distinct-islands/1

#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

class Solution {
    void visitIsland(int row, int col, vector<vector<bool>> &visited, vector<vector<int>> &grid, vector<pair<int, int>> &island) {
        int n = (int)visited.size();
        int m = (int)visited[0].size();
        visited[row][col] = true;
        queue<pair<int, int>> que;
        int dr[] = {0, -1, 0, +1};
        int dc[] = {-1, 0, +1, 0};
        que.push({row, col});
        island.push_back({0, 0});

        while (!que.empty()) {
            auto elt = que.front();
            int r = elt.first;
            int c = elt.second;
            island.push_back({r - row, c - col});
            que.pop();

            for (int index = 0; index < 4; index++) {
                int nrow = r + dr[index];
                int ncol = c + dc[index];
                if (nrow >= 0 && ncol >= 0 && nrow < n && ncol < m && !visited[nrow][ncol] && grid[nrow][ncol]) {
                    visited[nrow][ncol] = true;
                    que.push({nrow, ncol});
                }
            }
        }
    }

  public:
    int countDistinctIslands(vector<vector<int>> &grid) {
        int n = (int)grid.size();
        int m = (int)grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        set<vector<pair<int, int>>> islands;

        for (int row = 0; row < n; row++) {
            for (int col = 0; col < m; col++) {
                if (!visited[row][col] && grid[row][col]) {
                    vector<pair<int, int>> island;
                    visitIsland(row, col, visited, grid, island);
                    islands.insert(island);
                }
            }
        }

        return (int)islands.size();
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            cin >> grid[row][col];
        }
    }

    Solution sol;
    cout << sol.countDistinctIslands(grid) << endl;

    return EXIT_SUCCESS;
}
