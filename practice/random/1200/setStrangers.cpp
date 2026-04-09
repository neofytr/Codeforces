#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>> mat(n + 1, vector<int>(m + 1));
	for (int row = 1; row <= n; row++)
		for (int col = 1; col <= m; col++)
			cin >> mat[row][col];

	int dr[] = {-1, 0, 1, 0};
	int dc[] = {0, 1, 0, -1};
	
	vector<int> colors(n * m + 1);
	for (int row = 1; row <= n; row++)
		for (int col = 1; col <= m; col++) {
			if (!colors[mat[row][col]])	
				colors[mat[row][col]]++;

			for (int i = 0; i < 4; i++) {
				int nr = row + dr[i];
				int nc = col + dc[i];

				if (nr >= 1 && nr <= n && nc >= 1 && nc <= m && mat[nr][nc] == mat[row][col] && colors[mat[row][col]] != 2)
					colors[mat[row][col]] = 2;
			}
		}

	int maxi = LLONG_MIN, sum = 0;
	for (int r = 1; r <= n * m; r++)
		sum += colors[r], maxi = max(maxi, colors[r]);

	cout << sum - maxi << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}