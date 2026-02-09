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


}