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
		que.pop();
		int d = dist[r][c];

		for (int i = 0; i < 4; i++) {
			int nr = r + dr[i], nc = c + dc[i];
			if (nr <= n && nr >= 1 && nc <= m && nc >= 1 && !grid[nr][nc])
				if (dist[nr][nc] > d + 1)
					dist[nr][nc] = d + 1, que.push({nr, nc});
		}
	}

	vector<vector<bool>> vis(n + 1, vector<bool> (m + 1, false));
	vector<vector<pair<int, int>>> parent(n + 1, vector<pair<int, int>>(m + 1));
	queue<pair<int, pair<int, int>>> q;
	q.push({0, src});
	parent[src.first][src.second] = {-1, -1};
	vis[src.first][src.second] = true;

	while (!q.empty()) {
		auto [d, p] = q.front();
		auto [r, c] = p;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = r + dr[i], nc = c + dc[i];
			if (nr <= n && nr >= 1 && nc <= m && nc >= 1 && !grid[nr][nc])
				if (!vis[nr][nc] && d + 1 < dist[nr][nc])
					vis[nr][nc] = true, q.push({d + 1, {nr, nc}}), parent[nr][nc] = {r, c};
		}
	}

	int x = -1, y = -1;
	for (int r = 1; r <= n; r++) {
		if (!grid[r][1] && vis[r][1]) {
			x = r, y = 1;
			break;
		}
		if (!grid[r][m] && vis[r][m]) {
			x = r, y = m;
			break;
		}
	}
	for (int c = 1; c <= m; c++) {
		if (!grid[1][c] && vis[1][c]) {
			x = 1, y = c;
			break;
		}
		if (!grid[n][c] && vis[n][c]) {
			x = n, y = c;
			break;
		}
	}

	if (x == -1) {
		cout << "NO" << endl;
		return 0;
	}

	cout << "YES" << endl;
	string path;

	int r = x, c = y;
	while (parent[r][c].first != -1 && parent[r][c].second != -1) {
		auto [pr, pc] = parent[r][c];
		for (int i = 0; i < 4; i++) {
			int nr = pr + dr[i], nc = pc + dc[i];
			if (nr == r && nc == c) {
				switch(i) {
				case 0: 
					path.push_back('U');
					break;
				case 1:
					path.push_back('R');
					break;
				case 2:
					path.push_back('D');
					break;
				case 3:
					path.push_back('L');
					break;
				}
				break;
			}
		}
		r = pr, c = pc;
	}

	reverse(path.begin(), path.end());
	cout << path.length() << endl;
	cout << path << endl;
}