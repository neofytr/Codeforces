#include <bits/stdc++.h>
using namespace std;

#define O 'O'
#define X 'X'

class Solution {
  public:
    void solve(vector<vector<char>> &board) {
        int m = board.size();
        if (m == 0)
            return;
        int n = board[0].size();

        vector<vector<bool>> visited(m, vector<bool>(n, false));
        queue<pair<int, int>> q;

        // Add all 'O's on the border to the queue
        for (int i = 0; i < m; i++) {
            if (board[i][0] == O) {
                q.push({i, 0});
                visited[i][0] = true;
            }
            if (board[i][n - 1] == O) {
                q.push({i, n - 1});
                visited[i][n - 1] = true;
            }
        }

        for (int j = 0; j < n; j++) {
            if (board[0][j] == O) {
                q.push({0, j});
                visited[0][j] = true;
            }
            if (board[m - 1][j] == O) {
                q.push({m - 1, j});
                visited[m - 1][j] = true;
            }
        }

        // BFS to mark all 'O's connected to the border as safe
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            board[r][c] = '#'; // mark as safe

            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr >= 0 && nr < m && nc >= 0 && nc < n && board[nr][nc] == O && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == O)
                    board[i][j] = X;
                else if (board[i][j] == '#')
                    board[i][j] = O;
            }
        }
    }
};
