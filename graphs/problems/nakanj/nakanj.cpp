#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: nakanj
// URL: https://www.spoj.com/problems/NAKANJ/
// Difficulty: medium
// Tags: 
// Strategy: 

#define NROWS 8
#define NCOLS 8

#define idx(row, col) (row * NCOLS + col)

bool valid(int row, int col) {
    return (row >= 0 && col >= 0 && row < NROWS && col < NCOLS);
}

void solve() {
    string srcstr, dststr;
    cin >> srcstr >> dststr;

    // convert chess notation ('a1', 'h8') to 0-based row, col indices
    int src_row = srcstr[1] - '1';
    int src_col = srcstr[0] - 'a';
    int dst_row = dststr[1] - '1';
    int dst_col = dststr[0] - 'a';

    int src = idx(src_row, src_col);
    int dst = idx(dst_row, dst_col);

    queue<int> que;
    vector<bool> vis(NROWS * NCOLS, false);
    vector<int> dist(NROWS * NCOLS, LLONG_MAX);

    vis[src] = true;
    dist[src] = 0;
    que.push(src);

    // knight move offsets
    int dr[8] = {2, 2, -2, -2, 1, -1, 1, -1};
    int dc[8] = {1, -1, 1, -1, 2, 2, -2, -2};

    while(!que.empty()) {
        int x = que.front();
        que.pop();

        int r = x / NCOLS;
        int c = x % NCOLS;

        for (int i = 0; i < 8; i++) {
            int nrow = r + dr[i];
            int ncol = c + dc[i];
            int id = idx(nrow, ncol);
            if (valid(nrow, ncol) && !vis[id]) {
                dist[id] = dist[x] + 1;
                vis[id] = true;
                que.push(id);
            }
        }
    }

    cout << dist[dst] << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}
