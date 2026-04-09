#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, m; cin >> n >> m;
	int r, c; cin >> r >> c;
	int x, y; cin >> x >> y;

	vector<vector<int>> grid(n + 1, vector<int>(m + 1));
	for (int row = 1; row <= n; row++) {
		string s; cin >> s;
		for (int col = 1; col <= m; col++)
			if (s[col - 1] == '.') grid[row][col] = 0;
			else grid[row][col] = 1; 
	}

	vector<vector<int>> dist(n + 1, vector<int>(m + 1, LLONG_MAX));
	deque<pair<int, int>> dq;

	int dr[] = {-1, 0, 1, 0};
	int dc[] = {0, -1, 0, 1};
	dq.push_back({r, c});
	dist[r][c] = 0;
	while (!dq.empty()) {
		auto [i, j] = dq.front();
		dq.pop_front();
		int d = dist[i][j];
		for (int k = 0; k < 4; k++) {
			int nr = i + dr[k], nc = j + dc[k];
			if (nr <= n && nr >= 1 && nc <= m && nc >= 1 && !grid[nr][nc]) {
				if (k == 1 && dist[nr][nc] > d + 1) {
					dist[nr][nc] = d + 1;
					dq.push_back({nr, nc});
				}
				if (k != 1 && dist[nr][nc] > d) {
					dist[nr][nc] = d;
					dq.push_front({nr, nc});
				}
			}
		}
	}

	int cnt = 0;
	for (int row = 1; row <= n; row++) 
		for (int col = 1; col <= m; col++) {
			int d = dist[row][col];
			if (d <= x && (col - c) + d <= y)
				cnt++;
		}
	
	cout << cnt << endl;
	return 0;
}