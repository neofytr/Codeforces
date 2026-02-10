#include <bits/stdc++.h>
using namespace std;

#define int long long
#define EMPTY 0
#define WALL 1
#define GOOD 2 
#define BAD 3

void solve() {
	int n, m; cin >> n >> m;
	vector<vector<int>> grid(n + 1, vector<int>(m + 1));
	for (int r = 1; r <= n; r++) {
		string col; cin >> col;
		for (int c = 1; c <= m; c++)
			if (col[c - 1] == '.') grid[r][c] = EMPTY;
			else if (col[c - 1] == '#') grid[r][c] = WALL;
			else if (col[c - 1] == 'G') grid[r][c] = GOOD;
			else grid[r][c] = BAD;
	}

	int dr[] = {-1, 0, 1, 0};
	int dc[] = {0, 1, 0, -1};
	vector<vector<bool>> vis(n + 1, vector<bool>(m + 1, false));
	queue<pair<int, int>> que;

	vis[n][m] = true;
	que.push({n, m});
	while (!que.empty()) {
		auto [r, c] = que.front(); que.pop();
		for (int i = 0; i < 4; i++) {
			int nr = r + dr[i], nc = c + dc[i];
			if (nr <= n && nr >= 1 && nc <= m && nc >= 1)
				if (!vis[nr][nc] && grid[nr][nc] != WALL)
					vis[nr][nc] = true, que.push({nr, nc});
		}
	}

	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= m; c++)
			if (grid[r][c] == GOOD && !vis[r][c]) {
				cout << "NO" << endl;
				return;
			}

	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= m; c++)
			if (grid[r][c] == BAD) {
				for (int i = 0; i < 4; i++) {
					int nr = r + dr[i], nc = c + dc[i];
					if (nr <= n && nr >= 1 && nc <= m && nc >= 1)
						if (grid[nr][nc] == GOOD) {
							cout << "NO" << endl;
							return;
						} else if (grid[nr][nc] == EMPTY)
							grid[nr][nc] = WALL;
				}
			}

	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= m; c++)
			vis[r][c] = false;

	if (grid[n][m] != EMPTY)
		vis[n][m] = true, que.push({n, m});
	while (!que.empty()) {
		auto [r, c] = que.front(); que.pop();
		for (int i = 0; i < 4; i++) {
			int nr = r + dr[i], nc = c + dc[i];
			if (nr <= n && nr >= 1 && nc <= m && nc >= 1)
				if (!vis[nr][nc] && grid[nr][nc] != WALL)
					vis[nr][nc] = true, que.push({nr, nc});
		}
	}

	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= m; c++)
			if (grid[r][c] == GOOD && !vis[r][c]) {
				cout << "NO" << endl;
				return;
			} else if (grid[r][c] == BAD && vis[r][c]) {
				cout << "NO" << endl;
				return;
			}

	cout << "YES" << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}