// https://codeforces.com/problemset/problem/1829/E

#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

int traverse(int row, int col, vector<vector<bool>> &visited, vector<vector<int>> &graph) {
    int n = (int)visited.size();
    int m = (int)visited[0].size();
    visited[row][col] = true;
    if (!graph[row][col]) {
        return 0;
    }

    int dr[] = {-1, 0, +1, 0};
    int dc[] = {0, -1, 0, +1};

    int depth = 0;
    for (int index = 0; index < 4; index++) {
        int nrow = row + dr[index];
        int ncol = col + dc[index];

        if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m) { // is a valid grid cell
            if (!visited[nrow][ncol] && graph[nrow][ncol]) {
                depth += traverse(nrow, ncol, visited, graph);
            }
        }
    }

    return depth + graph[row][col];
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n, vector<int>(m));
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            cin >> graph[row][col];
        }
    }

    int maxDepth = INT_MIN;
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (!visited[row][col]) {
                maxDepth = max(maxDepth, traverse(row, col, visited, graph));
            }
        }
    }

    cout << maxDepth << endl;
    return;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}