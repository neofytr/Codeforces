#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(500)

int n, m;
int grid[MAX + 1][MAX + 1];
bool vis[MAX + 1][MAX + 1];
int srcx, srcy;
int dstx, dsty;

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, -1, 0, 1};
void dfs(int r, int c) {
	for (int i = 0; i < 4; i++) {
		int nr = r + dr[i], nc = c + dc[i];
		if (nr <= n && nr >= 1 && nc <= m && nc >= 1 && !vis[nr][nc]) {
			if (!grid[nr][nc])
				vis[nr][nc] = true, dfs(nr, nc);
			else {
				int row = nr;
				while (row + 1 <= n && grid[row + 1][nc])
					row++;
			}
		}
	}
}

int32_t main() {
	cin >> n >> m;
	for (int r = 1; r <= n; r++) {
		string col; cin >> col;
		for (int c = 1; c <= m; c++)
			grid[r][c] = (col[c - 1] == '.' ? 0 : 1);
	}

	cin >> srcx >> srcy >> dstx >> dsty;
	dfs(srcx, srcy);
	if (vis[dstx][dsty])
		cout << "YES"; 
	else
		cout << "NO";
	cout << endl;
	return 0;
}