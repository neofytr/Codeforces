#include <bits/stdc++.h>
using namespace std;

#define int long long
typedef pair<pair<int, int>, pair<int, int>> pp;

struct Cmp {
	bool operator()(const pp &one, const pp &two) const {
		auto [lone, rone] = one.first;
		auto [ltwo, rtwo] = two.first;
		int m1 = max(lone, rone), m2 = max(ltwo, rtwo);

		if (m1 > m2) return true;
		return false;
	}
};

int32_t main() {
	int n, m; cin >> n >> m;
	int x, y; cin >> x >> y;
	int maxl, maxr; cin >> maxl >> maxr;

	vector<vector<int>> grid(n + 1, vector<int>(m + 1));
	for (int r = 1; r <= n; r++) {
		string col; cin >> col;
		for (int c = 1; c <= m; c++)
			grid[r][c] = (col[c - 1] == '*' ? 1 : 0);
	}

	int dr[] = {-1, 0, 1, 0};
	int dc[] = {0, -1, 0, 1};

	vector<vector<bool>> vis(n + 1, vector<bool>(m + 1, false));

	set<pp, Cmp> que;
	que.insert({{maxl, maxr}, {x, y}});
	vis[x][y] = true;

	while (!que.empty()) {
		auto it = que.begin();
		auto [e, pos] = *it;
		que.erase(it);

		auto [r, c] = pos;
		auto [lft, rt] = e;

		for (int i = 0; i < 4; i++) {
			int nr = r + dr[i], nc = c + dc[i];
			if (nr >= 1 && nr <= n && nc >= 1 && nc <= m &&
			    !grid[nr][nc] && !vis[nr][nc]) {

				if (i == 1 && lft >= 1) {
					vis[nr][nc] = true;
					que.insert({{lft - 1, rt}, {nr, nc}});
				}

				if (i == 3 && rt >= 1) {
					vis[nr][nc] = true;
					que.insert({{lft, rt - 1}, {nr, nc}});
				}

				if (i == 0 || i == 2) {
					vis[nr][nc] = true;
					que.insert({{lft, rt}, {nr, nc}});
				}
			}
		}
	}

	int cnt = 0;
	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= m; c++)
			if (!grid[r][c] && vis[r][c])
				 cnt++;
	}

	cout << cnt << endl;
	return 0;
}
