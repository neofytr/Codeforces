#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int r, c, n, p;
    cin >> r >> c >> n >> p;

    vector<pair<int, int>> where(n + 1);
    vector<vector<int>> mat(r + 1, vector<int>(c + 1));
    for (int row = 1; row <= r; row++)
        for (int col = 1; col <= c; col++)
            cin >> mat[row][col], where[mat[row][col]] = {row, col};

    pair<int, int> src = where[p];
    queue<pair<int, int>> que;

    vector<bool> cnt(n + 1, false);

    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, -1, 0, 1};

    que.push(src);
    int d = 0;
    while (!que.empty()) {
        auto [x, y] = que.front();
        que.pop();

        for (int i = 0; i < 4; i++) {
            int nrow = x + dr[i], ncol = y + dc[i];
            if (nrow >= 1 && nrow <= r && ncol >= 1 && ncol <= c) {
                int elt = mat[nrow][ncol] + d;
                if (elt <= n)
                    cnt[elt] = true;
            }
        }

        for (int i = 0; i < 4; i++) {
            int nrow = x + dr[i], ncol = y + dc[i];
            if (nrow >= 1 && nrow <= r && ncol >= 1 && ncol <= c && mat[nrow][ncol] == mat[x][y] - 1) {
                que.push({nrow, ncol});
            }
        }
        d++;
    }

    int num = 0;
    for (int r = 1; r <= n; r++)
        if (cnt[r]) num++;

    cout << num << "/" << n - 1 << endl;
    return 0;
}