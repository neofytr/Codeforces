#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m; cin >> n >> m;

	vector<vector<char>> grid(n + 1, vector<char>(m + 1));
	for (int r = 1; r <= n; r++) {
		string col; cin >> col;
		for (int c = 1; c <= m; c++)
			grid[r][c] = col[c - 1];
	}

	queue<pair<int, int>> que;
	vector<vector<bool>> ex(n + 1, vector<bool>(m + 1, false));
	for (int c = 1; c <= m; c++) {
		if (grid[1][c] == 'U') ex[1][c] = true, que.push({1, c});
		if (grid[n][c] == 'D') ex[n][c] = true, que.push({n, c});
	}
	for (int r = 1; r <= n; r++) {
		if (grid[r][1] == 'L') ex[r][1] = true, que.push({r, 1});
		if (grid[r][m] == 'R') ex[r][m] = true, que.push({r, m});
	}

	int dr[] = {-1, 0, 1, 0};
	int dc[] = {0, -1, 0, 1};
	while (!que.empty()) {
		auto [r, c] = que.front(); que.pop();
		for (int i = 0; i < 4; i++) {
			int nr = r + dr[i], nc = c + dc[i];
			if (nr <= n && nr >= 1 && nc <= m && nc >= 1 && !ex[nr][nc] && grid[nr][nc] != '?') {
				if (!i && grid[nr][nc] == 'D')
					ex[nr][nc] = true, que.push({nr, nc});
				if (i == 1 && grid[nr][nc] == 'R')
					ex[nr][nc] = true, que.push({nr, nc});
				if (i == 2 && grid[nr][nc] == 'U')
					ex[nr][nc] = true, que.push({nr, nc});
				if (i == 3 && grid[nr][nc] == 'L')
					ex[nr][nc] = true, que.push({nr, nc});
			}
		}
	}

	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= m; c++) 
			if (grid[r][c] == '?') {
				int ucnt = 4, dcnt = 4, lcnt = 4, rcnt = 4;
				if (r == 1) ucnt--;
				if (r == n) dcnt--;
				if (c == 1) lcnt--;
				if (c == m) rcnt--;
				for (int i = 0; i < 4; i++) {
					int nr = r + dr[i], nc = c + dc[i];
					if (nr <= n && nr >= 1 && nc <= m && nc >= 1) 
						if (ex[nr][nc]) {
							if (!i) ucnt--;
							if (i == 1) lcnt--;
							if (i == 2) dcnt--;
							if (i == 3) rcnt--;
						} 
				}

				if (ucnt != 4 && dcnt != 4 && lcnt != 4 && rcnt != 4)
					ex[r][c] = true;
			}
			
		
	int cnt = 0;
	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= m; c++)
			if (!ex[r][c]) cnt++;
	cout << cnt << endl;
}

int32_t main() {
	int t; cin >> t;
	while(t--) solve();
	return 0;
}