#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, m; cin >> n >> m; 

	pair<int, int> src, dst;
	vector<vector<int>> grid(n + 1, vector<int>(m + 1));
	for (int r = 1; r <= n; r++) {
		string col; cin >> col;
		for (int c = 1; c <= m; c++)
			if (col[c - 1] == '.') grid[r][c] = 0;
			else if (col[c - 1] == '#') grid[r][c] = 1;
			else if (col[c - 1] == 'A') grid[r][c] = 0, src = {r, c};
			else grid[r][c] = 0, dst = {r, c};
	}

	vector<vector<int>> dist(n + 1, vector<int> (m + 1, LLONG_MAX));
	vector<vector<pair<int, int>>> p(n + 1, vector<pair<int, int>>(m + 1));
	queue<pair<int, int>> que;

	int dr[] = {-1, 0, 1, 0};
	int dc[] = {0, 1, 0, -1};
	dist[src.first][src.second] = 0;
	que.push(src);
	p[src.first][src.second] = {-1, -1};
	while (!que.empty()) {
		auto [r, c] = que.front(); que.pop();
		int d = dist[r][c];
		for (int i = 0; i < 4; i++) {
			int nr = r + dr[i], nc = c + dc[i];
			if (nr >= 1 && nr <= n && nc >= 1 && nc <= m && !grid[nr][nc])
				if (dist[nr][nc] > d + 1)
					dist[nr][nc] = d + 1, p[nr][nc] = {r, c}, que.push({nr, nc});
		}
	}

	if (dist[dst.first][dst.second] == LLONG_MAX) {
		cout << "NO" << endl;
		return 0;
	}

	cout << "YES" << endl;
	string path;

	int r = dst.first, c = dst.second;
	while (p[r][c].first != -1 && p[r][c].second != -1) {
		auto [pr, pc] = p[r][c];
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
	return 0;
}