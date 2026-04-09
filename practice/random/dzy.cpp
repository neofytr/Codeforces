#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    int n, m;
    cin >> n >> m;

    queue<pair<pair<int, int>, int>> que; // (row, col, color)
    vector<vector<char>> graph(n, vector<char>(m));
    for (int row = 0; row < n; row++)
        for (int col = 0; col < m; col++)
            cin >> graph[row][col];

    int dr[] = {1, 0, -1, 0};
    int dc[] = {0, -1, 0, 1};
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++) {
            if (graph[r][c] == '.' && !vis[r][c]) {
                que.push({{r, c}, 0});
                vis[r][c] = true;
                while (!que.empty()) {
                    auto [coord, clr] = que.front();
                    auto [row, col] = coord;
                    que.pop();

                    graph[row][col] = !clr ? 'B' : 'W';
                    for (int i = 0; i < 4; i++) {
                        int nrow = row + dr[i];
                        int ncol = col + dc[i];
                        if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && graph[nrow][ncol] == '.')
                            if (!vis[nrow][ncol])
                                vis[nrow][ncol] = true, que.push({{nrow, ncol}, !clr});
                    }
                }
            }
        }

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++)
            cout << graph[row][col];
        cout << endl;
    }
    return 0;
}