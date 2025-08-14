#include <bits/stdc++.h>
#include <climits>
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

                if (nrow <= n && nrow >= 1 && ncol <= m && ncol >= 1) {
                    if (graph[nrow][ncol] != '#' && mini[nrow][ncol] > mini[r][c] + 1) {
                        mini[nrow][ncol] = mini[r][c] + 1;
                        monsQue.push({nrow, ncol});
                    }
                }
            }
        }
    }

    queue<pair<int, int>> que;
    vector<vector<int>> dist(n + 1, vector<int>(m + 1, INT_MAX));
    vector<vector<pair<int, int>>> parent(n + 1, vector<pair<int, int>>(m + 1));
    for (int row = 1; row <= n; row++) {
        for (int col = 1; col <= m; col++) {
            parent[row][col] = {row, col};
        }
    }

    dist[src.first][src.second] = 0;
    que.push({src.first, src.second});
    while (!que.empty()) {
        auto [r, c] = que.front();
        que.pop();

        if (r == 1 || r == n || c == 1 || c == m) {
            cout << "YES\n";
            cout << dist[r][c] << endl;
            string path;
            pair<int, int> dst = {r, c};
            pair<int, int> x = dst;
            pair<int, int> nxt = dst;
            while (x != src) {
                if (x != dst) {
                    if (x.first > nxt.first) {
                        path.push_back('U');
                    } else if (x.first < nxt.first) {
                        path.push_back('D');
                    } else if (x.second > nxt.second) {
                        path.push_back('L');
                    } else {
                        path.push_back('R');
                    }
                } else {
                    path.push_back(graph[x.first][x.second]);
                }
                nxt = x;
                x = parent[x.first][x.second];
            }
            if (x.first > nxt.first) {
                path.push_back('U');
            } else if (x.first < nxt.first) {
                path.push_back('D');
            } else if (x.second > nxt.second) {
                path.push_back('L');
            } else {
                path.push_back('R');
            }

            for (int i = path.length() - 1; i > 0; i--) {
                cout << path[i];
            }
            cout << endl;
            return EXIT_SUCCESS;
        }

        for (int i = 0; i < 4; i++) {
            int nrow = r + dr[i];
            int ncol = c + dc[i];

            if (nrow <= n && nrow >= 1 && ncol <= m && ncol >= 1) {
                if (graph[nrow][ncol] == '.' && dist[nrow][ncol] > dist[r][c] + 1) {
                    dist[nrow][ncol] = dist[r][c] + 1;
                    parent[nrow][ncol] = {r, c};
                    if (dist[nrow][ncol] < mini[nrow][ncol]) {
                        que.push({nrow, ncol});
                    }
                }
            }
        }
    }

    cout << "NO\n";
    return EXIT_SUCCESS;
}