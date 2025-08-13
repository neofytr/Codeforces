#include <bits/stdc++.h>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<char>> map(n, vector<char>(m));
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            cin >> map[row][col];
        }
    }

    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, -1, 0, 1};

    // each map[y][x] is either . or #
    // we can walk in any four directions from a . to any other .
    // a collection of dots such that we can reach from any one to the other and no dots outside this
    // collection can be reached from any of the dots in the collection is called a room
    // we are to count the number of rooms

    int cnt = 0;
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (!vis[row][col] && map[row][col] == '.') {
                cnt++;
                queue<pair<int, int>> que; // (row, col)
                que.push({row, col});
                vis[row][col] = true;

                while (!que.empty()) {
                    auto [r, c] = que.front();
                    que.pop();

                    for (int i = 0; i < 4; i++) {
                        int nrow = r + dr[i];
                        int ncol = c + dc[i];

                        if (nrow < n && nrow >= 0 && ncol < m && ncol >= 0) {
                            if (!vis[nrow][ncol] && map[nrow][ncol] == '.') {
                                vis[nrow][ncol] = true;
                                que.push({nrow, ncol});
                            }
                        }
                    }
                }
            }
        }
    }

    cout << cnt << endl;
}