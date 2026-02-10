#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, m, k; cin >> n >> m >> k;
	vector<vector<int>> grid(n + 1, vector<int>(m + 1));
	int y, x;
	int s = 0;
	for (int r = 1; r <= n; r++) {
		string col; cin >> col;
		for (int c = 1; c <= m; c++) {
			grid[r][c] = ((col[c - 1] == '.') ? 0 : 1);
			if (!grid[r][c])
				y = r, x = c, s++;
		}
	}

 	int dr[] = {-1, 0, 1, 0};
 	int dc[] = {0, -1, 0, 1};

 	vector<vector<bool>> vis(n + 1, vector<bool>(m + 1, false));
 	queue<pair<int, int>> que;

 	int cnt = 1;
 	que.push({y, x}), vis[y][x] = true;
 	while (!que.empty() && cnt < s - k) {
 		auto [r, c] = que.front(); que.pop();
 		if (cnt == s - k) 
 			break;
 		for (int i = 0; i < 4; i++) {
 			int nr = r + dr[i], nc = c + dc[i];
 			if (nr <= n && nr >= 1 && nc <= m && nc >= 1)
 				if (!vis[nr][nc] && !grid[nr][nc]) {
 					cnt++, vis[nr][nc] = true, que.push({nr, nc});
 					if (cnt == s - k) 
 						break;
 				}
  		}
 	}

 	for (int r = 1; r <= n; r++) {
 		for (int c = 1; c <= m; c++)
 			if (grid[r][c] == 1)
 				cout << "#";
 			else if (!grid[r][c] && !vis[r][c])
 				cout << "X";
 			else 
 				cout << ".";
 		cout << endl;
 	}
 	return 0;	
}