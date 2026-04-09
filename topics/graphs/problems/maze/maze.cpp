#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

#define int long long

// Problem: maze
// URL: https://codeforces.com/problemset/problem/377/A
// Difficulty: medium
// Tags:
// Strategy:

#include <bits/stdc++.h>
#include <vector>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    int dr[] = {-1, 0, +1, 0};
    int dc[] = {0, -1, 0, +1};

    int empty = 0;
    pair<int, int> src;
    vector<vector<char>> graph(n, vector<char>(m));
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            cin >> graph[row][col];
            if (graph[row][col] == '.') {
                empty++;
                src = {row, col};
            }
        }
    }

    int cnt = 0;
    int toKeep = empty - k;
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    stack<pair<int, int>> st;

    st.push(src);
    vis[src.first][src.second] = true;
    cnt++;

    while (!st.empty() && cnt < toKeep) {
        auto [row, col] = st.top();
        st.pop();

        for (int i = 0; i < 4; i++) {
            int nrow = row + dr[i];
            int ncol = col + dc[i];
            if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && graph[nrow][ncol] == '.' && !vis[nrow][ncol]) {
                vis[nrow][ncol] = true;
                cnt++;
                st.push({nrow, ncol});
                if (cnt == toKeep)
                    break;
            }
        }
    }

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (graph[row][col] == '.' && !vis[row][col])
                graph[row][col] = 'X';
        }
    }

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            cout << graph[row][col];
        }
        cout << endl;
    }

    return EXIT_SUCCESS;
}