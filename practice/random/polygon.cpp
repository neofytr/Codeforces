#include <bits/stdc++.h>
using namespace std;

#define int long long
int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        string str;
        cin >> n;
        vector graph(n, vector<int>(n));
        for (int row = 0; row < n; row++) {
            cin >> str;
            for (int col = 0; col < n; col++)
                graph[row][col] = str[col] - '0';
        }

        int dr[] = {1, 0};
        int dc[] = {0, 1};

        bool can = true;
        vector vis(n, vector<bool>(n, false));
        for (int row = 0; row < n; row++)
            for (int col = 0; col < n; col++)
                if (graph[row][col] && !vis[row][col]) {
                    queue<pair<int, int>> que;

                    que.push({row, col});
                    vis[row][col] = true;
                    while (!que.empty()) {
                        auto [r, c] = que.front();
                        que.pop();

                        int cnt = 0;
                        for (int i = 0; i < 2; i++) {
                            int nrow = r + dr[i];
                            int ncol = c + dc[i];

                            if (nrow >= n || ncol >= n)
                                continue;
                            if (graph[nrow][ncol])
                                if (!vis[nrow][ncol])
                                    vis[nrow][ncol] = true, que.push({nrow, ncol});
                            if (!graph[nrow][ncol])
                                cnt++;
                        }
                        if (cnt >= 2)
                            can = false;
                    }
                }

        if (can)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}