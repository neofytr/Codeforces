#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (1000)

int n, m;
int grid[MAX + 1][MAX + 1];
int vis[MAX + 1][MAX + 1];

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, -1, 0, 1};
void dfs(int r, int c) {
	for (int i = 0; i < 4; i++) {
		int nr = r + dr[i];
		int nc = c + dc[i];

		if (nr <= n && nr >= 1 && nc <= m && nc >= 1 && !vis[nr][nc] && !grid[nr][nc])
			vis[nr][nc] = true, dfs(nr, nc);
	}
}

int32_t main() {
	cin >> n >> m;
	for (int r = 1; r <= n; r++) {
		string col; cin >> col;
		for (int c = 1; c <= m; c++)
			grid[r][c] = (col[c - 1] == '.' ? 0 : 1);
	}

	int cnt = 0;
	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= m; c++)
			if (!vis[r][c] && !grid[r][c]) {
				vis[r][c] = true;
				cnt++;
				dfs(r, c);
			}

	cout << cnt << endl;
	return 0;
}