#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, -1, 0, 1};

    pair<int, int> src;
    queue<pair<int, int>> monsQue;
    vector<vector<int>> mini(n + 1, vector<int>(m + 1, INT_MAX)); // mini[y][x] is the minimum number of steps in which a monster can reach (x, y)
    vector<vector<char>> graph(n + 1, vector<char>(m + 1));
    for (int row = 1; row <= n; row++) {
        for (int col = 1; col <= m; col++) {
            cin >> graph[row][col];
            if (graph[row][col] == 'A')
                src = {row, col};
            if (graph[row][col] == 'M') {
                monsQue.push({row, col});
                mini[row][col] = 0;
            }
        }
    }

    while (!monsQue.empty()) {
        int size = (int)monsQue.size();
        while (size--) {
            auto [r, c] = monsQue.front();
            monsQue.pop();

            for (int i = 0; i < 4; i++) {
                int nrow = r + dr[i];
                int ncol = c + dc[i];

                if (nrow < n && nrow >= 0 && ncol < m && ncol >= 0) {
                    if (graph[nrow][ncol] != '#' && mini[nrow][ncol] > mini[r][c] + 1) {
                        mini[nrow][ncol] = mini[r][c] + 1;
                        monsQue.push({nrow, ncol});
                    }
                }
            }
        }
    }

    return EXIT_SUCCESS;
}