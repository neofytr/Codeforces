#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: WATER
// URL: https://www.spoj.com/problems/WATER/
// Difficulty: medium
// Tags: priority-queue, bfs, graph, flood-fill
// Strategy: Use a min-heap (priority queue) to simulate water flooding from the boundaries inward.
//           Start by inserting all boundary cells into a min-heap. Then, repeatedly take the lowest
//           boundary and check its neighbors. If a neighbor is lower, water accumulates there.
//           Update the neighbor’s effective height and push it into the heap.

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n, vector<int>(m));
    for (int row = 0; row < n; row++)
        for (int col = 0; col < m; col++)
            cin >> graph[row][col];

    int vol = 0;
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, -1, 0, 1};

    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (r == 0 || r == n-1 || c == 0 || c == m-1) {
                pq.emplace(graph[r][c], r, c);
                visited[r][c] = true;
            }
        }
    }

    while (!pq.empty()) {
        auto [h, r, c] = pq.top();
        pq.pop();

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];

            if (nr < 0 || nr >= n || nc < 0 || nc >= m || visited[nr][nc])
                continue;

            visited[nr][nc] = true;

            if (graph[nr][nc] < h)
                vol += h - graph[nr][nc];

            pq.emplace(max(graph[nr][nc], h), nr, nc);
        }
    }
    
    cout << vol << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }    
    return 0;
}
