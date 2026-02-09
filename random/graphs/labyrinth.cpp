#include <bits/stdc++.h>
using namespace std;

#define int long long
typedef pair<pair<int, int>, pair<int, int>> pp;

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

	
	return 0;
}
