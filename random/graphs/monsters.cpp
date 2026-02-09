#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, m; cin >> n >> m;

	pair<int, int> src;
	vector<vector<int>> dist(n + 1, vector<int>(m + 1, LLONG_MAX));
	queue<pair<int, int>> que;
	vector<vector<int>> grid(n + 1, vector<int>(m + 1));
	for (int r = 1; r <= n; r++) {
		string col; cin >> col;
		for (int c = 1; c <= m; c++)
			if (col[c - 1] == '.') grid[r][c] = 0;
			else if (col[c - 1] == '#') grid[r][c] = 1;
			else if (col[c - 1] == 'A') grid[r][c] = 0, src = {r, c};
			else grid[r][c] = 0, que.push({r, c}), dist[r][c] = 0;
	}

	int dr[] = {-1, 0, 1, 0};
	int dc[] = {0, 1, 0, -1};
	while (!que.empty()) {
		auto [r, c] = que.front();
		int d = dist[r][c];

		for (int i = 0; i < 4; i++) {
			int nr = r + dr[i], nc = c + dc[i];
			if (nr <= n && nr >= 1 && nc <= m && nc >= 1 && !grid[nr][nc])
				if (dist[nr][nc] > d + 1)
					dist[nr][nc] = d + 1, que.push({nr, nc});
		}
	}
}