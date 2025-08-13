#include <bits/stdc++.h>
using namespace std;

#define MAX 1000

char laby[MAX + 1][MAX + 1];
pair<int, int> parent[MAX + 1][MAX + 1];
int dist[MAX + 1][MAX + 1];
int main() {
    int n, m;
    cin >> n >> m;

    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, -1, 0, 1};
    pair<int, int> src, dst;

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            cin >> laby[row][col];
            if (laby[row][col] == 'A')
                src = {row, col};
            if (laby[row][col] == 'B')
                dst = {row, col};
            parent[row][col] = {row, col};
            dist[row][col] = INT_MAX;
        }
    }

    queue<pair<int, int>> que;

    dist[src.first][src.second] = 0;
    que.push({src.first, src.second});
    while (!que.empty()) {
        auto &[r, c] = que.front();
        que.pop();

        for (int i = 0; i < 4; i++) {
            int nrow = r + dr[i];
            int ncol = c + dc[i];

            if (nrow < n && nrow >= 0 && ncol < m && ncol >= 0) {
                if (dist[r][c] + 1 < dist[nrow][ncol] && laby[nrow][ncol] != '#') {
                    dist[nrow][ncol] = dist[r][c] + 1;
                    parent[nrow][ncol] = {r, c};
                    que.push({nrow, ncol});
                }
            }
        }
    }

    if (dist[dst.first][dst.second] == INT_MAX) {
        cout << "NO\n";
        return EXIT_SUCCESS;
    }

    string path;
    pair<int, int> x = dst;
    pair<int, int> nxt = dst;
    while (x != parent[x.first][x.second]) {
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
            path.push_back(laby[x.first][x.second]);
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

    cout << "YES\n";
    cout << dist[dst.first][dst.second] << endl;
    for (int i = path.length() - 1; i > 0; i--) {
        cout << path[i];
    }
    cout << endl;
    return EXIT_SUCCESS;
}